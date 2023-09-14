#include <algorithm>
#include <iostream>
#include <vector>
#define INF 0xbadbeef
int n, m, s, t, flag, del;
int map[100][100], visit[100], dis[100], link[100];
std::vector<int> pre[100], temp;
std::vector<std::vector<int>> paths;

void dijkstra() {
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
                if (dis[v] > dis[u] + map[u][v]) {
                    dis[v] = dis[u] + map[u][v];
                    pre[v].clear();
                    pre[v].push_back(u);
                    link[v] = link[u];
                } else if (dis[v] == dis[u] + map[u][v])
                    pre[v].push_back(u), link[v] += link[u];
            }
    }
}

void dfs(int g) {
    temp.push_back(g);
    if (pre[g].empty())
        paths.push_back(temp);
    for (int i = 0; i < pre[g].size(); i++)
        dfs(pre[g][i]);
    temp.pop_back();
}

int main() {
    scanf("%d%d%d%d", &n, &m, &s, &t);
    std::fill(dis, dis + n, INF);
    std::fill(map[0], map[0] + 100 * 100, INF);
    int i, p, q, j, k;
    for (i = 0; i < m; i++) {
        scanf("%d%d%d", &p, &q, &j);
        map[p][q] = map[q][p] = j;
    }
    dijkstra();
    dfs(t);
    for (i = 0; i < link[t]; i++)
        std::reverse(paths[i].begin(), paths[i].end());
    std::sort(paths.begin(), paths.end());
    printf("%d", link[t]);
    for (i = 0; i < link[t]; i++) {
        printf("\n");
        temp = paths[i];
        printf("%d", temp[0]);
        for (j = 1; j < temp.size(); j++)
            printf("->%d", temp[j]);
    }
    return 0;
}
