#include <iostream>
#define MAXN 100
#define MAXM 100
int G[MAXN][MAXM], dp[MAXN][MAXM];
int DP(int x, int y) {
    if (dp[x][y])
        return dp[x][y];
    int left = y == 0 ? 0 : DP(x, y - 1);
    int up = x == 0 ? 0 : DP(x - 1, y);
    dp[x][y] = G[x][y] + std::max(left, up);
    return dp[x][y];
}

int main() {
    int n, m, i, j;
    scanf("%d%d", &n, &m);
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &G[i][j]);
    dp[0][0] = G[0][0];
    printf("%d", DP(n - 1, m - 1));
    return 0;
}
