#include "cas.h"
#include "number.h"

#include <ctype.h>
#include <math.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NODE_LIMIT 320
#define DEGREE 12
#define PI 3.14159265358979323846L
#define NO_NODE 0

typedef enum {
    Number, Variable, Add, Sub, Mul, Div, Pow, Sin, Cos, Tan, Exp, Ln, Log,
    Sqrt, Abs, Asin, Acos, Atan, Choose, Permute, Binomial, Normal, Floor, Gcd, Min, Factorial, Cbrt, Sinh, Cosh, Tanh, Asinh, Acosh, Atanh, Ceil, Round, Max, Lcm, Mod, LogBase, Root, Mixed, AngleRad, AngleDegree
} Kind;

typedef struct {
    long double value;
    unsigned short left, right, literal_length;
    Kind kind;
    unsigned char literal_kind;
} Node;
typedef unsigned short Expr;
typedef struct { long double c[DEGREE + 1]; int degree; } Poly;
typedef struct { const char *input; bool invalid; } Parser;
typedef struct { char *text; size_t capacity, length; } Writer;

const char *const operation_names[] = {
    "Calculate", "Factorise", "Simplify", "Expand", "Solve for x",
    "Differentiate", "Integrate", "Definite integral", "Substitute x", "Root in an interval",
    "Complete the square"
};

static Node nodes[NODE_LIMIT];
static const char *number_tokens[NODE_LIMIT];
static Expr used;
static bool too_complex, radians, gradians;
void cas_set_gradians(bool enabled) { gradians=enabled; }
static CasVariables stored_variables;

void cas_get_variables(CasVariables *variables) { *variables = stored_variables; }
void cas_set_variables(const CasVariables *variables) { stored_variables = *variables; }

static int variable_index(char ch) {
    if (ch >= 'a' && ch <= 'z') return ch - 'a';
    if (ch >= 'A' && ch <= 'Z') return 26 + ch - 'A';
    return -1;
}
static const struct { const char *name; Kind kind; int arity; } functions[] = {
    {"sin", Sin, 1}, {"cos", Cos, 1}, {"tan", Tan, 1}, {"exp", Exp, 1},
    {"ln", Ln, 1}, {"log", Log, 1}, {"sqrt", Sqrt, 1}, {"abs", Abs, 1},
    {"asin", Asin, 1}, {"acos", Acos, 1}, {"atan", Atan, 1},
    {"ncr", Choose, 2}, {"npr", Permute, 2}, {"binom", Binomial, 3},
    {"norm", Normal, 1}, {"floor", Floor, 1}, {"gcd", Gcd, 2}, {"min", Min, 2}, {"cbrt", Cbrt, 1}, {"sinh", Sinh, 1}, {"cosh", Cosh, 1}, {"tanh", Tanh, 1},
    {"asinh", Asinh, 1}, {"acosh", Acosh, 1}, {"atanh", Atanh, 1}, {"ceil", Ceil, 1},
    {"round", Round, 1}, {"max", Max, 2}, {"lcm", Lcm, 2}, {"mod", Mod, 2},
    {"logb", LogBase, 2}, {"root", Root, 2}, {"mixed", Mixed, 3}
};

static Expr make(Kind kind, Expr left, Expr right, long double value) {
    if (used == NODE_LIMIT - 1) {
        too_complex = true;
        return NO_NODE;
    }
    nodes[++used] = (Node){.value=value,.left=left,.right=right,.kind=kind};
    return used;
}

static Expr number(long double value) { return make(Number, 0, 0, value); }
static bool is_number(Expr expr, long double value) {
    return expr && nodes[expr].kind == Number && nodes[expr].value == value;
}

static long double numeric(Kind kind, long double a, long double b, long double c) {
    long double angle = radians ? 1 : PI / (gradians ? 200 : 180);
    switch (kind) {
        case Add: return a + b;
        case Sub: return a - b;
        case Mul: return a * b;
        case Div: return a / b;
        case Pow: return powl(a, b);
        case Factorial: {
            if (!isfinite(a) || a < 0 || a > 170 || a != floorl(a)) return NAN;
            long double product = 1;
            for (int i = 2; i <= (int)a; i++) product *= i;
            return product;
        }
        case Sin: return sinl(a * angle);
        case Cos: return cosl(a * angle);
        case Tan: {
            long double t = a * angle;
            return fabsl(cosl(t)) < 1e-14L ? NAN : tanl(t);
        }
        case Exp: return expl(a);
        case Ln: return logl(a);
        case Log: return log10l(a);
        case Sqrt: return sqrtl(a);
        case AngleRad: return a*(radians?1:(gradians?200:180)/PI);
        case AngleDegree: return a*(radians?PI/180:gradians?200.0L/180:1);
        case Mixed:
            if(a!=truncl(a)||b<0||b!=truncl(b)||c<=0||c!=truncl(c))return NAN;
            return a+(a<0?-1:1)*b/c;
        case Cbrt: return cbrtl(a);
        case Sinh: return sinhl(a);
        case Cosh: return coshl(a);
        case Tanh: return tanhl(a);
        case Asinh: return asinhl(a);
        case Acosh: return acoshl(a);
        case Atanh: return atanhl(a);
        case Ceil: return ceill(a);
        case Round: return roundl(a);
        case Max: return isfinite(a) && isfinite(b) ? fmaxl(a,b) : NAN;
        case Lcm: { long double g=numeric(Gcd,a,b,0); return g==0?0:fabsl(a/g*b); }
        case Mod: return fmodl(a,b);
        case LogBase: return a>0 && b>0 && b!=1 ? logl(a)/logl(b) : NAN;
        case Root:
            if(b==0) return NAN;
            if(a<0) return b==truncl(b) && fmodl(fabsl(b),2)==1 ? -powl(-a,1/b) : NAN;
            return powl(a,1/b);
        case Abs: return fabsl(a);
        case Min: return isfinite(a) && isfinite(b) ? fminl(a, b) : NAN;
        case Asin: return asinl(a) / angle;
        case Acos: return acosl(a) / angle;
        case Atan: return atanl(a) / angle;
        case Floor: return floorl(a);
        case Normal: return erfcl(-a / sqrtl(2)) / 2;
        case Choose: case Permute: case Binomial: {
            if (!(a >= 0 && a <= 1024 && b >= 0 && b <= a) ||
                a != floorl(a) || b != floorl(b)) return NAN;
            int terms = (int)b;
            if (kind != Permute && b > a - b) terms = (int)(a - b);
            long double result = 1;
            for (int i = 1; i <= terms; i++) {
                result *= (a - i + 1) / (kind == Permute ? 1 : i);
            }
            if (kind != Binomial) return result;
            if (!(c >= 0 && c <= 1)) return NAN;
            return result * powl(c, b) * powl(1 - c, a - b);
        }
        case Gcd:
            if (!isfinite(a) || !isfinite(b) || a != truncl(a) || b != truncl(b)) return NAN;
            a = fabsl(a);
            b = fabsl(b);
            while (b != 0) {
                long double rem = fmodl(a, b);
                a = b;
                b = rem;
            }
            return a;
        default: return NAN;
    }
}

static Expr binary(Kind kind, Expr a, Expr b) {
    if (!a || !b) return NO_NODE;
    bool a0 = is_number(a, 0), b0 = is_number(b, 0);
    bool a1 = is_number(a, 1), b1 = is_number(b, 1);
    if ((kind == Add || kind == Sub) && b0) return a;
    if (kind == Add && a0) return b;
    if (kind == Mul && (a0 || b0)) return a0 ? a : b;
    if (kind == Mul && a1) return b;
    if ((kind == Mul || kind == Div || kind == Pow) && b1) return a;
    if (kind == Pow && b0) return number(1);
    if (nodes[a].kind == Number && nodes[b].kind == Number) {
        long double value = numeric(kind, nodes[a].value, nodes[b].value, 0);
        if (isfinite(value)) return number(value);
    }
    return make(kind, a, b, 0);
}

static void spaces(Parser *p) { while (isspace((unsigned char)*p->input)) p->input++; }
static bool take(Parser *p, char ch) {
    spaces(p);
    if (*p->input != ch) return false;
    p->input++;
    return true;
}

static Expr expression(Parser *p);

