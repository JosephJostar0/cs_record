#include "hex_out.h"
#include <stdio.h>
int main() {
    unsigned char uc1 = 255, uc;
    char c1 = -127, c;
    c = (char)uc1;
    out_1byte(&uc1);
    printf(" = uc1 = %u\n", uc1);
    out_1byte(&c);
    printf(" = c = %d\n", c);
    uc = c1;
    out_1byte(&c1);
    printf(" = c1 = %d\n", c1);
    out_1byte(&uc);
    printf(" = uc = %u\n", uc);
    return 0;
}