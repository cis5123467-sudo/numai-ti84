#include "mathview.h"

#include <ctype.h>
#include <string.h>
extern int platform_width(const char *, int, bool, bool);

enum { LayoutLimit = 110, LayoutChars = 112 };
typedef enum { Text, Adjacent, Fraction, Radical, Raised, Lowered, Parentheses } LayoutKind;
typedef struct {
    LayoutKind kind;
    int a,b;
    MathBox box;
    const char *text, *start, *end;
    int length;
    char single;
    bool small;
    int pad;
} Layout;
static Layout layouts[LayoutLimit];
static int count;
static bool overflow, large;
static const char *cursor;
static MathCaret caret;
static int caret_depth;

static int max(int a,int b) { return a>b ? a:b; }

static int item(Layout layout) {
    if (count == LayoutLimit-1) { overflow = true; return 0; }
    layouts[++count] = layout;
    return count;
}

/* Native glyphs are 9 pixels high (7 for indices), independent of the
 * history row height. The text backend adds one top pixel to normal text. */
static int half_height(bool small) { return small ? 4 : 5; }

static int leaf(const char *text,int length,char one,bool small) {
    int above = small ? 3 : 5, below = small ? 4 : 5;
    int pad = one && (one == MathMultiply || one == MathApprox || strchr("+-=<>;",one)) ? 1 : 0;
    int width = one ? platform_width(&one,1,small,false) : platform_width(text,length,small,false);
    return item((Layout){.kind=Text,.box={width+2*pad,above,below},
                          .text=text,.length=length,.single=one,.small=small,
                          .start=text,.end=text ? text+length : NULL,.pad=pad});
}

static int join(LayoutKind kind,int a,int b) {
    if (!a || (kind != Radical && kind != Parentheses && !b)) { overflow = true; return 0; }
    MathBox left = layouts[a].box, right = layouts[b].box, box;
    switch (kind) {
        case Fraction:
            box = (MathBox){max(left.width,right.width)+4,left.above+left.below+2,right.above+right.below+2};
            break;
        case Radical: box = (MathBox){left.width+10,left.above+3,max(left.below,half_height(false))}; break;
        case Raised:
            box = (MathBox){left.width+right.width+1,max(left.above,left.above+right.above+right.below-(right.above+right.below>8 ? 1 : 4)),left.below};
            break;
        case Lowered:
            box = (MathBox){left.width+right.width+1,left.above,max(left.below,left.below+right.above+right.below-4)};
            break;
        case Parentheses: {
            bool small = layouts[a].small;
            int bracket = platform_width("(", 1, small, false);
            bool stretched = left.above + left.below > 2 * half_height(small);
            box = (MathBox){left.width + 2 * (bracket + 1),
                            left.above + (stretched ? 1 : 0), left.below + (stretched ? 1 : 0)};
            break;
        }
        default:
            box = (MathBox){left.width+right.width+(left.width && right.width ? 1 : 0),max(left.above,right.above),max(left.below,right.below)};
            break;
    }
    return item((Layout){.kind=kind,.a=a,.b=b,.box=box,.small=layouts[a].small});
}

static const char *closing(const char *first,const char *end) {
    int depth = 0;
    for (const char *p=first;p<end;p++) {
        if (*p=='(') depth++;
        if (*p==')' && --depth==0) return p;
    }
    return NULL;
}

static bool unary_mark(const char *start,const char *p,const char *end) {
    if (p==start) return true;
    const char *prev = p-1;
    while (prev>start && *prev==' ') prev--;
    if (*prev == 'e' || *prev == 'E')
        return prev>start && (isdigit((unsigned char)prev[-1]) || prev[-1]=='.') &&
               p+1<end && isdigit((unsigned char)p[1]);
    return strchr("+-*/^=(,",*prev)!=NULL;
}

static int parse_math(const char *start,const char *end,bool small,int depth);

static int fraction_term(const char *start,const char *end,bool small,int depth) {
    while (start<end && *start==' ') start++;
    while (start<end && end[-1]==' ') end--;
    if (start<end && *start=='(' && closing(start,end)==end-1) { start++; end--; }
    return parse_math(start,end,small,depth);
}