static Expr atom(Parser *p) {
    spaces(p);
    if (take(p, '(')) {
        Expr e = expression(p);
        if (!take(p, ')')) p->invalid = true;
        return e;
    }
    const char *start = p->input;
    if (start[0] == '0' && (start[1] == 'b' || start[1] == 'B')) {
        const char *end = start+2;
        long double value = 0;
        while (*end == '0' || *end == '1') value = 2*value + *end++ - '0';
        if (end != start+2 && isfinite(value)) {
            p->input = end;
            return number(value);
        }
    }
    if (isdigit((unsigned char)*start) || *start == '.') {
        char *end;
        long double value = strtold(start, &end);
        if (end != start && isfinite(value)) {
            p->input = end;
            if (end > start+2 && start[0] == '0' && (start[1] == 'x' || start[1] == 'X'))
                return number(value);
            Expr e = number(value);
            if (e) {
                number_tokens[e] = start;
                nodes[e].literal_length = (unsigned short)(end-start);
            }
            return e;
        }
    }
    if (*start == 'x') {
        p->input++;
        if(stored_variables.set[26+'X'-'A']) {Expr e=number(stored_variables.value[26+'X'-'A']);if(e)nodes[e].literal_kind=2;return e;}
        return make(Variable,0,0,0);
    }
    if (strncmp(start, "pi", 2) == 0) {
        p->input += 2;
        Expr e = number(PI);
        if (e) nodes[e].literal_kind=1;
        return e;
    }
    if (*start == 'e' && strncmp(start, "exp", 3) != 0) {
        p->input++;
        Expr e = number(expl(1));
        if (e) nodes[e].literal_kind=2;
        return e;
    }
    for (size_t i = 0; i < sizeof(functions) / sizeof(*functions); i++) {
        size_t len = strlen(functions[i].name);
        if (strncmp(start, functions[i].name, len) != 0 || start[len] != '(') continue;
        p->input += len + 1;
        Expr first = expression(p), second = 0;
        if (functions[i].arity > 1) {
            if (!take(p, ',')) p->invalid = true;
            second = expression(p);
        }
        if (functions[i].arity > 2) {
            if (!take(p, ',')) p->invalid = true;
            second = make(Add, second, expression(p), 0);
        }
        if (!take(p, ')')) p->invalid = true;
        return make(functions[i].kind, first, second, 0);
    }
    int index = variable_index(*start);
    if (index >= 0 && stored_variables.set[index]) {
        p->input++;
        Expr e = number(stored_variables.value[index]);
        if (e) nodes[e].literal_kind=2;
        return e;
    }
    p->invalid = true;
    return NO_NODE;
}

static Expr unary(Parser *p) {
    if (take(p, '+')) return unary(p);
    if (take(p, '-')) return make(Sub, number(0), unary(p), 0);
    Expr base = atom(p);
    while (!p->invalid) {
        if (take(p, '!')) base = make(Factorial, base, 0, 0);
        else if (take(p, '%')) base = make(Div, base, number(100), 0);
        else if(take(p,21))base=make(AngleRad,base,0,0);
        else if(take(p,24)) {
            Expr degrees=base;
            if(isdigit((unsigned char)*p->input)) {
                Expr minutes=atom(p);if(!take(p,24))p->invalid=true;
                degrees=make(Add,degrees,make(Div,minutes,number(60),0),0);
                if(isdigit((unsigned char)*p->input)) {
                    Expr seconds=atom(p);if(!take(p,24))p->invalid=true;
                    degrees=make(Add,degrees,make(Div,seconds,number(3600),0),0);
                }
            }
            base=make(AngleDegree,degrees,0,0);
        }
        else break;
    }
    if (take(p, '^')) return make(Pow, base, unary(p), 0);
    return base;
}

static Expr product(Parser *p) {
    Expr left = unary(p);
    while (!p->invalid) {
        spaces(p);
        if (take(p, '*')) left = make(Mul, left, unary(p), 0);
        else if (take(p, '/')) left = make(Div, left, unary(p), 0);
        else if (*p->input == '(' || isalpha((unsigned char)*p->input))
            left = make(Mul, left, unary(p), 0);
        else break;
    }
    return left;
}

static Expr expression(Parser *p) {
    Expr left = product(p);
    while (!p->invalid) {
        if (take(p, '+')) left = make(Add, left, product(p), 0);
        else if (take(p, '-')) left = make(Sub, left, product(p), 0);
        else break;
    }
    return left;
}

static Expr parse(const char *text, bool equation) {
    if (!text || strlen(text) >= EXPRESSION_SIZE * 4) return NO_NODE;
    // Bound the parser and tree-walking stack for deeply nested input.
    int depth = 0, operators = 0;
    for (const char *c = text; *c; c++) {
        if (*c == '(' && ++depth > 18) return NO_NODE;
        if (*c == ')') depth--;
        if (strchr("+-*/^(!", *c) && ++operators > 50) return NO_NODE;
    }
    Parser p = {text, false};
    Expr result = expression(&p);
    if (equation && take(&p, '=')) result = make(Sub, result, expression(&p), 0);
    spaces(&p);
    return p.invalid || *p.input || too_complex ? NO_NODE : result;
}

static long double evaluate(Expr e, long double x) {
    if (!e) return NAN;
    Node node = nodes[e];
    if (node.kind == Number) return node.value;
    if (node.kind == Variable) return x;
    long double a = evaluate(node.left, x);
    if (node.kind == Binomial || node.kind == Mixed) {
        Node pair = nodes[node.right];
        return numeric(node.kind, a, evaluate(pair.left, x), evaluate(pair.right, x));
    }
    return numeric(node.kind, a, node.right ? evaluate(node.right, x) : 0, 0);
}

static bool constant(Expr e) {
    if (!e) return false;
    Node n = nodes[e];
    if (n.kind == Number) return true;
    return n.kind != Variable && constant(n.left) && (!n.right || constant(n.right));
}

static void trim(Poly *p) {
    while (p->degree > 0 && p->c[p->degree] == 0) p->degree--;
}

static bool multiply(const Poly *a, const Poly *b, Poly *result) {
    if (a->degree + b->degree > DEGREE) return false;
    *result = (Poly){.degree = a->degree + b->degree};
    for (int i = 0; i <= a->degree; i++)
        for (int j = 0; j <= b->degree; j++) result->c[i + j] += a->c[i] * b->c[j];
    trim(result);
    return true;
}

static bool polynomial(Expr e, Poly *p) {
    if (!e) return false;
    Node n = nodes[e];
    // Use the output as scratch for the left branch to limit stack usage.
    if (n.kind == Variable) {
        *p = (Poly){.c = {0, 1}, .degree = 1};
        return true;
    }
    if (constant(e)) {
        long double value = evaluate(e, 0);
        if (!isfinite(value)) return false;
        *p = (Poly){.c = {value}};
        return true;
    }
    if (n.kind > Pow || !polynomial(n.left, p)) return false;
    if (n.kind == Pow || n.kind == Div) {
        long double value = evaluate(n.right, NAN);
        if (!isfinite(value)) return false;
        if (n.kind == Div) {
            if (!value) return false;
            for (int i = 0; i <= p->degree; i++) p->c[i] /= value;
            return true;
        }
        if (value < 0 || value > DEGREE || value != floorl(value)) return false;
        Poly base = *p, next;
        *p = (Poly){.c = {1}};
        for (int i = 0; i < (int)value; i++) {
            if (!multiply(p, &base, &next)) return false;
            *p = next;
        }
        return true;
    }
    Poly right;
    if (!polynomial(n.right, &right)) return false;
    if (n.kind == Mul) {
        Poly next;
        if (!multiply(p, &right, &next)) return false;
        *p = next;
    } else {
        if (right.degree > p->degree) p->degree = right.degree;
        for (int i = 0; i <= right.degree; i++) {
            long double previous = p->c[i];
            p->c[i] += n.kind == Add ? right.c[i] : -right.c[i];
            if (isfinite(previous) && fabsl(p->c[i]) < fabsl(previous) * 8e-16L) p->c[i] = 0;
        }
        trim(p);
    }
    return true;
}

static bool finite_poly(const Poly *p) {
    for (int i = 0; i <= p->degree; i++) if (!isfinite(p->c[i])) return false;
    return true;
}

static void append(Writer *out, const char *text) {
    size_t len = strlen(text), remaining = out->capacity - out->length - 1;
    if (len > remaining) len = remaining;
    memcpy(out->text + out->length, text, len);
    out->length += len;
    out->text[out->length] = 0;
}

static void print(Writer *out, const char *format, ...) {
    char temp[80];
    va_list args;
    va_start(args, format);
    vsnprintf(temp, sizeof(temp), format, args);
    va_end(args);
    append(out, temp);
}

