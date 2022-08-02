#include <iostream>
int main() {
    int dp[10000], n, i, ans;
    scanf("%d%d", &n, dp);
    for (i = 1, ans = dp[0]; i < n; i++) {
        scanf("%d", dp + i);
        if (dp[i - 1] > 0)
            dp[i] += dp[i - 1];
        ans = std::max(dp[i], ans);
    }
    printf("%d", ans);
    return 0;
}
