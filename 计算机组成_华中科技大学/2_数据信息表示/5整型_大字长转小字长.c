#include "hex_out.h"
int main() {
    int i = 0xFFFF1001;
    short s;
    unsigned short us;
    s = i;
    us = i;
    out_4byte(&i);
    printf(" = i = %d\n", i);
    out_2byte(&s);
    printf(" = s = %d\n", s); //大字长转小字长，机器码被截短
    out_2byte(&us);
    printf(" = us = %u", us);
}