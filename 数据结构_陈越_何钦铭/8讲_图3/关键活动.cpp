#include <iostream>
#include <queue>
#include <vector>
#define MAXN 100
class Link {
public:
    int len, point;
    Link() { len = -1, point = -1; }
} l;

std::vector<Link> G[MAXN], out;
std::vector<int> order;
int n, m, inDegree[MAXN], take[MAXN], late[MAXN];

bool topoLogicalSort() {
    int i;
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
        order.push_back(u);
    }
    return order.size() == n;
}

int CriticalPath() {
    if (!topoLogicalSort())
        return 0;
    int i, big = -1;
    for (i = 0; i < n; i++)
        if (big < take[i])
            big = take[i];
    std::fill(late, late + n, big);
    while (order.size()) {
        int u = order.back();
        order.pop_back();
        for (i = 0; i < G[u].size(); i++) {
            int v = G[u][i].point;
            if (late[u] > late[v] - G[u][i].len)
                late[u] = late[v] - G[u][i].len;
        }
    }
    for (i = 0; i < n; i++)
        for (int j = G[i].size() - 1; j >= 0; j--) {
            int start = late[G[i][j].point] - G[i][j].len;
            if (take[i] == start) {
                l.len = i, l.point = G[i][j].point;
                out.push_back(l);
            }
        }
    return big;
}

int main() {
    int i, j, paths;
    scanf("%d%d", &n, &m);
    std::fill(take, take + n, -1);
    for (i = 0; i < m; i++) {
        scanf("%d%d%d", &j, &l.point, &l.len);
        j--, l.point--;
        G[j].push_back(l);
        inDegree[l.point]++;
    }
    paths = CriticalPath();
    printf("%d", paths);
    for (i = 0; i < out.size(); i++)
        printf("\n%d->%d", out[i].len + 1, out[i].point + 1);
    return 0;
}
