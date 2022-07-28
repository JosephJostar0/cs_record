#include <iostream>
#include <queue>
#include <vector>
#define MAXN 100
std::vector<int> link[MAXN], out;
int inDegree[MAXN], n, m, visit[MAXN];

bool topoLogical() {
    std::priority_queue<int, std::vector<int>, std::greater<int>> q;
    int count = 0;
    for (int i = 0; i < n; i++)
        if (!inDegree[i])
            q.push(i);
    while (q.size()) {
        int u = q.top();
        q.pop();
        count++;
        out.push_back(u);
        for (int i = 0; i < link[u].size(); i++) {
            int v = link[u][i];
            if (--inDegree[v] == 0)
                q.push(v);
        }
    }
    return count == n;
}

int main() {
    int i, u, v;
    scanf("%d%d", &n, &m);
    for (i = 0; i < m; i++) {
        scanf("%d%d", &u, &v);
        inDegree[v]++;
        link[u].push_back(v);
    }
    if (!topoLogical()) {
        printf("No\n%d", n - out.size());
        return 0;
    }
    printf("Yes\n%d", out[0]);
    for (i = 1; i < out.size(); i++)
        printf(" %d", out[i]);
    return 0;
}