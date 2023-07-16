#include <stdio.h>
#include <stdlib.h>
#define size (sizeof(int) - 1 << 3)
int main() {
    // 0,-1,0xyyyyFFFF,0x0000yyyy
    int x;
    printf("input an integer:");
    if (scanf("%d", &x))
        printf("%d", !~x || !x || !~(x | ~0xFF) || !(x >> (sizeof(int) - 1 << 3)) & 0xFF);
    // printf("%d\n", !~x || !x || !~((x << (size) >> (size))) || !(x >> size));
    return 0;
}
