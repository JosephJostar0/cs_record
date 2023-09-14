#include <iostream>
#define MAXN 100 + 1
#define MAXV 1000 + 1
int n, V, dp[MAXV], w[MAXN], c[MAXN], flag;
int main() {
    scanf("%d%d", &n, &V);
    int i, j;
    for (i = 1; i <= n; i++)
        scanf("%d", w + i);
    for (i = 1; i <= n; i++)
        scanf("%d", c + i);
    for (i = 1; i <= n; i++)
        for (j = w[i]; j <= V; j++)
            dp[j] = std::max(dp[j], dp[j - w[i]] + c[i]);
    printf("%d", dp[V]);
    return 0;
}
