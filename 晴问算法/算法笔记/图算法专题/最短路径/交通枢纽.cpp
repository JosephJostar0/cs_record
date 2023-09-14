#include <iostream>
#define INF 0xbadbeef
int n, m, k, dis[100][100], visit[100], len[100];

void dijkstra(int s) {
    std::fill(len, len + n, INF);
    std::fill(visit, visit + n, 0);
    len[s] = 0;
    for (int i = 0; i < n; i++) {
        int MIN = INF, u;
        for (int j = 0; j < n; j++)
            if (!visit[j] && len[j] < MIN)
                u = j, MIN = len[j];
        if (MIN == INF)
            break;
        visit[u] = 1;
        for (int v = 0; v < n; v++)
            if (!visit[v] && dis[u][v])
                if (len[v] > len[u] + dis[u][v])
                    len[v] = len[u] + dis[u][v];
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    int i, x, y, z, MIN = INF, ans;
    for (i = 0; i < m; i++) {
        scanf("%d%d%d", &x, &y, &z);
        dis[x][y] = dis[y][x] = z;
    }
    for (i = 0; i < k; i++) {
        scanf("%d", &x);
        dijkstra(x);
        for (y = 0, z = 0; y < n; y++)
            z += len[y];
        if (z < MIN)
            MIN = z, ans = x;
    }
    printf("%d %d", ans, MIN);
    return 0;
}
