#include "eadk.h"
#include "topics.h"
#include "mathview.h"
#include "palette.h"
#include "number.h"
#include <stdio.h>
#include <string.h>

void platform_init(void);
void platform_end(void);
int platform_width(const char *, int, bool, bool);
void platform_text(int, int, const char *, uint16_t, uint16_t, bool, bool, bool);
char platform_alpha(int);

enum { Rows = 11, LineHeight = 16 };
typedef enum { Home, Courses, Chapters, Topics, Details, Reading, Operations,
               Result, Working, Settings, Search, Matches } Page;
static Page page, back_from_operations, reading_parent;
static int course, chapter, topic, detail, operation, match, scroll;
static int cursor, field;
static bool second, alpha, alpha_lock, degrees=true, decimal, topic_form, result_math;
static char input[MAX_FIELDS][EXPRESSION_SIZE], expression[EXPRESSION_SIZE];
static char query[EXPRESSION_SIZE], ans[EXPRESSION_SIZE];
static char last_expression[EXPRESSION_SIZE];
static const char *last_read, *read_title;
static Solution result;
static struct { unsigned c,h,t; } matches[40];
static int match_count;

static void rect(int x,int y,int w,int h,uint16_t color) {
    if(x<0){w+=x;x=0;} if(y<0){h+=y;y=0;}
    if(x+w>320)w=320-x;
    if(y+h>240)h=240-y;
    if(w>0&&h>0)eadk_display_push_rect_uniform((eadk_rect_t){x,y,w,h},color);
}
static void text(int x,int y,const char *s,uint16_t color) {
    if(s)platform_text(x,y,s,color,White,false,false,false);
}
static void math_text(int x,int y,const char *s,uint16_t ink,uint16_t paper,bool small) {
    platform_text(x,y,s,ink,paper,small,false,false);
}
static const MathCanvas canvas={math_text,rect,Ink,White};
static const Course *current_course(void) {return &courses[course];}
static const Chapter *current_chapter(void) {return &current_course()->chapters[chapter];}
static const Topic *current_topic(void) {return &current_chapter()->topics[topic];}
static void frame(const char *title,const char *hint) {
    rect(0,0,320,240,White);
    rect(0,0,320,22,Gold);
    text(7,7,title,Ink);
    if(second)text(263,7,"2ND",Ink);
    if(alpha||alpha_lock)text(294,7,"A",Ink);
    rect(0,222,320,18,Light);
    text(6,227,hint,Ink);
}
static void row(int y,int index,const char *label,bool active) {
    if(active)rect(3,y-3,314,LineHeight,FocusTint);
    char marker[4]={(char)(index<9?'1'+index:'A'+index-9),'.',0};
    if(index<35)text(8,y,marker,Blue);
    text(26,y,label,Ink);
}
static const char *detail_label(int i) {
    const Topic *t=current_topic();
    switch(i) {
        case 0:return "Course notes";
        case 1:return "Method";
        case 2:return "Worked example";
        case 3:return t->detail?t->detail->examples[0].title:"Extended notes";
        case 4:return t->detail?t->detail->examples[1].title:"More notes";
        default:return "Enter your values";
    }
}
static const char *match_title(int i) {
    return courses[matches[i].c].chapters[matches[i].h].topics[matches[i].t].title;
}
static unsigned next_line(const char *s) {
    int n=0,last=0,width=0;
    while(s[n]&&s[n]!='\n') {
        unsigned c=(unsigned char)s[n];
        if((c&0xc0)!=0x80) {
            if(width+platform_width(s+n,1,false,false)>304||n>=76)break;
            width+=platform_width(s+n,1,false,false);
        }
        if(s[n]==' ')last=n+1;
        n++;
    }
    if(s[n]&&s[n]!='\n'&&last>0)return last;
    return n+(s[n]=='\n');
}
static void paragraph(const char *s) {
    if(!s)s="No additional material for this topic.";
    for(int i=0;i<scroll&&*s;i++)s+=next_line(s);
    for(int i=0;i<13&&*s;i++) {
        unsigned count=next_line(s);
        char line[82];
        if(count&&s[count-1]=='\n')count--;
        memcpy(line,s,count);line[count]=0;
        text(8,29+i*14,line,Ink);
        s+=next_line(s);
    }
}
static int *selection(void) {
    switch(page) {
        case Courses:return &course;
        case Chapters:return &chapter;
        case Topics:return &topic;
        case Details:return &detail;
        case Operations:return &operation;
        case Matches:return &match;
        default:return NULL;
    }
}
static int list_count(void) {
    switch(page) {
        case Courses:return course_count;
        case Chapters:return current_course()->count;
        case Topics:return current_chapter()->count;
        case Details:return current_topic()->detail?6:3;
        case Operations:return OperationCount;
        case Matches:return match_count;
        default:return 0;
    }
}
static const char *list_label(int n) {
    switch(page) {
        case Courses:return courses[n].title;
        case Chapters:return current_course()->chapters[n].title;
        case Topics:return current_chapter()->topics[n].title;
        case Details:return detail_label(n);
        case Operations:return operation_names[n];
        case Matches:return match_title(n);
        default:return "";
    }
}
static int fields(void) {
    if(topic_form) {
        int n=0;
        while(n<MAX_FIELDS && current_topic()->labels[n])n++;
        return n?n:1;
    }
    return operation==Definite||operation==FindRoot?3:operation==Substitute?2:1;
}
static const char *field_label(int i) {
    if(topic_form && current_topic()->labels[i])return current_topic()->labels[i];
    if(i==0)return "Expression";
    if(operation==Substitute)return "Value of x";
    return i==1?"Lower bound":"Upper bound";
}
static void draw(void) {
    int *selected=selection();
    if(selected) {
        const char *titles[]={[Courses]="Courses",[Chapters]="Chapters",[Topics]="Topics",
                              [Details]="Topic menu",[Operations]="Equations and CAS",[Matches]="Search results"};
        frame(titles[page],"ARROWS: move   ENTER: open   CLEAR: back");
        int first=*selected/Rows*Rows;
        for(int i=first;i<first+Rows&&i<list_count();i++)
            row(31+(i-first)*LineHeight,i-first,list_label(i),i==*selected);
        if(!list_count())text(8,35,"No matches.",Ink);
        return;
    }
    switch(page) {
        case Home:
            frame("NumAI / TI-84 Plus CE","MATH: courses   VARS: CAS   MODE: exit");
            text(8,32,operation_names[operation],Blue);
            for(int i=0;i<fields();i++) {
                int y=48+(fields()==4?42:49)*i;
                text(8,y,field_label(i),Ink);
                rect(6,y+12,308,31,i==field?Light:White);
                int start=0;
                if(i==field)
                    while(start<cursor&&platform_width(input[i]+start,cursor-start,false,false)>286)start++;
                MathCaret caret=paint_math_input(input[i]+start,294,10,y+26,&canvas,i==field?cursor-start:0,false);
                if(i==field)rect(caret.x,caret.y,1,caret.height,Blue);
            }
            break;
        case Search:
            frame("Course search","ALPHA: letters   ENTER: search   DEL: edit");
            int start=0;
            while(start<cursor&&platform_width(query+start,cursor-start,false,false)>298)start++;
            text(8,41,query+start,Ink);
            rect(8+platform_width(query+start,cursor-start,false,false),39,1,11,Blue);
            break;
        case Reading:
            frame(read_title,"UP/DOWN: scroll   CLEAR: back");paragraph(last_read);break;
        case Result:
            frame("Result","ENTER: working   CLEAR: edit   2ND (-): Ans");
            if(result_math&&measure_math(result.answer,300).width<=300)
                paint_math(result.answer,300,10,66,&canvas);
            else paragraph(result.answer);
            break;
        case Working:
            frame("Working","UP/DOWN: scroll   CLEAR: back");paragraph(result.steps);break;
        case Settings:
            frame("Preferences","1: angle   2: format   CLEAR: back");
            text(8,35,degrees?"1. Degrees":"1. Radians",Ink);
            text(8,55,decimal?"2. Decimal answers":"2. Exact where available",Ink);
            text(8,83,"NumAI v" NUMAI_VERSION,Blue);
            text(8,108,"MATH Courses  VARS CAS  STAT Search",Ink);
            text(8,128,"Y= Fraction   WINDOW Working",Ink);
            text(8,148,"TRACE / GRAPH Previous / next page",Ink);
            text(8,168,"APPS Clear input   PRGM Absolute value",Ink);
            break;
        default:break;
    }
}
static void read_page(const char *title,const char *body) {
    reading_parent=page;read_title=title;last_read=body;scroll=0;page=Reading;
}
static bool contains(const char *s,const char *term) {
    if(!s)return false;
    for(;*s;s++) {
        unsigned i=0;
        while(term[i]&&s[i]&&((s[i]>='A'&&s[i]<='Z')?s[i]+32:s[i])==
              ((term[i]>='A'&&term[i]<='Z')?term[i]+32:term[i]))i++;
        if(!term[i])return true;
    }
    return false;
}
static void search(void) {
    match_count=match=0;
    if(*query)for(int pass=0;pass<2;pass++)
        for(int c=0;c<course_count;c++)for(int h=0;h<courses[c].count;h++) {
            const Chapter *ch=&courses[c].chapters[h];
            for(int t=0;t<ch->count&&match_count<40;t++) {
                const Topic *entry=&ch->topics[t];
                bool title=contains(entry->title,query);
                if(pass?title||!contains(entry->course,query):!title)continue;
                matches[match_count].c=c;matches[match_count].h=h;matches[match_count++].t=t;
            }
        }
    page=Matches;
}
static void choose(void) {
    switch(page) {
        case Courses:chapter=0;page=Chapters;break;
        case Chapters:topic=0;page=Topics;break;
        case Topics:detail=0;page=Details;break;
        case Matches:
            if(!match_count)break;
            course=matches[match].c;chapter=matches[match].h;topic=matches[match].t;
            detail=0;page=Details;break;
        case Details: {
            const Topic *t=current_topic();
            if(detail==0)read_page(t->title,t->detail?t->detail->notes:t->course);
            if(detail==1)read_page("Method",t->method);
            if(detail==2)read_page("Worked example",t->example);
            if(detail==3||detail==4)read_page(detail_label(detail),t->detail->examples[detail-3].working);
            if(detail==5) {
                topic_form=true;field=0;operation=t->operation;
                for(int i=0;i<MAX_FIELDS;i++)snprintf(input[i],sizeof(input[i]),"%s",t->values[i]?t->values[i]:"");
                cursor=strlen(input[0]);page=Home;
            }
            break;}
        case Operations:topic_form=false;field=0;cursor=strlen(input[0]);page=Home;break;
        default:break;
    }
}
static void insert(char *target,const char *value) {
    size_t size=strlen(value),len=strlen(target);
    if(size+len>=EXPRESSION_SIZE)return;
    memmove(target+cursor+size,target+cursor,len-cursor+1);
    memcpy(target+cursor,value,size);
    cursor+=size;
}
static void submit(void) {
    const char *formula=topic_form?current_topic()->formula:NULL;
    if(formula) {
        size_t used=0;
        for(;*formula;formula++) {
            char ch=*formula;
            if(ch=='$'&&formula[1]>='1'&&formula[1]<='0'+MAX_FIELDS) {
                const char *value=input[*++formula-'1'];
                size_t size=strlen(value);
                if(used+size+2>=sizeof(expression))return;
                expression[used++]='(';
                memcpy(expression+used,value,size);used+=size;expression[used++]=')';
            } else {
                if(used+1>=sizeof(expression))return;
                expression[used++]=ch;
            }
        }
        expression[used]=0;
    }else strcpy(expression,input[0]);
    if(!*expression)return;
    solve_expression(operation,expression,input[1],input[2],degrees,decimal,&result);
    result_math=false;
    if(operation==Calculate) {
        CalculationValue number;
        if(cas_calculation(expression,degrees,&number)&&number.numeric) {
            result_math=true;
            if(!decimal&&number.exact[0])snprintf(result.answer,sizeof(result.answer),"%s",number.exact);
            else number_text(result.answer,sizeof(result.answer),number.value,NumberGeneral,10);
            snprintf(ans,sizeof(ans),"(%s)",result.answer);
        }
    }
    strcpy(last_expression,input[0]);scroll=0;page=Result;
}
static const char *plain_key(int key,bool shift) {
    if(shift) switch(key) {
        case eadk_key_square:return "sqrt(";
        case eadk_key_sine:return "asin(";
        case eadk_key_cosine:return "acos(";
        case eadk_key_tangent:return "atan(";
        case eadk_key_power:return "pi";
        case eadk_key_log:return "10^(";
        case eadk_key_ln:return "exp(";
        case eadk_key_comma:return "*10^";
        case eadk_key_left_parenthesis:return "=";
        case eadk_key_plus:return "%";
        case eadk_key_multiplication:return "!";
        case eadk_key_pi:return ans;
        default:break;
    }
    static const char *const symbols[64]={
        [eadk_key_xnt]="x",[eadk_key_imaginary]="^(-1)",[eadk_key_exp]="abs(",
        [eadk_key_sine]="sin(",[eadk_key_cosine]="cos(",[eadk_key_tangent]="tan(",
        [eadk_key_square]="^2",[eadk_key_ln]="ln(",[eadk_key_log]="log(",
        [eadk_key_power]="^",[eadk_key_comma]=",",[eadk_key_pi]="-",
        [eadk_key_left_parenthesis]="(",[eadk_key_right_parenthesis]=")",
        [eadk_key_plus]="+",[eadk_key_minus]="-",[eadk_key_multiplication]="*",
        [eadk_key_division]="/",[eadk_key_fraction]="/",[eadk_key_dot]=".",
        [eadk_key_store]="->",
        [eadk_key_zero]="0",[eadk_key_one]="1",[eadk_key_two]="2",[eadk_key_three]="3",
        [eadk_key_four]="4",[eadk_key_five]="5",[eadk_key_six]="6",
        [eadk_key_seven]="7",[eadk_key_eight]="8",[eadk_key_nine]="9",
    };
    return symbols[key];
}
static void back(void) {
    switch(page) {
        case Home:input[field][0]=0;cursor=0;break;
        case Chapters:page=Courses;break;
        case Topics:page=Chapters;break;
        case Details:page=Topics;break;
        case Reading:page=reading_parent;break;
        case Operations:page=back_from_operations;break;
        case Working:page=Result;scroll=0;break;
        case Matches:page=Search;cursor=strlen(query);break;
        default:page=Home;cursor=strlen(input[field]);break;
    }
}
static void handle(int key) {
    bool had_alpha=alpha||alpha_lock;
    char letter=had_alpha?platform_alpha(key):0;
    bool shift=second;second=false;alpha=false;
    if(key==eadk_key_back){back();return;}
    if(key==eadk_key_xnt&&had_alpha) {
        page=Home;cursor=strlen(input[field]);return;
    }
    if(shift&&key==eadk_key_pi&&page==Result){
        page=Home;cursor=strlen(input[field]);insert(input[field],ans);return;
    }
    if(key==eadk_key_toolbox&&!letter){page=Courses;return;}
    if(key==eadk_key_var&&!letter){back_from_operations=page;page=Operations;return;}
    if(key==eadk_key_clear){page=Search;cursor=strlen(query);return;}
    if(key==eadk_key_settings||(shift&&key==eadk_key_exe)){page=Settings;return;}
    int *selected=selection();
    if(selected) {
        int count=list_count(), first=*selected/Rows*Rows;
        int offset=key==eadk_key_up?-1:key==eadk_key_down?1:
            key==eadk_key_prevtab?-Rows:key==eadk_key_nexttab?Rows:0;
        if(offset&&count) {
            *selected+=offset;
            if(*selected<0)*selected=0;
            if(*selected>=count)*selected=count-1;
        }
        if(key==eadk_key_exe||key==eadk_key_right)choose();
        else if(key==eadk_key_left)back();
        else if(count) {
            const char *value=plain_key(key,false);
            int i=letter>='A'&&letter<='B'?9+letter-'A':
                !letter&&value&&*value>='1'&&*value<='9'?*value-'1':-1;
            if(i>=0&&first+i<count){*selected=first+i;choose();}
        }
        return;
    }
    if(page==Reading||page==Result||page==Working) {
        const char *body=page==Reading?last_read:page==Result?result.answer:result.steps;
        if(key==eadk_key_exe||key==eadk_key_format) {
            if(page==Result){page=Working;scroll=0;}
            else if(page==Working){page=Result;scroll=0;}
        } else if(body) {
            int offset=key==eadk_key_up?-1:key==eadk_key_down?1:
                key==eadk_key_prevtab?-10:key==eadk_key_nexttab?10:0;
            if(offset<0)scroll=scroll+offset<0?0:scroll+offset;
            if(offset>0) {
                const char *at=body;
                for(int i=0;i<scroll&&*at;i++)at+=next_line(at);
                for(int i=0;i<offset&&*at;i++){
                    at+=next_line(at);
                    if(*at)scroll++;
                }
            }
        }
        return;
    }
    if(page==Settings) {
        if(key==eadk_key_one)degrees=!degrees;
        if(key==eadk_key_two)decimal=!decimal;
        return;
    }
    if(page==Home&&key==eadk_key_format){page=Result;scroll=0;return;}
    if(page==Home&&(key==eadk_key_up||key==eadk_key_down||key==eadk_key_prevtab||key==eadk_key_nexttab)) {
        if(fields()==1&&*last_expression)strcpy(input[0],last_expression);
        else if(fields()>1)field=(field+((key==eadk_key_up||key==eadk_key_prevtab)?fields()-1:1))%fields();
        cursor=strlen(input[field]);return;
    }
    if(key==eadk_key_exe){if(page==Search)search();else submit();return;}
    char *target=page==Search?query:input[field];
    if(key==eadk_key_left){if(cursor>0)cursor--;return;}
    if(key==eadk_key_right){if(target[cursor])cursor++;return;}
    if(key==eadk_key_backspace){
        if(cursor){memmove(target+cursor-1,target+cursor,strlen(target+cursor)+1);cursor--;}
        return;
    }
    if(key==eadk_key_variable){target[0]=0;cursor=0;return;}
    if(letter){char token[]={letter,0};insert(target,token);return;}
    const char *value=plain_key(key,shift);
    if(value)insert(target,value);
}
int main(void) {
    platform_init();
    if(!courses_load()) {
        frame("NumAI","MODE: exit");
        text(8,44,"Send the course pack to Archive.",Ink);
        eadk_timing_msleep(0);
        while(!eadk_keyboard_key_down(eadk_keyboard_scan(),eadk_key_home))eadk_timing_msleep(20);
        platform_end();return 1;
    }
    eadk_keyboard_state_t previous=eadk_keyboard_scan();
    draw();
    int repeat=-1, ticks=0;
    for(;;) {
        eadk_timing_msleep(15);
        eadk_keyboard_state_t state=eadk_keyboard_scan(), pressed=state&~previous;
        previous=state;
        if(repeat>=0&&eadk_keyboard_key_down(state,(eadk_key_t)repeat)) {
            if(++ticks>=22&&(ticks-22)%5==0)pressed|=UINT64_C(1)<<repeat;
        }else repeat=-1;
        if(!pressed)continue;
        if(eadk_keyboard_key_down(pressed,eadk_key_home))break;
        if(eadk_keyboard_key_down(pressed,eadk_key_shift))second=!second;
        if(eadk_keyboard_key_down(pressed,eadk_key_alpha)){
            if(second){alpha_lock=!alpha_lock;second=false;}
            else if(alpha_lock)alpha_lock=false;
            else alpha=!alpha;
        }
        for(int k=0;k<=eadk_key_last;k++)
            if(k!=eadk_key_shift&&k!=eadk_key_alpha&&eadk_keyboard_key_down(pressed,(eadk_key_t)k)) {
                handle(k);
                if(k<=eadk_key_right&&repeat!=k){repeat=k;ticks=0;}
            }
        draw();
    }
    platform_end();return 0;
}
