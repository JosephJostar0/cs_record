#include <iostream>
int n, m, dis[100][100], visit[100], weight[100];

int dfs(int id) {
    visit[id] = 1;
    int value = weight[id];
    for (int i = 0; i < n; i++)
        if (!visit[i] && dis[id][i])
            value += dfs(i);
    return value;
}

int main() {
    scanf("%d%d", &n, &m);
    int i, x, y, ans = 0;
    for (i = 0; i < n; i++)
        scanf("%d", weight + i);
    for (i = 0; i < m; i++) {
        scanf("%d%d", &x, &y);
        dis[x][y] = dis[y][x] = 1;
    }
    for (i = 0; i < n; i++)
        if (!visit[i])
            ans = std::max(ans, dfs(i));
    printf("%d", ans);
    return 0;
}
