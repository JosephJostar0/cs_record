#include <iostream>
#include <queue>
#include <vector>
#define MAXN 100
class Link {
public:
    int len, point;
    Link() { len = -1, point = -1; }
} l;

std::vector<Link> G[MAXN];
int n, m, inDegree[MAXN], take[MAXN];

bool topoLogicalSort() {
    int num = 0, i;
    std::priority_queue<int, std::vector<int>, std::greater<int>> q;
    for (i = 0; i < n; i++)
        if (inDegree[i] == 0) {
            q.push(i);
            take[i] = 0;
        }
    while (q.size()) {
        int u = q.top();
        q.pop();
        for (i = 0; i < G[u].size(); i++) {
            int v = G[u][i].point;
            if (take[v] < take[u] + G[u][i].len)
                take[v] = take[u] + G[u][i].len;
            if (--inDegree[v] == 0)
                q.push(v);
        }
        num++;
    }
    return num == n;
}

int main() {
    int i, x;
    scanf("%d%d", &n, &m);
    std::fill(take, take + n, -1);
    for (i = 0; i < m; i++) {
        scanf("%d%d%d", &x, &l.point, &l.len);
        G[x].push_back(l);
        inDegree[l.point]++;
    }
    if (!topoLogicalSort()) {
        printf("No");
        return 0;
    }
    for (i = 0, x = -1; i < n; i++)
        if (take[i] > x)
            x = take[i];
    printf("Yes\n%d", x);
    return 0;
}
