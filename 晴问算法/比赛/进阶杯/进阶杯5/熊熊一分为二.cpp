#include <iostream>
#define MOD 1000000007 * 2
#define MAXN 301
#define MAXSUM 150 * 301 + 1
long long n, total, dp[MAXSUM], top;
int main() {
    scanf("%d", &n);
    total = (n * (n + 1)) / 2;
    if (total % 2) {
        printf("0");
        return 0;
    }
    dp[0] = 1, top = total / 2;
    for (int i = 1; i <= n; i++)
        for (int j = top; j >= i; j--) {
            dp[j] += dp[j - i];
            dp[j] %= MOD;
        }
    printf("%lld", dp[top] / 2);
    return 0;
}