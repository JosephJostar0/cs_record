#include <iostream>
#define MAXN 100
int n, m, G[MAXN][MAXN], dp[MAXN];
int dag(int x) {
    if (dp[x])
        return dp[x];
    for (int i = 0; i < n; i++)
        if (G[x][i])
            dp[x] = std::max(dp[x], dag(i) + G[x][i]);
    return dp[x];
}

int main() {
    scanf("%d%d", &n, &m);
    int i, x, y, z;
    for (i = 0; i < m; i++) {
        scanf("%d%d%d", &x, &y, &z);
        G[x][y] = z;
    }
    for (i = 0, z = 0; i < n; i++)
        z = std::max(z, dag(i));
    printf("%d", z);
    return 0;
}