static bool fraction(long double value, long *num, long *den) {
    if (!isfinite(value) || fabsl(value) > 1e7L || (value != 0 && fabsl(value) < 1e-6L)) return false;
    for (int d = 1; d <= 999; d++) {
        long double n = roundl(value * d);
        if (fabsl(value - n / d) <= fabsl(value) * 2e-15L && fabsl(n) < 2e9L) {
            *num = (long)n;
            *den = d;
            return true;
        }
    }
    return false;
}

static void value_text(Writer *out, long double value, bool decimal) {
    long n, d;
    if (!decimal && fraction(value, &n, &d) && d != 1) print(out, "%ld/%ld", n, d);
    else {
        char text[40];
        number_text(text,sizeof(text),value,NumberGeneral,10);
        append(out,text);
    }
}

static void poly_text_variable(Writer *out, const Poly *p, char variable) {
    bool first = true;
    for (int i = p->degree; i >= 0; i--) {
        long double c = p->c[i];
        if (!c) continue;
        if (c < 0) append(out, first ? "-" : " - ");
        else if (!first) append(out, " + ");
        if (!i || fabsl(c) != 1) {
            value_text(out, fabsl(c), false);
            if (i) append(out, "*");
        }
        if (i) print(out, "%c", variable);
        if (i > 1) print(out, "^%d", i);
        first = false;
    }
    if (first) append(out, "0");
}

static void poly_text(Writer *out, const Poly *p) { poly_text_variable(out,p,'x'); }

static int precedence(Kind k) {
    if (k == Add || k == Sub) return 1;
    if (k == Mul || k == Div) return 2;
    if (k == Pow) return 3;
    return 4;
}

static void expr_text(Writer *out, Expr e, int level) {
    if (!e || out->length == out->capacity - 1) return;
    Node n = nodes[e];
    int prec = precedence(n.kind);
    long num, den;
    if (n.kind == Number && fraction(n.value, &num, &den) && den != 1) prec = 2;
    else if (n.kind == Number && n.value < 0) prec = 2;
    if (prec < level) append(out, "(");
    if (n.kind == Number) value_text(out, n.value, false);
    else if (n.kind == Variable) append(out, "x");
    else if (n.kind == Factorial) {
        expr_text(out, n.left, prec);
        append(out, "!");
    } else if (n.kind <= Pow) {
        static const char *const operators[] = {" + ", " - ", "*", "/", "^"};
        if (n.kind == Sub && is_number(n.left, 0)) append(out, "-");
        else {
            expr_text(out, n.left, prec + (n.kind == Pow));
            append(out, operators[n.kind - Add]);
        }
        expr_text(out, n.right, prec + (n.kind == Div || n.kind == Sub));
    } else {
        for (size_t i = 0; i < sizeof(functions) / sizeof(*functions); i++) {
            if (functions[i].kind != n.kind) continue;
            append(out, functions[i].name);
            append(out, "(");
            expr_text(out, n.left, 0);
            if (functions[i].arity == 2) {
                append(out, ",");
                expr_text(out, n.right, 0);
            } else if (functions[i].arity == 3) {
                append(out, ",");
                expr_text(out, nodes[n.right].left, 0);
                append(out, ",");
                expr_text(out, nodes[n.right].right, 0);
            }
            append(out, ")");
            break;
        }
    }
    if (prec < level) append(out, ")");
}

static Expr derivative(Expr e) {
    if (!e || too_complex) return NO_NODE;
    if (constant(e)) return isfinite(evaluate(e, 0)) ? number(0) : NO_NODE;
    Node n = nodes[e];
    if (n.kind == Variable) return number(1);
    Expr a = n.left, b = n.right, da = derivative(a);
    if (!da) return NO_NODE;
    switch (n.kind) {
        case Add: case Sub: return binary(n.kind, da, derivative(b));
        case Mul: return binary(Add, binary(Mul, da, b), binary(Mul, a, derivative(b)));
        case Div:
            return binary(Div, binary(Sub, binary(Mul, da, b), binary(Mul, a, derivative(b))),
                          binary(Pow, b, number(2)));
        case Pow:
            if (constant(b) && isfinite(evaluate(b, 0))) {
                long double power = evaluate(b, 0);
                return binary(Mul, binary(Mul, number(power), binary(Pow, a, number(power - 1))), da);
            }
            return binary(Mul, e, binary(Add, binary(Mul, derivative(b), make(Ln, a, 0, 0)),
                                           binary(Div, binary(Mul, b, da), a)));
        case Sin: case Cos: case Tan: {
            Expr outer = make(n.kind == Cos ? Sin : Cos, a, 0, 0);
            if (n.kind == Cos) outer = binary(Mul, number(-1), outer);
            if (n.kind == Tan) outer = binary(Div, number(1), binary(Pow, outer, number(2)));
            if (!radians) da = binary(Mul, number(PI / 180), da);
            return binary(Mul, outer, da);
        }
        case Exp: return binary(Mul, e, da);
        case Ln: return binary(Div, da, a);
        case Log: return binary(Div, da, binary(Mul, number(logl(10)), a));
        case Sqrt: return binary(Div, da, binary(Mul, number(2), e));
        default: return NO_NODE;
    }
}

static Expr primitive(Expr e) {
    if (!e || too_complex) return NO_NODE;
    Poly p;
    if (polynomial(e, &p) && finite_poly(&p)) {
        Expr sum = number(0), x = make(Variable, 0, 0, 0);
        for (int i = p.degree; i >= 0; i--) {
            if (!p.c[i]) continue;
            Expr term = binary(Mul, number(p.c[i] / (i + 1)), binary(Pow, x, number(i + 1)));
            sum = binary(Add, sum, term);
        }
        return sum;
    }
    Node n = nodes[e];
    Expr a = n.left, b = n.right;
    if (n.kind == Add || n.kind == Sub)
        return binary(n.kind, primitive(a), primitive(b));
    if (n.kind == Mul) {
        if (constant(a)) return binary(Mul, a, primitive(b));
        if (constant(b)) return binary(Mul, b, primitive(a));
    }
    if (n.kind == Div && constant(b) && evaluate(b, 0) != 0)
        return binary(Div, primitive(a), b);

    Expr arg = n.kind == Div ? b : a;
    Poly inner;
    if (!polynomial(arg, &inner) || inner.degree != 1) return NO_NODE;
    long double slope = inner.c[1];
    Expr outer;
    if (n.kind == Exp) outer = e;
    else if (n.kind == Sin || n.kind == Cos) {
        outer = make(n.kind == Sin ? Cos : Sin, arg, 0, 0);
        if (n.kind == Sin) outer = binary(Mul, number(-1), outer);
        if (!radians) slope *= PI / 180;
    } else if (n.kind == Div && constant(a)) {
        outer = binary(Mul, a, make(Ln, make(Abs, arg, 0, 0), 0, 0));
    } else if ((n.kind == Pow && constant(b)) || n.kind == Sqrt) {
        long double power = n.kind == Sqrt ? 0.5L : evaluate(b, 0);
        if (!isfinite(power)) return NO_NODE;
        if (power == -1) outer = make(Ln, make(Abs, arg, 0, 0), 0, 0);
        else {
            outer = binary(Pow, arg, number(power + 1));
            slope *= power + 1;
        }
    } else return NO_NODE;
    return binary(Div, outer, number(slope));
}

static long double poly_value(const Poly *p, long double x) {
    long double value = p->c[p->degree];
    for (int i = p->degree - 1; i >= 0; i--) value = value * x + p->c[i];
    return value;
}

static unsigned long gcd(unsigned long a, unsigned long b) {
    while (b) { unsigned long r = a % b; a = b; b = r; }
    return a;
}

static int divisors(int n, int values[128]) {
    int count = 0;
    for (int k = 1; k*k <= n; k++) {
        if (n % k) continue;
        values[count++] = k;
        if (n / k != k) values[count++] = n / k;
    }
    return count;
}

static bool rational_root(const Poly *p, long double *root) {
    if (p->c[0] == 0) { *root = 0; return true; }
    long double lead = fabsl(p->c[p->degree]), tail = fabsl(p->c[0]);
    if (lead > 20000 || tail > 20000 || lead != roundl(lead) || tail != roundl(tail)) return false;
    int numerators[128], denominators[128];
    int numerator_count = divisors((int)tail, numerators);
    int denominator_count = divisors((int)lead, denominators);
    for (int i = 0; i < numerator_count; i++) {
        int n = numerators[i];
        for (int j = 0; j < denominator_count; j++) {
            int d = denominators[j];
            if (gcd(n, d) != 1) continue;
            for (int sign = -1; sign <= 1; sign += 2) {
                long double x = (long double)(sign * n) / d;
                long double magnitude = 0;
                for (int i = p->degree; i >= 0; i--) magnitude = magnitude * fabsl(x) + fabsl(p->c[i]);
                if (fabsl(poly_value(p, x)) <= magnitude * 2e-15L && isfinite(magnitude)) {
                    *root = x;
                    return true;
                }
            }
        }
    }
    return false;
}

