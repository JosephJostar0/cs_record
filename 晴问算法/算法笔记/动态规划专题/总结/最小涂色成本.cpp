#include <iostream>
#define MAXN 10000
int cost[MAXN][3], dp[MAXN][3];
int DP(int x, int i) {
    if (dp[x][i])
        return dp[x][i];
    int c0 = DP(x - 1, 0);
    int c1 = DP(x - 1, 1);
    int c2 = DP(x - 1, 2);
    dp[x][0] = cost[x][0] + std::min(c1, c2);
    dp[x][1] = cost[x][1] + std::min(c0, c2);
    dp[x][2] = cost[x][2] + std::min(c0, c1);
    return dp[x][i];
}

int main() {
    int n, i, j;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
        for (j = 0; j < 3; j++)
            scanf("%d", &cost[i][j]);
    for (i = 0; i < 3; i++)
        dp[0][i] = cost[0][i];
    i = std::min(DP(n - 1, 0), DP(n - 1, 1));
    printf("%d", std::min(i, DP(n - 1, 2)));
    return 0;
}
