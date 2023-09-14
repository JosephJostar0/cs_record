#include <iostream>
#include <queue>
#include <vector>
#define MAXN 100
std::vector<int> G[MAXN];
int n, m, inDegree[MAXN], flag;

bool topoLogicalSort() {
    int num = 0, i;
    std::priority_queue<int, std::vector<int>, std::greater<int>> q;
    for (i = 0; i < n; i++)
        if (inDegree[i] == 0)
            q.push(i);
    while (q.size()) {
        int u = q.top();
        q.pop();
        if (flag)
            printf(" ");
        printf("%d", u);
        flag = 1;
        for (i = 0; i < G[u].size(); i++) {
            int v = G[u][i];
            if (--inDegree[v] == 0)
                q.push(v);
        }
        num++;
    }
    return num == n;
}

int main() {
    int i, x, y;
    scanf("%d%d", &n, &m);
    for (i = 0; i < m; i++) {
        scanf("%d%d", &x, &y);
        G[x].push_back(y);
        inDegree[y]++;
    }
    topoLogicalSort();
    return 0;
}
