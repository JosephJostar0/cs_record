#include <iostream>
#define INF 0xbadbeef
int main() {
    int m, n; // m个顶点n条边
    int e[8][8], dis[8], book[8] = {0};
    int cost = 0, node = 0; //代价，顶点数目
    int i, j, k, min;
    std::cin >> m >> n;
    for (i = 1; i <= m; i++)
        for (j = 1; j <= m; j++) {
            if (i == j)
                e[i][j] = 0;
            else
                e[i][j] = INF;
        }
    for (i = 0; i < n; i++) {
        std::cin >> j >> k;
        std::cin >> e[j][k];
        e[k][j] = e[j][k];
    }
    for (i = 1; i <= m; i++)
        dis[i] = e[1][i];
    book[1] = 1;
    node++;
    while (node < m) {
        min = INF;
        for (i = 1; i <= m; i++)
            if (book[i] == 0 && dis[i] < min)
                min = dis[i], j = i;
        book[j] = 1;
        node++;
        cost += dis[j];
        for (i = 1; i <= m; i++)
            if (book[i] == 0 && dis[i] > e[j][i])
                dis[i] = e[j][i];
    }
    std::cout << cost << std::endl;
    return 0;
}
