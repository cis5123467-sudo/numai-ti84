#include "number.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

void number_text(char *out, size_t capacity, long double value,
                 NumberFormat format, int precision)
{
    if(!capacity)return;
    if(value==0)value=0;
    if(!isfinite(value)) {
        snprintf(out,capacity,"%s",isnan(value)?"nan":value<0?"-inf":"inf");
        return;
    }

    // CEdev's printf handles %Lf, but does not implement decimal exponents.
    long double mantissa=fabsl(value);
    int exponent=0;
    if(mantissa!=0) {
        while(mantissa>=1e32L){mantissa/=1e32L;exponent+=32;}
        while(mantissa<1e-31L){mantissa*=1e32L;exponent-=32;}
        while(mantissa>=10){mantissa/=10;exponent++;}
        while(mantissa<1){mantissa*=10;exponent--;}
    }
    if(format==NumberFixed && exponent+precision<19) {
        snprintf(out,capacity,"%.*Lf",precision,value);
        return;
    }

    int decimals=format==NumberGeneral?precision-1:precision;
    char digits[24];
    snprintf(digits,sizeof(digits),"%.*Lf",decimals,mantissa);
    if(digits[1]=='0') {
        exponent++;
        snprintf(digits,sizeof(digits),"%.*Lf",decimals,1.0L);
    }

    if(format==NumberGeneral && decimals) {
        size_t length=strlen(digits);
        while(length>1 && digits[length-1]=='0')digits[--length]=0;
        if(digits[length-1]=='.')digits[--length]=0;
    }
    const char *sign=value<0?"-":"";
    if(format!=NumberGeneral || exponent<-4 || exponent>=precision) {
        snprintf(out,capacity,"%s%se%+d",sign,digits,exponent);
        return;
    }

    // Reposition the decimal point using the already rounded digits.
    char plain[24];
    int count=0;
    for(const char *p=digits;*p;p++)if(*p!='.')plain[count++]=*p;
    char expanded[32];
    size_t end=0;
    int point=exponent+1;
    if(point<=0) {
        expanded[end++]='0';
        expanded[end++]='.';
        for(int i=0;i< -point;i++)expanded[end++]='0';
    }
    for(int i=0;i<count || i<point;i++) {
        if(i==point && i>0)expanded[end++]='.';
        expanded[end++]=i<count?plain[i]:'0';
    }
    expanded[end]=0;
    snprintf(out,capacity,"%s%s",sign,expanded);
}
