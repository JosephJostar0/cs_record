#include <iostream>
#define INF 0xbadbeef
int n, m, s, t, map[100][100], visit[100], dis[100], link[100];
void dijkstra(int s) {
    dis[s] = 0, link[s] = 1;
    for (int i = 0; i < n; i++) {
        int MIN = INF, u;
        for (int j = 0; j < n; j++)
            if (!visit[j] && dis[j] < MIN)
                u = j, MIN = dis[j];
        if (MIN == INF)
            break;
        visit[u] = 1;
        for (int v = 0; v < n; v++)
            if (!visit[v] && map[u][v] < INF) {
                if (dis[v] > dis[u] + map[u][v])
                    dis[v] = dis[u] + map[u][v], link[v] = link[u];
                else if (dis[v] == dis[u] + map[u][v])
                    link[v] += link[u];
            }
    }
}

int main() {
    scanf("%d%d%d%d", &n, &m, &s, &t);
    std::fill(dis, dis + n, INF);
    std::fill(map[0], map[0] + 100 * 100, INF);
    int i, p, q, j;
    for (i = 0; i < m; i++) {
        scanf("%d%d%d", &p, &q, &j);
        map[p][q] = map[q][p] = j;
    }
    dijkstra(s);
    printf("%d %d", dis[t], link[t]);
    return 0;
}