static Poly remove_root(const Poly *p, long n, long d) {
    Poly q = {.degree = p->degree - 1};
    q.c[q.degree] = p->c[p->degree] / d;
    for (int i = q.degree - 1; i >= 0; i--)
        q.c[i] = (p->c[i + 1] + n * q.c[i + 1]) / d;
    return q;
}

static unsigned long integer_content(const Poly *p) {
    unsigned long content = 0;
    for (int i = 0; i <= p->degree; i++) {
        long double value = fabsl(p->c[i]);
        if (value > 1e8L || value != floorl(value)) return 1;
        content = gcd(content, (unsigned long)value);
    }
    return content ? content : 1;
}

static bool integer_form(Poly *p, long double *scale) {
    long numerators[DEGREE + 1], denominators[DEGREE + 1];
    unsigned long lcm = 1;
    for (int i = 0; i <= p->degree; i++) {
        if (!fraction(p->c[i], &numerators[i], &denominators[i])) return false;
        unsigned long d = (unsigned long)denominators[i];
        lcm *= d / gcd(lcm, d);
        if (lcm > 1000000) return false;
    }
    for (int i = 0; i <= p->degree; i++)
        p->c[i] = (long double)numerators[i] * (lcm / (unsigned long)denominators[i]);
    unsigned long content = integer_content(p);
    *scale = (long double)content / lcm;
    for (int i = 0; i <= p->degree; i++) p->c[i] /= content;
    return true;
}

static void factor_text(Writer *out, long double root) {
    long n, d;
    if (root == 0) { append(out, "(x)"); return; }
    if (!fraction(root, &n, &d)) return;
    append(out, "(");
    if (d != 1) print(out, "%ld", d);
    print(out, "x %c %ld)", n < 0 ? '+' : '-', labs(n));
}

static void quadratic(Writer *out, Writer *steps, const Poly *p, bool decimal, bool prefix) {
    long double a = p->c[2], b = p->c[1], c = p->c[0];
    long double disc = b*b - 4*a*c;
    append(steps, "\nUse x = (-b +/- sqrt(D))/(2a).\nD = b^2 - 4ac = ");
    value_text(steps, disc, false);
    if (!isfinite(disc)) { append(out, "Coefficients out of range"); return; }
    if (disc < 0) {
        append(out, prefix ? " (no further real roots)" : "No real solutions");
        return;
    }
    if (prefix) append(out, ", ");
    long double s = sqrtl(disc);
    append(out, "x = ");
    if (!decimal && disc == floorl(disc) && disc <= 1e7L && s != floorl(s) &&
        a == truncl(a) && b == truncl(b) && fabsl(a) <= 1e7L && fabsl(b) <= 1e7L) {
        unsigned long radicand = (unsigned long)disc, outside = 1;
        for (unsigned long i = 2; i*i <= radicand; i++) {
            while (radicand % (i*i) == 0) { radicand /= i*i; outside *= i; }
        }
        long centre = (long)(a < 0 ? b : -b), denominator = (long)fabsl(2*a);
        unsigned long common = gcd(gcd((unsigned long)labs(centre), outside), (unsigned long)denominator);
        centre /= (long)common;
        outside /= common;
        denominator /= (long)common;
        if (denominator != 1) append(out, "(");
        if (centre) print(out, "%ld +/- ", centre);
        else append(out, "+/- ");
        if (outside != 1) print(out, "%lu*", outside);
        print(out, "sqrt(%lu)", radicand);
        if (denominator != 1) print(out, ")/%ld", denominator);
        return;
    }
    long double q = -0.5L * (b + copysignl(s, b));
    long double first = disc == 0 ? -b/(2*a) : q/a;
    long double other = q == 0 ? first : c/q;
    if (disc > 0 && other < first) { long double temp = first; first = other; other = temp; }
    bool approximate = disc > 0 && s != floorl(s);
    if (approximate) append(out, "approx. ");
    value_text(out, first, decimal || approximate);
    if (disc > 0) {
        append(out, ", ");
        value_text(out, other, decimal || approximate);
    }
}

static bool complete_square(const Poly *p, bool equation, Writer *out, Writer *steps) {
    if (p->degree != 2) return false;
    long double a = p->c[2], c = p->c[0];
    long double h = (p->c[1] * 0.5L) / a;
    long double k = fmal(-p->c[1] * 0.5L, h, c);
    if (!isfinite(h) || !isfinite(k)) return false;

    append(steps, equation ? "Bring all terms to one side:\n" : "Write as ax^2 + bx + c:\n");
    poly_text(steps, p);
    if (equation) append(steps, " = 0");
    append(steps, "\nHalf the x coefficient inside the bracket:\nh = b/(2a) = ");
    value_text(steps, h, false);
    append(steps, "\nAdjust the constant: c - a*h^2 = ");
    value_text(steps, k, false);

    if (a == -1) append(out, "-");
    else if (a != 1) {
        value_text(out, a, false);
        append(out, "*");
    }
    if (h) {
        append(out, h > 0 ? "(x + " : "(x - ");
        value_text(out, fabsl(h), false);
        append(out, ")^2");
    } else append(out, "x^2");
    if (k) {
        append(out, k > 0 ? " + " : " - ");
        value_text(out, fabsl(k), false);
    }
    if (equation) append(out, " = 0");
    return true;
}

static void algebra(Operation operation, Poly p, Writer *out, Writer *steps, bool decimal) {
    if (operation == Simplify || operation == Expand) {
        append(steps, "Expand brackets using distribution.\nCollect coefficients of each power of x.");
        poly_text(out, &p);
        return;
    }
    append(steps, operation == Solve ? "Bring all terms to one side.\n" : "Collect like terms.\n");
    poly_text(steps, &p);
    if (operation == Solve) append(steps, " = 0");
    Poly remainder = p;
    long double scale = 1;
    if (p.degree > 0) integer_form(&remainder, &scale);
    if (operation == Solve && scale != 1) {
        append(steps, "\nDivide through by the common coefficient:\n");
        poly_text(steps, &remainder);
        append(steps, " = 0");
    }
    long double roots[DEGREE];
    int count = 0;
    while (remainder.degree >= (operation == Solve ? 3 : 1)) {
        long double root;
        if (remainder.degree == 1) root = -remainder.c[0] / remainder.c[1];
        else if (!rational_root(&remainder, &root)) break;
        long n, d;
        if (!fraction(root, &n, &d)) break;
        roots[count++] = root;
        remainder = remove_root(&remainder, n, d);
    }
    if (operation == Factorise) {
        if (!count && scale == 1) {
            append(steps, "\nNo rational linear factor found within the search range.");
            poly_text(out, &p);
            return;
        }
        if (scale != 1) append(steps, "\nTake out the common coefficient.");
        if (count) append(steps, "\nUse the factor theorem and divide out each linear factor.");
        append(steps, "\nRemaining factor: ");
        poly_text(steps, &remainder);
        if (remainder.degree == 0) scale *= remainder.c[0];
        if (scale != 1) {
            value_text(out, scale, false);
            append(out, "*");
        }
        for (int i = 0; i < count; i++) factor_text(out, roots[i]);
        if (remainder.degree) {
            append(out, "(");
            poly_text(out, &remainder);
            append(out, ")");
        }
        return;
    }
    if (count) {
        append(steps, "\nFind rational roots by the factor theorem.\nSolve the remaining equation:\n");
        poly_text(steps, &remainder);
        append(steps, " = 0");
        append(out, "x = ");
        for (int i = 0; i < count; i++) {
            bool duplicate = false;
            for (int j = 0; j < i; j++) if (roots[j] == roots[i]) duplicate = true;
            if (duplicate) continue;
            if (i) append(out, ", ");
            value_text(out, roots[i], decimal);
        }
    }
    if (remainder.degree == 2) quadratic(out, steps, &remainder, decimal, count > 0);
    else if (remainder.degree == 1) {
        long double root = -remainder.c[0] / remainder.c[1];
        append(steps, "\nIsolate x by subtracting the constant and dividing by its coefficient.");
        bool found = false;
        for (int i = 0; i < count; i++) if (roots[i] == root) found = true;
        if (!found) {
            append(out, count ? ", " : "x = ");
            value_text(out, root, decimal);
        }
    } else if (remainder.degree == 0 && !count) {
        append(out, remainder.c[0] == 0 ? "All real x" : "No real solutions");
    } else if (remainder.degree > 2) {
        append(out, count ? "\nOther roots unresolved" : "Unable to solve this polynomial");
        append(steps, "\nThe remaining degree exceeds two and no further rational root was found.");
    }
}


