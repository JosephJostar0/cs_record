#include <iostream>
#define INF 0xbadbeef
int n, m, s, t;
int map[100][100], take[100][100], visit[100], dis[100], cost[100];

void dijkstra(int s) {
    dis[s] = 0, cost[s] = 0;
    for (int i = 0; i < n; i++) {
        int MIN = INF, u, need = INF;
        for (int j = 0; j < n; j++)
            if (!visit[j])
                if (dis[j] < MIN)
                    u = j, MIN = dis[j], need = cost[j];
        if (MIN == INF)
            break;
        visit[u] = 1;
        for (int v = 0; v < n; v++)
            if (!visit[v] && map[u][v] < INF) {
                if (dis[v] > dis[u] + map[u][v])
                    dis[v] = dis[u] + map[u][v], cost[v] = cost[u] + take[u][v];
                else if (dis[v] == dis[u] + map[u][v])
                    if (cost[v] > cost[u] + take[u][v])
                        cost[v] = cost[u] + take[u][v];
            }
    }
}

int main() {
    scanf("%d%d%d%d", &n, &m, &s, &t);
    std::fill(dis, dis + n, INF);
    std::fill(map[0], map[0] + 100 * 100, INF);
    std::fill(take[0], take[0] + 100 * 100, INF);
    std::fill(cost, cost + n, INF);
    int i, p, q, j, k;
    for (i = 0; i < m; i++) {
        scanf("%d%d%d%d", &p, &q, &j, &k);
        map[p][q] = map[q][p] = j;
        take[p][q] = take[q][p] = k;
    }
    dijkstra(s);
    printf("%d %d", dis[t], cost[t]);
    return 0;
}
