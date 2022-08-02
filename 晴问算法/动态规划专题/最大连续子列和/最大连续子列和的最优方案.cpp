#include <iostream>
int main() {
    int dp[10000], begin[10000], n, i, ans;
    scanf("%d%d", &n, dp);
    for (i = 1, ans = 0, begin[0] = 0; i < n; i++) {
        scanf("%d", dp + i);
        begin[i] = i;
        if (dp[i - 1] >= 0)
            dp[i] += dp[i - 1], begin[i] = begin[i - 1];
        if (dp[i] > dp[ans])
            ans = i;
    }
    printf("%d %d %d", dp[ans], begin[ans] + 1, ans + 1);
    return 0;
}