typedef struct { Poly numerator, denominator; } Rational;

static bool rational(Expr e, Rational *r) {
    if (!e) return false;
    if (polynomial(e, &r->numerator)) {
        r->denominator = (Poly){.c = {1}};
        return finite_poly(&r->numerator);
    }
    Node node = nodes[e];
    if (node.kind < Add || node.kind > Div || !rational(node.left, r)) return false;
    Rational right, result;
    if (!rational(node.right, &right)) return false;
    const Poly *a = &r->numerator, *b = &r->denominator;
    const Poly *c = &right.numerator, *d = &right.denominator;
    if (node.kind == Mul || node.kind == Div) {
        if (node.kind == Div && c->degree == 0 && c->c[0] == 0) return false;
        if (!multiply(a, node.kind == Div ? d : c, &result.numerator) ||
            !multiply(b, node.kind == Div ? c : d, &result.denominator)) return false;
    } else {
        Poly part;
        if (!multiply(a, d, &result.numerator) || !multiply(b, c, &part) ||
            !multiply(b, d, &result.denominator)) return false;
        if (part.degree > result.numerator.degree) result.numerator.degree = part.degree;
        for (int i = 0; i <= part.degree; i++)
            result.numerator.c[i] += node.kind == Add ? part.c[i] : -part.c[i];
        trim(&result.numerator);
    }
    if (!finite_poly(&result.numerator) || !finite_poly(&result.denominator)) return false;
    *r = result;
    return true;
}

static bool divide_exactly(const Poly *p, const Poly *divisor, Poly *quotient) {
    Poly rem = *p;
    *quotient = (Poly){0};
    for (int i = p->degree - divisor->degree; i >= 0; i--) {
        int power = i + divisor->degree;
        long double value = rem.c[power] / divisor->c[divisor->degree];
        if (!isfinite(value)) return false;
        quotient->c[i] = value;
        for (int j = 0; j < divisor->degree; j++) {
            long double product = value * divisor->c[j], before = rem.c[i+j];
            rem.c[i+j] -= product;
            if (isfinite(rem.c[i+j]) && fabsl(rem.c[i+j]) <= fmaxl(fabsl(before), fabsl(product)) * 8e-16L)
                rem.c[i+j] = 0;
        }
        rem.c[power] = 0;
    }
    for (int i = 0; i <= rem.degree; i++) if (rem.c[i] != 0) return false;
    quotient->degree = p->degree >= divisor->degree ? p->degree - divisor->degree : 0;
    trim(quotient);
    return true;
}

static void restrictions(Expr e, Writer *out) {
    if (!e) return;
    Node node = nodes[e];
    if (node.kind == Div && !constant(node.right)) {
        append(out, "\n");
        expr_text(out, node.right, 0);
        append(out, " != 0");
    }
    restrictions(node.left, out);
    restrictions(node.right, out);
}

static bool rational_text(Expr e, Writer *out, Writer *steps) {
    Rational r;
    if (!rational(e, &r)) return false;
    Poly *p = &r.numerator, *q = &r.denominator;
    if (!q->c[q->degree]) return false;
    Poly candidate = *q, quotient;
    long double ignored;
    integer_form(&candidate, &ignored);
    while (candidate.degree > 0 && q->degree > 0) {
        if (divide_exactly(p, q, &quotient)) {
            *p = quotient;
            *q = (Poly){.c = {1}};
            break;
        }
        long double root = 0;
        if (candidate.degree == 1) root = -candidate.c[0]/candidate.c[1];
        else if (!rational_root(&candidate, &root)) break;
        long n, d;
        if (!fraction(root, &n, &d)) break;
        candidate = remove_root(&candidate, n, d);
        Poly factor = {.c = {-n, d}, .degree = 1}, reduced_denominator;
        if (divide_exactly(p, &factor, &quotient) && divide_exactly(q, &factor, &reduced_denominator)) {
            *p = quotient;
            *q = reduced_denominator;
        }
    }
    long double scale = q->degree ? gcd(integer_content(p), integer_content(q)) : q->c[0];
    if (q->degree && q->c[q->degree] < 0) scale = -scale;
    for (int i = 0; i <= p->degree; i++) p->c[i] /= scale;
    for (int i = 0; i <= q->degree; i++) q->c[i] /= scale;
    if (!finite_poly(p) || !finite_poly(q)) return false;
    append(steps, "Use a common denominator.\nCancel common factors and keep the original domain.");
    if (q->degree && p->degree) append(out, "(");
    poly_text(out, p);
    if (q->degree) {
        if (p->degree) append(out, ")");
        append(out, "/(");
        poly_text(out, q);
        append(out, ")");
    }
    restrictions(e, out);
    return true;
}

static void numeric_answer(Writer *out, long double value, bool decimal) {
    long n, d;
    if (!decimal && fraction(value, &n, &d)) value_text(out, value, false);
    else {
        if (value != truncl(value)) append(out, "approx. ");
        value_text(out, value, true);
    }
}

static bool calculated_special(const char *input, bool decimal, Solution *solution) {
    Writer out = {solution->answer, sizeof(solution->answer), 0};
    Writer steps = {solution->steps, sizeof(solution->steps), 0};
    const char *operator = strstr(input, "->");
    if (operator) {
        const char *name = operator + 2;
        while (isspace((unsigned char)*name)) name++;
        int index = variable_index(*name);
        if (index < 0 || strchr("exi", *name)) goto invalid_store;
        const char *end = name + 1;
        while (isspace((unsigned char)*end)) end++;
        if (*end || operator - input >= EXPRESSION_SIZE) goto invalid_store;
        char expression_text[EXPRESSION_SIZE];
        snprintf(expression_text, sizeof(expression_text), "%.*s", (int)(operator - input), input);
        Expr expression = parse(expression_text, false);
        long double value = constant(expression) ? evaluate(expression, 0) : NAN;
        if (!isfinite(value)) goto invalid_store;
        stored_variables.set[index] = true;
        stored_variables.value[index] = value;
        print(&steps, "Store the result in %c for this session.\n", *name);
        numeric_answer(&out, value, decimal);
        solution->ok = true;
        return true;

invalid_store:
        append(&out, "Use a numeric result and one letter other than e, i or x.");
        return true;
    }
    operator = strpbrk(input, "<>");
    if (!operator || operator - input >= EXPRESSION_SIZE) return false;
    char left[EXPRESSION_SIZE];
    snprintf(left, sizeof(left), "%.*s", (int)(operator - input), input);
    bool inclusive = operator[1] == '=';
    Expr a = parse(left, false);
    Expr b = parse(operator + (inclusive ? 2 : 1), false);
    long double x = constant(a) ? evaluate(a, 0) : NAN;
    long double y = constant(b) ? evaluate(b, 0) : NAN;
    if (!isfinite(x) || !isfinite(y)) append(&out, "Enter two real numeric expressions to compare.");
    else {
        bool result = (inclusive && x == y) || (*operator == '<' ? x < y : x > y);
        append(&steps, "Evaluate both sides and compare their values.");
        append(&out, result ? "True" : "False");
        solution->ok = true;
    }
    return true;
}

bool cas_read_number(const char *input, long double *value) {
    used = 0;
    too_complex = false;
    radians = true;
    Expr expr = parse(input, false);
    if (!constant(expr)) return false;
    *value = evaluate(expr, 0);
    return isfinite(*value);
}

