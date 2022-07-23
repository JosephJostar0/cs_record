#include <iostream>
#define INF 0xbadbeef
int n, m, s, t, dis[100][100], weight[100], visit[100], pre[100];
int len[100], count[100], flag;
double car[100];

void dijkstra() {
    len[s] = 0, car[s] = (double)weight[s], count[s] = 1;
    for (int i = 0; i < n; i++) {
        int MIN = INF, u;
        for (int j = 0; j < n; j++)
            if (!visit[j] && len[j] < MIN)
                u = j, MIN = len[j];
        if (MIN == INF)
            break;
        visit[u] = 1;
        for (int v = 0; v < n; v++)
            if (!visit[v] && dis[u][v]) {
                if (len[v] > len[u] + dis[u][v]) {
                    len[v] = len[u] + dis[u][v];
                    pre[v] = u;
                    count[v] = count[u] + 1;
                    car[v] = (car[u] * count[u] + weight[v]) / count[v];
                } else if (len[v] == len[u] + dis[u][v])
                    if (car[v] > (car[u] * count[u] + weight[v]) / (count[u] + 1)) {
                        pre[v] = u;
                        count[v] = count[u] + 1;
                        car[v] = (car[u] * count[u] + weight[v]) / count[v];
                    }
            }
    }
}

void dfs(int g = t) {
    if (pre[g] != -1)
        dfs(pre[g]);
    if (flag)
        printf("->");
    printf("%d", g);
    flag = 1;
}

int main() {
    std::fill(len, len + 100, INF);
    std::fill(car, car + 100, 200.0);
    std::fill(pre, pre + 100, -1);
    scanf("%d%d%d%d", &n, &m, &s, &t);
    int i, x, y, z;
    for (i = 0; i < n; i++)
        scanf("%d", weight + i);
    for (i = 0; i < m; i++) {
        scanf("%d%d%d", &x, &y, &z);
        dis[x][y] = dis[y][x] = z;
    }
    dijkstra();
    printf("%d ", len[t]);
    dfs();
    return 0;
}
