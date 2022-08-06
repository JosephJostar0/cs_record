#include <iostream>
#define MAXN 100
int n, m, G[MAXN][MAXN], dp[MAXN], step[MAXN];
int dag(int x) {
    if (dp[x])
        return dp[x];
    for (int i = 0; i < n; i++)
        if (G[x][i]) {
            int temp = dag(i) + G[x][i];
            if (temp > dp[x])
                dp[x] = temp, step[x] = i;
        }
    return dp[x];
}

int main() {
    scanf("%d%d", &n, &m);
    std::fill(step, step + n, -1);
    int i, x, y, z;
    for (i = 0; i < m; i++) {
        scanf("%d%d%d", &x, &y, &z);
        G[x][y] = z;
    }
    for (i = 1, z = 0; i < n; i++)
        if (dag(z) < dag(i))
            z = i;
    printf("%d", z);
    while (step[z] != -1)
        z = step[z], printf("->%d", z);
    return 0;
}
