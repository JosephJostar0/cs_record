#include <iostream>
#define MAXN 100
#define INF 0xbadbeef
int n, m, tar, G[MAXN][MAXN], dp[MAXN], visit[MAXN];
int dag(int x) {
    if (visit[x])
        return dp[x];
    visit[x] = 1;
    for (int i = 0; i < n; i++)
        if (G[x][i])
            dp[x] = std::max(dp[x], dag(i) + G[x][i]);
    return dp[x];
}

int main() {
    scanf("%d%d%d", &n, &m, &tar);
    std::fill(dp, dp + n, -INF);
    int i, x, y, z;
    dp[tar] = 0;
    for (i = 0; i < m; i++) {
        scanf("%d%d%d", &x, &y, &z);
        G[x][y] = z;
    }
    for (i = 0, z = 0; i < n; i++)
        z = std::max(z, dag(i));
    printf("%d", z);
    return 0;
}