void solve_expression(Operation operation, const char *input, const char *second,
                      const char *third, bool degrees, bool decimal, Solution *solution) {
    *solution = (Solution){0};
    used = 0;
    too_complex = false;
    radians = !degrees;
    if (operation == Calculate && input && calculated_special(input, decimal, solution)) return;
    bool equation = operation == Solve || operation == Factorise || operation == FindRoot || operation == CompleteSquare;
    Expr e = parse(input, equation);
    Writer out = {solution->answer, sizeof(solution->answer), 0};
    Writer steps = {solution->steps, sizeof(solution->steps), 0};
    const char *error = "Check brackets, numbers and operators.";
    if (!e) goto fail;

    if (operation == Calculate || operation == Substitute) {
        long double x = operation == Substitute ? evaluate(parse(second, false), NAN) : NAN;
        long double result = ((operation == Substitute && !isfinite(x)) ||
                         (operation == Calculate && !constant(e))) ? NAN : evaluate(e, x);
        error = "Enter a numeric expression in its real domain.";
        if (!isfinite(result)) goto fail;
        if (operation == Substitute) {
            append(&steps, "Substitute x = ");
            value_text(&steps, x, decimal);
            append(&steps, " and evaluate.");
        } else append(&steps, "Evaluate powers and functions, then products, then sums.");
        numeric_answer(&out, result, decimal);
    } else if (operation == CompleteSquare) {
        Poly p;
        error = "Enter a quadratic in x with a nonzero x^2 coefficient.";
        if (!polynomial(e, &p) || !finite_poly(&p) || !complete_square(&p, strchr(input, '=') != NULL, &out, &steps))
            goto fail;
    } else if (operation == Factorise || operation == Simplify || operation == Expand || operation == Solve) {
        Poly p;
        if (polynomial(e, &p) && finite_poly(&p)) {
            algebra(operation, p, &out, &steps, decimal);
            if (operation == Factorise && strchr(input, '=')) append(&out, " = 0");
        } else if (operation != Simplify || !rational_text(e, &out, &steps)) {
            error = "Use a polynomial in x of degree 12 or less.";
            goto fail;
        }
    } else if (operation == Differentiate) {
        Poly p;
        if (polynomial(e, &p) && finite_poly(&p)) {
            append(&steps, "Use the power rule: ax^n -> anx^(n-1).\nThe derivative of a constant is zero.");
            for (int i = 0; i < p.degree; i++) p.c[i] = p.c[i + 1] * (i + 1);
            p.c[p.degree] = 0;
            trim(&p);
            error = "Derivative coefficients out of range.";
            if (!finite_poly(&p)) goto fail;
            poly_text(&out, &p);
        } else {
            Expr result = derivative(e);
            error = "A symbolic derivative is unavailable for this expression.";
            if (!result || too_complex) goto fail;
            Kind k = nodes[e].kind;
            if (k == Mul) append(&steps, "Use the product rule: (uv)' = u'v + uv'.");
            else if (k == Div) append(&steps, "Use the quotient rule: (u/v)' = (u'v - uv')/v^2.");
            else if (k == Add || k == Sub) append(&steps, "Differentiate each term separately.");
            else append(&steps, "Apply the chain rule to each composed function.");
            expr_text(&out, result, 0);
        }
    } else if (operation == Integrate || operation == Definite) {
        Poly p;
        bool is_poly = polynomial(e, &p) && finite_poly(&p);
        if (operation == Definite && !is_poly) {
            error = "The definite-integral form currently accepts polynomials.";
            goto fail;
        }
        Expr f = primitive(e);
        error = "Try a polynomial or a basic function of a linear expression.";
        if (!f || too_complex) goto fail;
        if (is_poly) append(&steps, "For each ax^n, raise the power by 1 and divide by n+1.\n");
        else append(&steps, "Reverse the chain rule, dividing by the inner gradient.\n");
        append(&steps, "F(x) = ");
        Poly integrated;
        bool poly_result = polynomial(f, &integrated) && finite_poly(&integrated);
        if (poly_result) poly_text(&steps, &integrated);
        else expr_text(&steps, f, 0);
        if (operation == Integrate) {
            if (poly_result) poly_text(&out, &integrated);
            else expr_text(&out, f, 0);
            append(&out, " + C");
        } else {
            long double a = evaluate(parse(second, false), NAN), b = evaluate(parse(third, false), NAN);
            long double result = isfinite(a) && isfinite(b) ? evaluate(f, b) - evaluate(f, a) : NAN;
            error = "Enter two numeric limits with a finite result.";
            if (!isfinite(result)) goto fail;
            append(&steps, "\nF(");
            value_text(&steps, b, decimal);
            append(&steps, ") - F(");
            value_text(&steps, a, decimal);
            append(&steps, ") = ");
            value_text(&steps, evaluate(f, b), decimal);
            append(&steps, " - (");
            value_text(&steps, evaluate(f, a), decimal);
            append(&steps, ")");
            numeric_answer(&out, result, decimal);
        }
    } else if (operation == FindRoot) {
        long double a = evaluate(parse(second, false), NAN), b = evaluate(parse(third, false), NAN);
        error = "Enter numeric bounds with lower < upper.";
        if (!isfinite(a) || !isfinite(b) || a >= b || !isfinite(b-a)) goto fail;
        long double fa = evaluate(e, a), fb = evaluate(e, b);
        error = "Use finite endpoint values with opposite signs.";
        if (!isfinite(fa) || !isfinite(fb) || ((fa < 0) == (fb < 0) && fa && fb)) goto fail;
        long double left = a, right = b, x = !fa ? a : b;
        append(&steps, "For a continuous function, opposite signs bracket a root.\nBisect and keep the half with the sign change.");
        if (fa && fb) {
            for (int i = 0; i < 64; i++) {
                x = left + (right - left)/2;
                long double fx = evaluate(e, x);
                error = "No root verified. Check for a discontinuity or refine the interval.";
                if (!isfinite(fx)) goto fail;
                if (!fx || x == left || x == right) break;
                if ((fx < 0) == (fa < 0)) left = x;
                else right = x;
            }
            if (fabsl(evaluate(e, x)) > fmaxl(fabsl(fa), fabsl(fb)) * 1e-10L) goto fail;
        }
        append(&out, "x approx. ");
        value_text(&out, x, true);
    }
    if (out.length == out.capacity - 1) {
        error = "The result is too long to display.";
        goto fail;
    }
    solution->ok = true;
    return;

fail:
    solution->steps[0] = 0;
    snprintf(solution->answer, sizeof(solution->answer), "%s", error);
}

/* The calculation history keeps a proven exact rational, single surd or
 * rational multiple of pi alongside the floating-point value for display. */
typedef struct { long n, d, rad; } Exact;
static const long ExactLimit = 1000000000L;

static Exact exact_value(int64_t n, int64_t d, long rad) {
    if (!d) return (Exact){0};
    if (!n) return (Exact){0, 1, 1};
    if (d < 0) { n = -n; d = -d; }
    int64_t a = n < 0 ? -n : n, b = d;
    while (b) { int64_t remainder = a % b; a = b; b = remainder; }
    n /= a;
    d /= a;
    if (n < -ExactLimit || n > ExactLimit || d > ExactLimit) return (Exact){0};
    return (Exact){(long)n, (long)d, rad};
}

static Exact exact_literal(const char *text, int length) {
    int64_t n = 0, d = 1;
    int decimals = 0, exponent = 0, sign = 1, i = 0;
    bool dot = false;
    for (; i < length && text[i] != 'e' && text[i] != 'E'; i++) {
        if (text[i] == '.') { dot = true; continue; }
        if (!isdigit((unsigned char)text[i]) || n > INT64_C(100000000000000000))
            return (Exact){0};
        n = 10*n + text[i] - '0';
        decimals += dot;
    }
    if (i < length) {
        i++;
        if (text[i] == '-' || text[i] == '+') sign = text[i++] == '-' ? -1 : 1;
        for (; i < length && exponent <= 40; i++) exponent = 10*exponent + text[i] - '0';
        if (exponent > 40) return (Exact){0};
    }
    if (!n) return (Exact){0, 1, 1};
    int shift = decimals - sign*exponent;
    while (shift > 0 && n % 10 == 0) { n /= 10; shift--; }
    if (shift > 9 || shift < -9) return (Exact){0};
    for (; shift > 0; shift--) d *= 10;
    for (; shift < 0; shift++) {
        if (n > ExactLimit/10) return (Exact){0};
        n *= 10;
    }
    return exact_value(n, d, 1);
}

static Exact exact_root(Exact a) {
    if (!a.d || a.rad != 1 || a.n < 0) return (Exact){0};
    if (!a.n) return a;
    unsigned long outside = 1, inside = 1;
    unsigned long top = (unsigned long)a.n, bottom = (unsigned long)a.d;
    // Factoring the numerator and denominator separately keeps the loop bounded.
    for (unsigned long p = 2; p <= top/p || p <= bottom/p; p++) {
        unsigned long count = 0;
        while (top % p == 0) { top /= p; count++; }
        while (bottom % p == 0) { bottom /= p; count++; }
        for (unsigned long j = 0; j < count/2; j++) {
            if (outside > (unsigned long)ExactLimit/p) return (Exact){0};
            outside *= p;
        }
        if (count % 2) {
            if (inside > (unsigned long)ExactLimit/p) return (Exact){0};
            inside *= p;
        }
    }
    if (top == bottom) {
        if (outside > (unsigned long)ExactLimit/top) return (Exact){0};
        outside *= top;
    } else {
        if ((uint64_t)inside*top*bottom > ExactLimit) return (Exact){0};
        inside *= top*bottom;
    }
    return exact_value(outside, a.d, (long)inside);
}

