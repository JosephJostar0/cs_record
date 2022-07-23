#include <iostream>
#define INF 0xbadbeef
int n, m, dis[100][100];
void prime() {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                if (dis[j][i] != INF && dis[i][k] != INF)
                    if (dis[j][k] > dis[j][i] + dis[i][k])
                        dis[j][k] = dis[j][i] + dis[i][k];
}

int main() {
    std::fill(dis[0], dis[0] + 100 * 100, INF);
    scanf("%d%d", &n, &m);
    int i, x, y, z;
    for (i = 0; i < n; i++)
        dis[i][i] = 0;
    for (i = 0; i < m; i++) {
        scanf("%d%d%d", &x, &y, &z);
        dis[x][y] = dis[y][x] = z;
    }
    prime();
    for (x = 0; x < n; x++) {
        printf("%d", dis[x][0] == INF ? -1 : dis[x][0]);
        for (y = 1; y < n; y++)
            printf(" %d", dis[x][y] == INF ? -1 : dis[x][y]);
        printf("\n");
    }
    return 0;
}
