#include <iostream>
#define MAXN 1000
int n, a[MAXN], ans = 0xbadbeef;
int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", a + i);
    for (int num = -100; num <= 100; num++) {
        int temp = 0;
        for (int i = 0; i < n; i++) {
            int val = std::abs(num - a[i]);
            temp += i & 1 ? val : -val;
        }
        if (temp < ans)
            ans = temp;
    }
    printf("%d", ans);
    return 0;
}
