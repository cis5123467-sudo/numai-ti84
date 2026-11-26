#ifndef NUMAI_CAS_H
#define NUMAI_CAS_H
#include <stdbool.h>

#define EXPRESSION_SIZE 112
#define ANSWER_SIZE 512

typedef enum {
    Calculate, Factorise, Simplify, Expand, Solve, Differentiate,
    Integrate, Definite, Substitute, FindRoot, CompleteSquare, OperationCount
} Operation;

typedef struct {
    char steps[ANSWER_SIZE];
    char answer[ANSWER_SIZE];
    bool ok;
} Solution;

typedef enum { ExtraNone, ExtraRoot, ExtraSin, ExtraCos, ExtraTan } CalculationKind;
typedef struct {
    long double value, argument;
    long numerator, denominator, radicand, argument_n, argument_d, argument_rad;
    CalculationKind kind;
    bool numeric, degrees, syntax_valid;
    char exact[64];
} CalculationValue;

enum { CAS_VARIABLE_COUNT = 52 };
typedef struct {
    long double value[CAS_VARIABLE_COUNT];
    bool set[CAS_VARIABLE_COUNT];
} CasVariables;

void cas_set_gradians(bool enabled);
void cas_get_variables(CasVariables *variables);
void cas_set_variables(const CasVariables *variables);

extern const char *const operation_names[OperationCount];
bool cas_read_number(const char *input, long double *value);
bool cas_calculation(const char *input, bool degrees, CalculationValue *result);
void cas_trig_equation(const char *input, const char *lower, const char *upper,
                       bool degrees, Solution *solution);
void solve_expression(Operation operation, const char *expression, const char *second,
                      const char *third, bool degrees, bool decimal, Solution *solution);

#endif
