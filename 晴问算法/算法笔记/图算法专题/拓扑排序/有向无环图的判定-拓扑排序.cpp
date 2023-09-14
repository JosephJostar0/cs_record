#include <iostream>
#include <queue>
#include <vector>
#define MAXN 100
std::vector<int> link[MAXN];
int inDegree[MAXN], n, m, visit[MAXN];

bool topoLogical() {
    std::queue<int> q;
    int count = 0;
    for (int i = 0; i < n; i++)
        if (!inDegree[i])
            q.push(i);
    while (q.size()) {
        int u = q.front();
        q.pop();
        count++;
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
    printf("%s", topoLogical() ? "Yes" : "No");
    return 0;
}
