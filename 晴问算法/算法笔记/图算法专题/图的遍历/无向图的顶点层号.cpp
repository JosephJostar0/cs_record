#include <iostream>
#include <queue>
int n, m, dis[100][100], visit[100], weight[100];
void bfs(int s) {
    std::queue<int> q;
    q.push(s);
    visit[s] = 1;
    int t, last, level = 0, margin = s;
    while (q.size()) {
        t = q.front(), q.pop();
        weight[t] = level;
        for (int i = 0; i < n; i++)
            if (dis[t][i] && !visit[i])
                q.push(i), last = i, visit[i] = 1;
        if (t == margin) {
            margin = last;
            level++;
        }
    }
}

int main() {
    int i, x, y, s;
    scanf("%d%d%d", &n, &m, &s);
    for (i = 0; i < m; i++) {
        scanf("%d%d", &x, &y);
        dis[x][y] = dis[y][x] = 1;
    }
    bfs(s);
    printf("%d", weight[0]);
    for (i = 1; i < n; i++)
        printf(" %d", weight[i]);
    return 0;
}
