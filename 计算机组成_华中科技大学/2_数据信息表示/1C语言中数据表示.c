#include "hex_out.h"
#include <stdio.h>
union {
    int i;
    unsigned int ui;
    float f;
    short s;
    unsigned short us;
    char c;
    unsigned char uc;
} t;

int main() {
    t.i = 0xc77fffff;         //直接通过机器码复制，联合体中所有变量共享该机器码
    out_4byte((char *)&t.i);  //输出i的机器码和真值，&表示引用变量的内存地址
    printf(" = %d \n", t.i);  // c77fffff=-947912705
    out_4byte((char *)&t.ui); //输出ui的机器码和真值
    printf(" = %u\n", t.ui);  // c77fffff=3347054591

    out_4byte((char *)&t.f);
    printf(" = %f\n", t.f); // C77FFFFF=-65535.996094

    out_2byte((char *)&t.s);
    printf(" = %d\n", t.s); // FFFF=-1
    out_2byte((char *)&t.us);
    printf(" = %u\n", t.us); // FFFF=65535

    out_1byte(&t.c);
    printf(" = %d\n", t.c); // FF=-1
    out_1byte(&t.uc);
    printf(" = %u\n", t.uc); // FF=255
    return 0;
}