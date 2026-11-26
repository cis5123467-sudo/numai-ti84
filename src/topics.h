#ifndef NUMAI_TOPICS_H
#define NUMAI_TOPICS_H
#include "cas.h"

#define MAX_FIELDS 4
#define EXTRA_EXAMPLES 2

typedef struct { const char *title, *working; } WorkedExample;
typedef struct { const char *notes; WorkedExample examples[EXTRA_EXAMPLES]; } MathsDetail;
typedef struct {
    const char *title, *course, *method, *example;
    Operation operation;
    const char *formula;
    const char *labels[MAX_FIELDS], *values[MAX_FIELDS];
    MathsDetail *detail;
} Topic;

typedef struct { const char *title; Topic *topics; int count; } Chapter;
typedef struct { const char *title, *code; Chapter *chapters; int count; } Course;

extern Course courses[];
extern const int course_count;
bool courses_load(void);
#endif
