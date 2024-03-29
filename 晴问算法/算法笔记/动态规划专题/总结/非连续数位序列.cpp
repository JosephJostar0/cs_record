#include <iostream>
#define MOD 10007
#define MAXN 10000
int dp[MAXN][2];
int DP(int n, int i) {
    if (dp[n][i])
        return dp[n][i];
    int zero = DP(n - 1, 0);
    int not_zero = DP(n - 1, 1);
    dp[n][0] = not_zero % MOD;
    dp[n][1] = (not_zero + zero) * 9 % MOD;
    return dp[n][i];
}

int main() {
    int n;
    scanf("%d", &n);
    dp[1][0] = 1, dp[1][1] = 9;
    printf("%d", (DP(n, 0) + DP(n, 1)) % MOD);
    return 0;
}
