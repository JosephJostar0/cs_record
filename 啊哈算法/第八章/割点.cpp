#include <iostream>
int m, n, e[9][9], root;
int num[9], low[9], flag[9], id;

void dfs(int cur, int father) {
    int child = 0, i;
    id++;
    num[cur] = id;
    low[cur] = id;
    for (i = 1; i <= m; i++) {
        if (e[cur][i] == 1) {
            if (num[i] == 0) {
                child++;
                dfs(i, cur);
                low[cur] = std::min(low[cur], low[i]);
                if (cur != root && low[i] >= num[cur])
                    flag[cur] = 1;
                if (cur == root && child >= 2)
                    flag[cur] = 1;
            } else if (i != father)
                low[cur] = std::min(low[cur], num[i]);
        }
    }
}

int main() {
    int i, j, x, y;
    std::cin >> m >> n;
    for (i = 0; i <= m; i++)
        for (j = 0; j <= m; j++)
            e[i][j] = 0;
    for (i = 1; i <= n; i++) {
        std::cin >> x >> y;
        e[x][y] = 1;
        e[y][x] = 1;
    }
    root = 1;
    dfs(1, root);
    for (i = 1; i <= m; i++)
        if (flag[i] == 1)
            std::cout << i;
    return 0;
}