static Exact exact_product(Exact a, Exact b, bool divide) {
    if (!a.d || !b.d || (divide && !b.n)) return (Exact){0};
    if (!a.n || (!divide && !b.n)) return (Exact){0, 1, 1};
    int64_t n = (int64_t)a.n*(divide ? b.d : b.n);
    int64_t d = (int64_t)a.d*(divide ? b.n : b.d);
    if (!a.rad || !b.rad) {
        if (divide && a.rad == b.rad) return exact_value(n, d, 1);
        if ((a.rad == 0 && b.rad == 1) || (!divide && a.rad == 1 && b.rad == 0))
            return exact_value(n, d, 0);
        return (Exact){0};
    }
    if (a.rad == b.rad) {
        if (!divide) {
            Exact product = exact_value(n, d, 1);
            return product.d ? exact_value((int64_t)product.n*a.rad, product.d, 1) : product;
        }
        return exact_value(n, d, 1);
    }
    unsigned long common = gcd((unsigned long)a.rad, (unsigned long)b.rad);
    int64_t rad = (int64_t)(a.rad/common)*(b.rad/common);
    if (rad > ExactLimit) return (Exact){0};
    Exact product = exact_value(n, d, (long)rad);
    if (!product.d) return product;
    return divide ? exact_value(product.n, (int64_t)product.d*(b.rad/common), product.rad) :
                    exact_value((int64_t)product.n*common, product.d, product.rad);
}

static Exact exact_trig(Kind kind, Exact a) {
    if(gradians) return (Exact){0};
    if (!a.d || (a.n && a.rad != (radians ? 0 : 1))) return (Exact){0};
    int64_t numerator = radians ? (int64_t)a.n*12 : a.n;
    int64_t denominator = radians ? a.d : 15LL*a.d;
    if (numerator % denominator) return (Exact){0};
    int turn = (int)((numerator/denominator)%24);
    if (turn < 0) turn += 24;
    if (kind == Tan)
        return exact_product(exact_trig(Sin, a), exact_trig(Cos, a), true);
    if (kind == Cos) turn = (turn + 6)%24;
    int sign = turn > 12 ? -1 : 1;
    turn %= 12;
    if (turn > 6) turn = 12 - turn;
    switch (turn) {
        case 0: return (Exact){0, 1, 1};
        case 2: return (Exact){sign, 2, 1};
        case 3: return (Exact){sign, 2, 2};
        case 4: return (Exact){sign, 2, 3};
        case 6: return (Exact){sign, 1, 1};
        default: return (Exact){0};
    }
}

static Exact exact_expression(Expr e) {
    if (!e) return (Exact){0};
    Node v = nodes[e];
    if (v.kind == Number) {
        if (v.literal_kind == 1) return (Exact){1, 1, 0};
        if (v.literal_kind) return (Exact){0};
        if (v.literal_length) return exact_literal(number_tokens[e], v.literal_length);
        return fabsl(v.value) <= ExactLimit && truncl(v.value) == v.value ?
               (Exact){(long)v.value, 1, 1} : (Exact){0};
    }
    if(v.kind==Mixed) {
        Node pair=nodes[v.right];Exact a=exact_expression(v.left),b=exact_expression(pair.left),c=exact_expression(pair.right);
        if(a.d==1&&b.d==1&&c.d==1&&a.rad==1&&b.rad==1&&c.rad==1&&b.n>=0&&c.n>0)
            return exact_value((int64_t)a.n*c.n+(a.n<0?-1:1)*b.n,c.n,1);
        return (Exact){0};
    }
    Exact a = exact_expression(v.left);
    if (!a.d) return a;
    if (v.kind == Sqrt) return exact_root(a);
    if (v.kind == Sin || v.kind == Cos || v.kind == Tan) return exact_trig(v.kind, a);
    if (v.kind == Abs) return (Exact){labs(a.n), a.d, a.rad};
    if (v.kind < Add || v.kind > Pow) {
        long double value = evaluate(e, 0);
        if ((v.kind == Floor || v.kind == Gcd || v.kind == Choose || v.kind == Permute || v.kind == Factorial) &&
            isfinite(value) && fabsl(value) <= ExactLimit && value == truncl(value))
            return (Exact){(long)value, 1, 1};
        return (Exact){0};
    }
    Exact b = exact_expression(v.right);
    if (!b.d) return b;
    if (v.kind == Mul || v.kind == Div) return exact_product(a, b, v.kind == Div);
    if (v.kind == Add || v.kind == Sub) {
        if (v.kind == Sub) b.n = -b.n;
        if (!a.n) return b;
        if (!b.n) return a;
        return a.rad == b.rad ? exact_value((int64_t)a.n*b.d + (int64_t)b.n*a.d,
                                            (int64_t)a.d*b.d, a.rad) : (Exact){0};
    }
    if (b.rad != 1) return (Exact){0};
    if (b.n == 1 && b.d == 2) return exact_root(a);
    if (b.d != 1 || labs(b.n) > 32) return (Exact){0};
    Exact result = {1, 1, 1};
    for (int i = 0; i < labs(b.n) && result.d; i++) result = exact_product(result, a, b.n < 0);
    return result;
}

bool cas_calculation(const char *input, bool degrees, CalculationValue *result) {
    *result = (CalculationValue){.degrees = degrees};
    used = 0;
    too_complex = false;
    radians = !degrees;
    Expr e = parse(input, false);
    if (!constant(e)) return false;
    result->syntax_valid=true;
    result->value = evaluate(e, 0);
    if (!isfinite(result->value)) return false;
    result->numeric = true;
    Node top = nodes[e];
    if (top.kind == Sqrt || top.kind == Sin || top.kind == Cos || top.kind == Tan) {
        result->argument = evaluate(top.left, 0);
        Exact argument = exact_expression(top.left);
        result->argument_n = argument.n;
        result->argument_d = argument.d;
        result->argument_rad = argument.rad;
        result->kind = top.kind == Sqrt ? ExtraRoot : top.kind == Sin ? ExtraSin :
                       top.kind == Cos ? ExtraCos : ExtraTan;
    }
    Exact exact = exact_expression(e);
    if (!exact.d) return true;
    result->numerator = exact.n;
    result->denominator = exact.d;
    result->radicand = exact.rad;
    Writer out = {result->exact, sizeof(result->exact), 0};
    if (exact.rad == 1) print(&out, "%ld", exact.n);
    else {
        if (exact.d != 1) append(&out, "(");
        if (exact.n < 0) append(&out, "-");
        if (labs(exact.n) != 1) print(&out, "%ld*", labs(exact.n));
        if (exact.rad == 0) append(&out, "pi");
        else print(&out, "sqrt(%ld)", exact.rad);
        if (exact.d != 1) append(&out, ")");
    }
    if (exact.d != 1) print(&out, "/%ld", exact.d);
    return true;
}

typedef struct { Kind kind; long double scale, shift; bool found; } TrigAngle;

static bool trig_polynomial(Expr e, TrigAngle *angle, Poly *out) {
    if (!e) return false;
    Node v = nodes[e];
    if (constant(e)) {
        long double value = evaluate(e, 0);
        if (!isfinite(value)) return false;
        *out = (Poly){.c={value}};
        return true;
    }
    if (v.kind == Sin || v.kind == Cos || v.kind == Tan) {
        Poly p;
        if (!polynomial(v.left, &p) || p.degree != 1 || !finite_poly(&p)) return false;
        if (angle->found && (angle->kind != v.kind || angle->scale != p.c[1] || angle->shift != p.c[0]))
            return false;
        *angle = (TrigAngle){v.kind,p.c[1],p.c[0],true};
        *out = (Poly){.c={0,1},.degree=1};
        return true;
    }
    if (v.kind < Add || v.kind > Pow || !trig_polynomial(v.left, angle, out)) return false;
    if (v.kind == Pow) {
        long double power = evaluate(v.right, NAN);
        if (power == 0) { *out = (Poly){.c={1}}; return true; }
        if (power == 1) return true;
        if (power != 2 || out->degree > 1) return false;
        Poly square;
        multiply(out, out, &square);
        *out = square;
        return finite_poly(out);
    }
    Poly right;
    if (!trig_polynomial(v.right, angle, &right)) return false;
    if (v.kind == Div) {
        if (right.degree || right.c[0] == 0) return false;
        for (int i = 0; i <= out->degree; i++) out->c[i] /= right.c[0];
    } else if (v.kind == Mul) {
        Poly product;
        if (out->degree + right.degree > 2 || !multiply(out, &right, &product)) return false;
        *out = product;
    } else {
        if (right.degree > out->degree) out->degree = right.degree;
        for (int i = 0; i <= right.degree; i++) out->c[i] += v.kind == Add ? right.c[i] : -right.c[i];
        trim(out);
    }
    return finite_poly(out);
}

