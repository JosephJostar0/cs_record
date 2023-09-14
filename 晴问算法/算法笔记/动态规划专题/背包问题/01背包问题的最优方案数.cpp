#include <iostream>
const int maxn = 100 + 1;
const int maxv = 1000 + 1;
int n, V, w[maxn], c[maxn], dp[maxv], ans[maxv];
int main() {
    scanf("%d%d", &n, &V);
    int i, j;
    for (i = 1; i <= n; i++)
        scanf("%d", w + i);
    for (i = 1; i <= n; i++)
        scanf("%d", c + i);
    std::fill(ans, ans + V, 1);
    for (i = 1; i <= n; i++)
        for (j = V; j >= w[i]; j--) {
            int temp = j - w[i];
            if (dp[temp] + c[i] > dp[j]) {
                dp[j] = dp[temp] + c[i];
                ans[j] = ans[temp];
            } else if (dp[temp] + c[i] == dp[j])
                ans[j] += ans[temp], ans[j] %= 10007;
        }
    printf("%d %d", dp[V], ans[V]);
    return 0;
}
