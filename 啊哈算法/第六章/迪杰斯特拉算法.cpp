#include <iostream>
int main() {
    int e[10][10], m, n, distance[10], book[10];
    std::cin >> m >> n; // m:顶点数,n:边数
    int i, j, k, min, t;
    for (i = 1; i <= m; i++)
        for (j = 1; j <= m; j++) {
            if (i == j)
                e[i][j] = 0;
            else
                e[i][j] = 0x3f3f3f;
        }
    for (i = 0; i < n; i++) {
        std::cin >> j >> k;
        std::cin >> e[j][k]; //有向图
    }
    for (i = 1; i <= m; i++)
        distance[i] = e[1][i], book[i] = 0;
    book[1] = 1;
    for (i = 0; i < m - 1; i++) {
        min = 0x3f3f3f, k = 0;
        for (j = 1; j <= m; j++)
            if (book[j] == 0 && distance[j] < min)
                min = distance[j], k = j;
        if (k == 0)
            break;
        book[k] = 1;
        for (t = 1; t <= m; t++)
            if (e[k][t] < 0x3f3f3f)
                if (distance[t] > distance[k] + e[k][t])
                    distance[t] = distance[k] + e[k][t];
    }
    for (i = 1; i <= m; i++)
        printf("%d ", distance[i]);
    return 0;
}
