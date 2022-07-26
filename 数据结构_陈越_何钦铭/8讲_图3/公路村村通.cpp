#include <iostream>
#define INF 0xbadbeef
int N, M, map[1000][1000], dis[1000], visit[1000], ans;
void prim(int s) {
    dis[s] = 0;
    for (int i = 0; i < N; i++) {
        int MIN = INF, u;
        for (int j = 0; j < N; j++)
            if (!visit[j] && dis[j] < MIN)
                u = j, MIN = dis[j];
        if (MIN == INF)
            break;
        ans += dis[u];
        visit[u] = 1;
        for (int v = 0; v < N; v++)
            if (!visit[v] && map[u][v])
                if (dis[v] > map[u][v])
                    dis[v] = map[u][v];
    }
}

int main() {
    scanf("%d%d", &N, &M);
    std::fill(dis, dis + N, INF);
    int i, x, y, z;
    for (i = 0; i < M; i++) {
        scanf("%d%d%d", &x, &y, &z);
        map[x - 1][y - 1] = map[y - 1][x - 1] = z;
    }
    prim(0);
    for (i = 0; i < N; i++)
        if (dis[i] == INF)
            break;
    printf("%d", i == N ? ans : -1);
    return 0;
}