static int parse_span(const char *start,const char *end,bool small,int depth) {
    while (start<end && *start==' ') start++;
    while (start<end && end[-1]==' ') end--;
    if (overflow || depth>20 || start==end) return leaf(start,(int)(end-start),0,small);
    const char *level1 = NULL, *level2 = NULL, *power = NULL;
    int nesting = 0;
    for (const char *p=start;p<end;p++) {
        if (end-p >= 3 && !memcmp(p, "+/-", 3)) { p += 2; continue; }
        if (*p=='{' || *p=='[') { nesting++; continue; }
        if (*p=='}' || *p==']') { nesting--; continue; }
        if (*p=='(') { nesting++; continue; }
        if (*p==')') { nesting--; continue; }
        if (nesting) continue;
        if ((*p=='+' || *p=='-') && !unary_mark(start,p,end)) {
            if (!level1 || (*level1!='=' && *level1!=MathApprox)) level1=p;
        } else if (*p=='=' || *p==MathApprox) level1=p;
        else if (*p=='*' || *p=='/') level2=p;
        else if (*p=='^' && !power && !level1 && !level2) power=p;
    }
    if (level1 || level2 || power) {
        const char *op = level1 ? level1 : level2 ? level2 : power;
        if (*op=='/') {
            int a = fraction_term(start,op,small,depth+1);
            int b = fraction_term(op+1,end,small,depth+1);
            return join(Fraction,a,b);
        }
        if (*op=='^') {
            int a = parse_math(start,op,small,depth+1);
            int b = fraction_term(op+1,end,true,depth+1);
            return join(Raised,a,b);
        }
        int a = parse_math(start,op,small,depth+1);
        int b = parse_math(op+1,end,small,depth+1);
        if (*op=='*' && ((end-op>5 && !strncmp(op+1,"sqrt(",5)) ||
                         (end-op==3 && !strncmp(op+1,"pi",2)))) return join(Adjacent,a,b);
        int symbol = leaf(NULL,0,*op=='*'?MathMultiply:*op,small);
        return join(Adjacent,join(Adjacent,a,symbol),b);
    }
    if (end-start >= 3 && !memcmp(start, "+/-", 3)) {
        int sign = leaf(start,3,0,small);
        return join(Adjacent,sign,parse_math(start+3,end,small,depth+1));
    }
    for (const char *p=start;p<end;p++) {
        if (*p!='(') continue;
        const char *close = closing(p,end);
        if (!close) break;
        bool root = p-start>=4 && !strncmp(p-4,"sqrt",4);
        const char *prefix_end = root ? p-4 : p;
        int child = parse_math(p+1,close,small,depth+1);
        int group = join(root?Radical:Parentheses,child,0);
        if (prefix_end>start) {
            int prefix = parse_math(start,prefix_end,small,depth+1);
            group = join(Adjacent,prefix,group);
        }
        if (close+1<end) {
            int suffix = parse_math(close+1,end,small,depth+1);
            group = join(Adjacent,group,suffix);
        }
        return group;
    }
    for (const char *p=start+1;p+2<end;p++) {
        if (*p != '_' || p[1] != '{') continue;
        const char *close = memchr(p+2, '}', (size_t)(end-p-2));
        if (!close) break;
        int base = parse_math(start,p,small,depth+1);
        int sub = leaf(p+2,(int)(close-p-2),0,true);
        int value = join(Lowered,base,sub);
        if (close+1<end) value=join(Adjacent,value,parse_math(close+1,end,small,depth+1));
        return value;
    }
    for (const char *p=start;p+1<end;p++) {
        if (p[0]!='p' || p[1]!='i') continue;
        if (p>start && isalpha((unsigned char)p[-1])) continue;
        if (p+2<end && isalpha((unsigned char)p[2])) continue;
        int value = leaf(NULL,0,MathPi,small);
        if (p>start) value=join(Adjacent,parse_math(start,p,small,depth+1),value);
        if (p+2<end) value=join(Adjacent,value,parse_math(p+2,end,small,depth+1));
        return value;
    }
    return leaf(start,(int)(end-start),0,small);
}

static int parse_math(const char *start,const char *end,bool small,int depth) {
    int result = parse_span(start,end,small,depth);
    if (result) {
        layouts[result].start = start;
        layouts[result].end = end;
    }
    return result;
}

static int prepare(const char *text,int width,bool big) {
    count=0;
    large=big;
    overflow=false;
    int root = parse_math(text,text+strlen(text),false,0);
    if (overflow || !root || layouts[root].box.width>width ||
        layouts[root].box.above+layouts[root].box.below>68) {
        count=0;
        int length=(int)strlen(text);
        while (length && platform_width(text,length,false,false)>width) length--;
        root=leaf(text,length,0,false);
    }
    return root;
}

MathBox measure_math(const char *text,int width) {
    return layouts[prepare(text,width,false)].box;
}

MathBox measure_calculation(const char *text,int width) {
    return layouts[prepare(text,width,true)].box;
}

