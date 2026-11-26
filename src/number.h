#ifndef LCD_NUMBER_H
#define LCD_NUMBER_H

#include <stddef.h>

typedef enum { NumberGeneral, NumberFixed, NumberScientific } NumberFormat;

void number_text(char *out, size_t capacity, long double value,
                 NumberFormat format, int precision);

#endif
