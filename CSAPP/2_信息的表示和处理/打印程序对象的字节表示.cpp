#include <stdio.h>
typedef unsigned char *byte_pointer;
void show_bytes(byte_pointer start, size_t len) {
    size_t i;
    for (i = 0; i < len; i++)
        printf(" %.2x", start[i]);
    printf("\n");
}

void show(int x) { show_bytes((byte_pointer)&x, sizeof(int)); }

void show(float x) { show_bytes((byte_pointer)&x, sizeof(float)); }

void show(void *x) { show_bytes((byte_pointer)&x, sizeof(void *)); }

void test_show_bytes(int val) {
    int ival = val;
    float fval = (float)val;
    int *pval = &ival;
    show(ival);
    show(fval);
    show(pval);
}

int main() {
    test_show_bytes(12345);
    return 0;
}