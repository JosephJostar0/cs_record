#include <iostream>
#define MAXN 101
#define MAXW 100000001
#define MAXV 100001
int n, W, weight, value, dp[MAXV], ans;
int main() {
    std::fill(dp + 1, dp + MAXV, MAXW + 1);
    scanf("%d %d", &n, &W);
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &weight, &value);
        for (int j = MAXV; j >= value; j--)
            if (dp[j - value] + weight < dp[j]) {
                dp[j] = dp[j - value] + weight;
                if (dp[j] <= W && j > ans)
                    ans = j;
            }
    }
    printf("%d", ans);
    return 0;
}
