#include "hex_out.h"
int main() {
    unsigned int uc = 254;
    char c = uc;
    int i;
    unsigned ui;
    i = uc;
    ui = uc;
    out_1byte(&uc);
    printf(" = uc =%d\n", uc); //无符号小字长转大字长，高位补0
    out_4byte(&i);
    printf(" = i = %d\n", i);
    out_4byte(&ui);
    printf(" = ui = %u\n", ui);
    i = c;
    ui = c;
    out_1byte(&c);
    printf(" = c = %d\n", c); //有符号小字长转大字长，机器码符号扩展
    out_4byte(&i);
    printf(" = i = %d\n", i);
    out_4byte(&ui);
    printf(" = ui = %u", ui);
}