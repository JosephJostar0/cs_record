#include <iostream>
int main() {
    int n, cnt = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        cnt += a == b ? 0 : (a > b ? 1 : -1);
    }
    printf("%c", cnt == 0 ? 'C' : (cnt > 0 ? 'A' : 'B'));
    return 0;
}