typedef struct { long double constant, sine, cosine; } TrigSum;

static bool mixed_trig(Expr e, TrigAngle *angle, TrigSum *out) {
    if (!e) return false;
    Node v = nodes[e];
    if (constant(e)) {
        out->constant = evaluate(e,0);
        return isfinite(out->constant);
    }
    if (v.kind == Sin || v.kind == Cos) {
        Poly p;
        if (!polynomial(v.left,&p) || p.degree != 1 || !finite_poly(&p)) return false;
        if (angle->found && (angle->scale != p.c[1] || angle->shift != p.c[0])) return false;
        *angle = (TrigAngle){Sin,p.c[1],p.c[0],true};
        if (v.kind == Sin) out->sine = 1;
        else out->cosine = 1;
        return true;
    }
    if (v.kind < Add || v.kind > Div) return false;
    TrigSum a = {0}, b = {0};
    if (!mixed_trig(v.left,angle,&a) || !mixed_trig(v.right,angle,&b)) return false;
    if (v.kind == Add || v.kind == Sub) {
        long double sign = v.kind == Add ? 1 : -1;
        *out = (TrigSum){a.constant+sign*b.constant,a.sine+sign*b.sine,a.cosine+sign*b.cosine};
    } else {
        if (v.kind == Mul && (b.sine || b.cosine)) { TrigSum swap=a; a=b; b=swap; }
        if (b.sine || b.cosine || (v.kind == Div && !b.constant)) return false;
        long double factor = v.kind == Div ? 1/b.constant : b.constant;
        *out = (TrigSum){a.constant*factor,a.sine*factor,a.cosine*factor};
    }
    return isfinite(out->constant) && isfinite(out->sine) && isfinite(out->cosine);
}

static bool trig_family(long double base, long double period, TrigAngle angle, long double low, long double high,
                        long double roots[64], int *count) {
    long double start = angle.scale*low + angle.shift, end = angle.scale*high + angle.shift;
    long double left = fminl(start, end), right = fmaxl(start, end);
    if (!isfinite(left) || !isfinite(right)) return false;
    long double first = ceill((left - base)/period - 1e-12L);
    long double last = floorl((right - base)/period + 1e-12L);
    if (last < first) return true;
    if (last-first >= 64 || fabsl(first) > 1e13L || fabsl(last) > 1e13L) return false;
    for (long double n = first; n <= last; n++) {
        long double x = (fmal(period, n, base) - angle.shift)/angle.scale;
        long double tol = 1e-12L*fmaxl(1, fmaxl(fabsl(low), fabsl(high)));
        if (x < low-tol || x > high+tol) continue;
        if (fabsl(x-low) <= tol) x = low;
        if (fabsl(x-high) <= tol) x = high;
        int j = 0;
        while (j < *count && roots[j] < x-tol) j++;
        if (j < *count && fabsl(roots[j]-x) <= tol) continue;
        if (*count == 64) return false;
        for (int i = (*count)++; i > j; i--) roots[i] = roots[i-1];
        roots[j] = x;
    }
    return true;
}

void cas_trig_equation(const char *input, const char *lower, const char *upper,
                       bool degrees, Solution *solution) {
    *solution = (Solution){0};
    long double low, high;
    if (!cas_read_number(lower, &low) || !cas_read_number(upper, &high) || low > high) {
        strcpy(solution->answer, "Enter finite bounds with lower <= upper.");
        return;
    }
    used = 0;
    too_complex = false;
    radians = !degrees;
    Expr e = parse(input, true);
    TrigAngle angle = {0};
    Poly p;
    char reduction[92] = "";
    if (!e || !trig_polynomial(e, &angle, &p) || !angle.found) {
        angle = (TrigAngle){0};
        TrigSum sum = {0};
        if (!e || !mixed_trig(e,&angle,&sum) || !angle.found) {
            strcpy(solution->answer, "Use linear angles in sin, cos or tan. Sine and cosine can share an angle.");
            return;
        }
        long double radius = hypotl(sum.sine,sum.cosine);
        long double phase = atan2l(sum.cosine,sum.sine)*(degrees ? 180/PI : 1);
        angle.shift += phase;
        if (!isfinite(radius) || !isfinite(angle.shift)) {
            strcpy(solution->answer,"The coefficients are outside the supported range.");
            return;
        }
        p = (Poly){.c={sum.constant,radius},.degree=radius != 0};
        snprintf(reduction,sizeof(reduction),"Combine sine and cosine as %.8Lg sin(angle %+.8Lg).\n",radius,phase);
    }
    Writer out = {solution->answer, sizeof(solution->answer), 0};
    Writer steps = {solution->steps, sizeof(solution->steps), 0};
    append(&steps,reduction);
    const char *name = angle.kind == Sin ? "sin" : angle.kind == Cos ? "cos" : "tan";
    print(&steps, "Let t = %s(theta).\n", name);
    append(&steps, "theta = ");
    if (angle.scale == 1) append(&steps, "x");
    else if (angle.scale == -1) append(&steps, "-x");
    else print(&steps, "%.10Lgx", angle.scale);
    if (angle.shift) print(&steps, " %+.10Lg", angle.shift);
    append(&steps, ".\n");
    append(&steps, "Solve in t: ");
    poly_text_variable(&steps, &p,'t');
    append(&steps, " = 0.\n");
    solution->ok = true;
    if (p.degree == 0) {
        append(&out, p.c[0] != 0 ? "No solutions." : angle.kind == Tan ?
               "All x in the interval where tan is defined." : "All x in the interval.");
        return;
    }
    long double targets[2];
    int targets_count = 0;
    if (p.degree == 1) targets[targets_count++] = -p.c[0]/p.c[1];
    else {
        long double scale = fmaxl(fabsl(p.c[0]), fmaxl(fabsl(p.c[1]), fabsl(p.c[2])));
        long double a = p.c[2]/scale, b = p.c[1]/scale, c = p.c[0]/scale;
        long double d = fmal(b,b,-4*a*c);
        if (d == 0) targets[targets_count++] = -b/(2*a);
        else if (d > 0) {
            long double q = -0.5L*(b+copysignl(sqrtl(d),b));
            targets[targets_count++] = q/a;
            targets[targets_count++] = c/q;
        }
    }
    long double roots[64], convert = degrees ? 180/PI : 1, turn = degrees ? 360 : 2*PI;
    int count = 0;
    for (int i = 0; i < targets_count; i++) {
        long double t = targets[i];
        if (!isfinite(t) || (angle.kind != Tan && fabsl(t) > 1+1e-13L)) continue;
        if (angle.kind != Tan) t = fmaxl(-1,fminl(1,t));
        long double base = (angle.kind == Sin ? asinl(t) : angle.kind == Cos ? acosl(t) : atanl(t))*convert;
        long double periodic = angle.kind == Tan ? turn/2 : turn;
        print(&steps, "%s(theta) = %.10Lg gives theta = %.10Lg\n", name,t,base);
        long double other = angle.kind == Sin ? turn/2-base : -base;
        if (angle.kind != Tan) print(&steps, "or theta = %.10Lg by symmetry.\n", other);
        print(&steps, "Add multiples of %.10Lg, then find x.\n", periodic);
        if (!trig_family(base, periodic, angle, low, high, roots, &count) ||
            (angle.kind != Tan && !trig_family(other, periodic, angle, low, high, roots, &count))) {
            solution->ok = false;
            strcpy(solution->answer, "Too many periods to display. Narrow the interval.");
            return;
        }
    }
    if (!count) append(&out, "No solutions in the interval.");
    else {
        append(&out, "x = ");
        for (int i = 0; i < count; i++) {
            char item[32];
            snprintf(item, sizeof(item), "%s%.11Lg", i ? ", " : "", roots[i] == 0 ? 0 : roots[i]);
            if (out.length + strlen(item) + 6 >= out.capacity) {
                solution->ok = false;
                strcpy(solution->answer, "Too many answers to display. Narrow the interval.");
                return;
            }
            append(&out,item);
        }
        append(&out, degrees ? " deg" : " rad");
    }
}
