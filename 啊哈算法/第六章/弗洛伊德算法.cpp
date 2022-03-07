#include <iostream>
int main() {
    int e[10][10], n, m;
    int inf = 0x3f3f3f;
    int i, j, k;
    std::cin >> n >> m; // n:顶点个数,m:边的条数
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++) {
            if (i == j)
                e[i][j] = 0;
            else
                e[i][j] = inf;
        }
    for (i = 0; i < m; i++) {
        std::cin >> j >> k;
        std::cin >> e[j][k]; //有向图
    }
    for (i = 1; i <= n; i++)
        for (k = 1; k <= n; k++)
            for (j = 1; j <= n; j++)
                if (e[k][j] > e[k][i] + e[i][j])
                    e[k][j] = e[k][i] + e[i][j];
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++)
            std::cout << e[i][j] << ' ';
        std::cout << std::endl;
    }
    return 0;
}
