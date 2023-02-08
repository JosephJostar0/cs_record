#include <iostream>
#define MOD 10007
#define MAXN 10001
int dp[MAXN];
int main() {
    dp[0] = 1, dp[1] = 9;
    int n;
    scanf("%d", &n);
    for (int i = 2; i <= n; i++)
        dp[i] = 9 * (dp[i - 1] + dp[i - 2]) % MOD;
    printf("%d", (dp[n] + dp[n - 1]) % MOD);
    return 0;
}
