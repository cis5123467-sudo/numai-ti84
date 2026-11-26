#include "topics.h"
#include <fileioc.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "course_sizes.inc"

Course courses[COURSE_COUNT];
const int course_count=COURSE_COUNT;
static Chapter chapters[CHAPTER_COUNT];
static Topic topics[TOPIC_COUNT];
static MathsDetail details[DETAIL_COUNT];

static const uint16_t sizes[]={TEXT_SIZES};
static const char *archive[sizeof(sizes)/sizeof(*sizes)];
static const uint8_t *at,*end;
static bool invalid;

static const void *archived_data(const char *name,uint16_t size,const char magic[4]) {
    uint8_t file=ti_Open(name,"r");
    if(!file)return NULL;
    const void *data=NULL;
    if(ti_IsArchived(file)&&ti_GetSize(file)==size) {
        const void *pointer=ti_GetDataPtr(file);
        if(pointer&&!memcmp(pointer,magic,4))data=pointer;
    }
    ti_Close(file);
    return data;
}

static uint24_t read_number(void) {
    if(end-at<3){invalid=true;return 0;}
    uint24_t value=(uint24_t)at[0]|(uint24_t)at[1]<<8|(uint24_t)at[2]<<16;
    at+=3;
    return value;
}

static const char *read_text(void) {
    uint24_t offset=read_number();
    if(!offset)return NULL;
    unsigned file=offset>>16;
    unsigned pos=offset&UINT16_MAX;
    if(file>=sizeof(sizes)/sizeof(*sizes)||pos<4||pos>=sizes[file]) {
        invalid=true;
        return NULL;
    }
    // Writers only emit offsets at string boundaries. Check the terminator
    // before passing a user-transferred AppVar pointer to the UI.
    const char *text=archive[file]+pos;
    if(!memchr(text,0,sizes[file]-pos)){invalid=true;return NULL;}
    return text;
}

bool courses_load(void) {
    for(unsigned i=0;i<sizeof(sizes)/sizeof(*sizes);i++) {
        char name[9];
        snprintf(name,sizeof(name),"NMC%03u",i);
        archive[i]=archived_data(name,sizes[i],"N14\0");
        if(!archive[i])return false;
    }
    const uint8_t *table=archived_data("NMTABLE",TABLE_SIZE,"NT4\0");
    if(!table)return false;
    at=table+4;end=table+TABLE_SIZE;invalid=false;
    unsigned h=0,t=0,d=0;
    for(int i=0;i<COURSE_COUNT;i++) {
        Course *course=&courses[i];
        course->title=read_text();
        course->code=read_text();
        unsigned count=read_number();
        if(!course->title||!count||count>CHAPTER_COUNT-h)return false;
        course->count=count;
        course->chapters=chapters+h;
        for(unsigned j=0;j<count;j++) {
            Chapter *chapter=&chapters[h++];
            chapter->title=read_text();
            unsigned entries=read_number();
            if(!chapter->title||!entries||entries>TOPIC_COUNT-t)return false;
            chapter->count=entries;
            chapter->topics=topics+t;
            for(unsigned k=0;k<entries;k++) {
                Topic *topic=&topics[t++];
                topic->title=read_text();
                topic->course=read_text();
                topic->method=read_text();
                topic->example=read_text();
                topic->formula=read_text();
                unsigned operation=read_number();
                if(!topic->title||operation>=OperationCount)return false;
                topic->operation=operation;
                for(unsigned f=0;f<MAX_FIELDS;f++) {
                    topic->labels[f]=read_text();
                    topic->values[f]=read_text();
                }
                if(read_number()) {
                    if(d==DETAIL_COUNT)return false;
                    MathsDetail *detail=&details[d++];
                    topic->detail=detail;
                    detail->notes=read_text();
                    for(unsigned e=0;e<EXTRA_EXAMPLES;e++) {
                        detail->examples[e].title=read_text();
                        detail->examples[e].working=read_text();
                    }
                }
            }
        }
    }
    return !invalid&&at==end&&h==CHAPTER_COUNT&&t==TOPIC_COUNT&&d==DETAIL_COUNT;
}
