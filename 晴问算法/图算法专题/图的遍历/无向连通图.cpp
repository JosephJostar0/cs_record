#include <iostream>
int n, m, dis[100][100], visit[100];
void dfs(int id) {
    visit[id] = 1;
    for (int i = 0; i < n; i++)
        if (!visit[i] && dis[id][i])
            dfs(i);
}

bool isLink() {
    int i;
    for (i = 0; i < n; i++)
        if (!visit[i]) {
            dfs(i);
            break;
        }
    for (i = 0; i < n; i++)
        if (!visit[i])
            return false;
    return true;
}

int main() {
    scanf("%d%d", &n, &m);
    int i, x, y;
    for (i = 0; i < m; i++) {
        scanf("%d%d", &x, &y);
        dis[x][y] = dis[y][x] = 1;
    }
    std::cout << (isLink() ? "Yes" : "No");
    return 0;
}
