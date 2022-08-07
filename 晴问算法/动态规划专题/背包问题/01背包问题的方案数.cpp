#include <iostream>
#define MAXN 100 + 1
#define MAXV 1000 + 1
int n, V, w[MAXN], dp[MAXV];
int main() {
    scanf("%d%d", &n, &V);
    int i, j;
    for (i = 1; i <= n; i++)
        scanf("%d", w + i);
    dp[0] = 1;
    for (i = 1; i <= n; i++)
        for (j = V; j >= w[i]; j--)
            dp[j] += dp[j - w[i]], dp[j] %= 10007;
    printf("%d", dp[V]);
    return 0;
}