static void paint(int id,int x,int mid,const MathCanvas *c,int depth) {
    if (!id) return;
    const Layout *l=&layouts[id], *a=&layouts[l->a], *b=&layouts[l->b];
    if (cursor && l->start && l->end && cursor >= l->start && cursor <= l->end && depth >= caret_depth) {
        int offset = cursor == l->end ? l->box.width : 0;
        bool match = cursor == l->start || cursor == l->end;
        if (l->kind == Text && l->text && cursor >= l->text && cursor <= l->text + l->length) {
            offset = platform_width(l->text, (int)(cursor - l->text), l->small, false);
            match = true;
        }
        if (match) {
            caret = (MathCaret){x+offset,mid-l->box.above,l->box.above+l->box.below};
            caret_depth = depth;
        }
    }
    switch (l->kind) {
        case Text: {
            char text[LayoutChars+1];
            if (l->single) { text[0]=l->single; text[1]=0; }
            else {
                int length=l->length<LayoutChars?l->length:LayoutChars;
                memcpy(text,l->text,(size_t)length);
                text[length]=0;
            }
            c->text(x+l->pad,mid-l->box.above,text,c->ink,c->paper,l->small);
            break;
        }
        case Adjacent:
            paint(l->a,x,mid,c,depth+1);
            paint(l->b,x+a->box.width+(a->box.width && b->box.width ? 1 : 0),mid,c,depth+1);
            break;
        case Fraction:
            c->rect(x,mid,l->box.width,1,c->ink);
            paint(l->a,x+(l->box.width-a->box.width)/2,mid-a->box.below-1,c,depth+1);
            paint(l->b,x+(l->box.width-b->box.width)/2,mid+b->box.above+(b->small ? 2 : 1),c,depth+1);
            break;
        case Raised:
            paint(l->a,x,mid,c,depth+1);
            paint(l->b,x+a->box.width+1,mid-a->box.above-b->box.below+(b->box.above+b->box.below>8 ? 1 : 4),c,depth+1);
            break;
        case Lowered:
            paint(l->a,x,mid,c,depth+1);
            paint(l->b,x+a->box.width+1,mid+a->box.below+b->box.above-4,c,depth+1);
            break;
        case Radical: {
            int top=mid-a->box.above-2, bottom=mid+max(a->box.below-2,2);
            c->rect(x,mid+1,2,1,c->ink);
            for (int y=mid+1;y<=bottom;y++) c->rect(x+2+(y-mid-1)/2,y,1,1,c->ink);
            for (int y=top;y<=bottom;y++) c->rect(x+4+(bottom-y)*3/(bottom-top),y,1,1,c->ink);
            c->rect(x+7,top,l->box.width-7,1,c->ink);
            paint(l->a,x+9,mid,c,depth+1);
            break;
        }
        case Parentheses: {
            int bracket = platform_width("(",1,l->small,false);
            int padding = bracket + 1;
            int close_x = x + padding + a->box.width + 1;
            paint(l->a,x+padding,mid,c,depth+1);
            if (a->box.above + a->box.below <= 2 * half_height(l->small)) {
                int top = mid - (l->small ? 3 : 5);
                c->text(x,top,"(",c->ink,c->paper,l->small);
                c->text(close_x,top,")",c->ink,c->paper,l->small);
            } else {
                int top = mid-l->box.above+1, bottom = mid+l->box.below-1;
                for (int y=top;y<=bottom;y++) {
                    int distance = y-top < bottom-y ? y-top : bottom-y;
                    int curve = distance >= bracket-1 ? 0 : bracket-1-distance;
                    c->rect(x+curve,y,1,1,c->ink);
                    c->rect(close_x+bracket-1-curve,y,1,1,c->ink);
                }
            }
            break;
        }
    }
}

void paint_math(const char *text,int width,int x,int mid,const MathCanvas *canvas) {
    paint(prepare(text,width,false),x,mid,canvas,0);
}

void paint_calculation(const char *text,int width,int x,int mid,const MathCanvas *canvas) {
    paint(prepare(text,width,true),x,mid,canvas,0);
}

MathCaret paint_math_input(const char *text,int width,int x,int mid,const MathCanvas *canvas,
                           int position,bool big) {
    int id = prepare(text,width,big);
    MathBox box = layouts[id].box;
    caret = (MathCaret){x+box.width,mid-box.above,box.above+box.below};
    caret_depth = -1;
    cursor = text+position;
    paint(id,x,mid,canvas,0);
    cursor = NULL;
    return caret;
}
