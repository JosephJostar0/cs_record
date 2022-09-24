#include <iostream>
long long myMul(int x, int y) {
    printf("the answer is:\n%d * %d  =  ", x, y);
    int more = 0, ans = 0;
    unsigned int low = 0;
    for (int i = 0; i <= 32; i++) {
        int plus = more - (y & 1);
        if (plus == 1)
            ans += x;
        else if (plus == -1)
            ans -= x;
        if (i == 32)
            break;
        more = (y & 1);
        y >>= 1;
        low >>= 1, low += 0x80000000 * (ans & 1);
        ans >>= 1;
    }
    long long last = (long long)ans * 0x100000000 + (long long)low;
    printf("0x%08x %08x  = %lld", ans, low, last, last);
    return last;
}

int main() {
    int x, y;
    while (1) {
        printf("Please enter the multipliers, both of which are integers, separated by a space:\n");
        if (scanf("%d %d", &x, &y) == 2) {
            myMul(x, y);
            break;
        } else {
            printf("format wrong! please reinput\n");
            system("pause");
            system("cls");
            fflush(stdin);
        }
    }
    return 0;
}
