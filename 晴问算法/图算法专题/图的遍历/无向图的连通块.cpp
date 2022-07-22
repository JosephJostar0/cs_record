#include <iostream>
int n, m, dis[100][100], visit[100];
void dfs(int id) {
    visit[id] = 1;
    for (int i = 0; i < n; i++)
        if (!visit[i] && dis[id][i])
            dfs(i);
}

int getNum() {
    int ans = 0, i;
    for (i = 0; i < n; i++)
        if (!visit[i]) {
            ans++;
            dfs(i);
        }
    return ans;
}

int main() {
    scanf("%d%d", &n, &m);
    int i, x, y;
    for (i = 0; i < m; i++) {
        scanf("%d%d", &x, &y);
        dis[x][y] = dis[y][x] = 1;
    }
    printf("%d", getNum());
    return 0;
}
