#include <iostream>
#include <queue>
int n, m, k, dis[100][100], visit[100], weight[100], ans;
void bfs(int s) {
    std::queue<int> q;
    q.push(s);
    visit[s] = 1;
    int t, last, level = 0, margin = s;
    while (q.size()) {
        t = q.front(), q.pop();
        weight[t] = level;
        ans++;
        for (int i = 0; i < n; i++)
            if (dis[t][i] && !visit[i])
                q.push(i), last = i, visit[i] = 1;
        if (t == margin) {
            margin = last;
            level++;
        }
        if (level > k)
            return;
    }
}

int main() {
    int i, x, y, s;
    scanf("%d%d%d%d", &n, &m, &s, &k);
    std::fill(weight, weight + n, 0xbadbeef);
    for (i = 0; i < m; i++) {
        scanf("%d%d", &x, &y);
        dis[x][y] = 1;
    }
    bfs(s);
    printf("%d", ans);
    return 0;
}
