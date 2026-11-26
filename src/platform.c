#include "eadk.h"
#include <graphx.h>
#include <keypadc.h>
#include <tice.h>

static bool dirty;
void platform_init(void) {
    gfx_Begin();
    gfx_SetDrawBuffer();
    gfx_SetTextConfig(gfx_text_clip);
    uint16_t palette[256];
    for(unsigned i=0;i<256;i++) {
        unsigned r=(i>>5)*31/7,g=((i>>2)&7)*63/7,b=(i&3)*31/3;
        palette[i]=(r<<10)|((g>>1)<<5)|b|((g&1)<<15);
    }
    gfx_SetPalette(palette,sizeof(palette),0);
    gfx_SetTextBGColor(254);
    gfx_SetTextTransparentColor(254);
}
void platform_end(void) { gfx_End(); }

static uint8_t color(uint16_t rgb) {
    return ((rgb >> 8) & 0xe0) | ((rgb >> 6) & 0x1c) | ((rgb >> 3) & 3);
}

void eadk_display_push_rect_uniform(eadk_rect_t rect, eadk_color_t ink) {
    gfx_SetColor(color(ink));
    gfx_FillRectangle(rect.x, rect.y, rect.width, rect.height);
    dirty = true;
}

void eadk_display_push_rect(eadk_rect_t rect, const eadk_color_t *pixels) {
    for (unsigned y=0; y<rect.height && rect.y+y<240; y++)
        for (unsigned x=0; x<rect.width && rect.x+x<320; x++) {
            gfx_SetColor(color(pixels[y*rect.width+x]));
            gfx_SetPixel(rect.x+x,rect.y+y);
        }
    dirty = true;
}

static char display_char(const char **text) {
    const unsigned char *p=(const unsigned char *)*text;
    unsigned char c=*p++;
    char result;
    switch(c) {
        case 24: result='O';break;
        case 25: result='v';break;
        case 26: result='2';break;
        case 28: result='/';break;
        case 29: result='x';break;
        case 30: result='p';break;
        case 31: result='~';break;
        default:
            result=c>=32&&c<127?c:'?';
            if(c==0xe2&&p[0]&&p[1]){
                if(p[0]==0x80&&p[1]>=0x90&&p[1]<=0x94)result='-';
                else if(p[0]==0x80&&p[1]>=0x98&&p[1]<=0x99)result='\'';
                else if(p[0]==0x80&&p[1]>=0x9c&&p[1]<=0x9d)result='"';
                else if(p[0]==0x88&&p[1]==0x92)result='-';
            }
            if(c==0xc2&&p[0]==0xb0)result='o';
            if(c==0xc3&&p[0]==0x97)result='x';
            if(c>=0xc0)while((*p&0xc0)==0x80)p++;
    }
    *text=(const char *)p;
    return result;
}

int platform_width(const char *text, int length, bool small, bool bold) {
    (void)small;
    int width=0;
    const char *start=text;
    while(*text&&(length<0||text-start<length))width+=gfx_GetCharWidth(display_char(&text));
    return width+(bold && width!=0);
}

void platform_text(int x, int y, const char *text, uint16_t ink, uint16_t paper,
                   bool small, bool large, bool bold) {
    (void)paper; (void)small; (void)large;
    gfx_SetTextFGColor(color(ink));
    while(*text && x<320) {
        char ch=display_char(&text);
        if(x>=0) {
            gfx_SetTextXY(x,y);
            gfx_PrintChar(ch);
            if(bold){gfx_SetTextXY(x+1,y);gfx_PrintChar(ch);}
        }
        x+=gfx_GetCharWidth(ch);
    }
    dirty=true;
}

typedef struct { kb_lkey_t physical; eadk_key_t logical; } KeyBinding;
#define KEY(ti, app) {kb_Key##ti, eadk_key_##app}
static const KeyBinding keypad[] = {
    KEY(Left,left), KEY(Up,up), KEY(Down,down), KEY(Right,right),
    KEY(Enter,exe), KEY(Clear,back), KEY(Mode,home), KEY(2nd,shift), KEY(Alpha,alpha),
    KEY(GraphVar,xnt), KEY(Vars,var), KEY(Math,toolbox), KEY(Del,backspace),
    KEY(Yequ,fraction), KEY(Window,format), KEY(Zoom,settings),
    KEY(Trace,prevtab), KEY(Graph,nexttab), KEY(Stat,clear), KEY(Apps,variable),
    KEY(Prgm,exp), KEY(Sto,store), KEY(Ln,ln), KEY(Log,log), KEY(Recip,imaginary),
    KEY(Comma,comma), KEY(Power,power), KEY(Sin,sine), KEY(Cos,cosine),
    KEY(Tan,tangent), KEY(Square,square), KEY(Chs,pi),
    KEY(LParen,left_parenthesis), KEY(RParen,right_parenthesis),
    KEY(7,seven), KEY(8,eight), KEY(9,nine), KEY(4,four), KEY(5,five), KEY(6,six),
    KEY(Mul,multiplication), KEY(Div,division), KEY(1,one), KEY(2,two), KEY(3,three),
    KEY(Add,plus), KEY(Sub,minus), KEY(0,zero), KEY(DecPnt,dot)
};
eadk_keyboard_state_t eadk_keyboard_scan(void) {
    eadk_keyboard_state_t state=0;
    kb_Scan();
    for(unsigned i=0;i<sizeof(keypad)/sizeof(*keypad);i++)
        if(kb_IsDown(keypad[i].physical))state|=UINT64_C(1)<<keypad[i].logical;
    return state;
}

void eadk_timing_msleep(uint32_t ms) {
    if(dirty){gfx_SwapDraw();dirty=false;}
    if(ms)delay(ms);
}

char platform_alpha(int key) {
    static const char letters[64]={
        [eadk_key_toolbox]='A',[eadk_key_variable]='B',[eadk_key_exp]='C',
        [eadk_key_imaginary]='D',[eadk_key_sine]='E',[eadk_key_cosine]='F',
        [eadk_key_tangent]='G',[eadk_key_power]='H',[eadk_key_square]='I',
        [eadk_key_comma]='J',[eadk_key_left_parenthesis]='K',[eadk_key_right_parenthesis]='L',
        [eadk_key_division]='M',[eadk_key_log]='N',[eadk_key_seven]='O',
        [eadk_key_eight]='P',[eadk_key_nine]='Q',[eadk_key_multiplication]='R',
        [eadk_key_ln]='S',[eadk_key_four]='T',[eadk_key_five]='U',
        [eadk_key_six]='V',[eadk_key_minus]='W',[eadk_key_store]='X',
        [eadk_key_one]='Y',[eadk_key_two]='Z',[eadk_key_zero]=' ',
        [eadk_key_dot]=':',[eadk_key_plus]='"'
    };
    return letters[key];
}
