#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#define MAXN 100
class Link {
public:
    int len, point;
    Link() { len = -1, point = -1; }
} l;

std::vector<Link> G[MAXN];
std::stack<int> s;
int n, m, inDegree[MAXN], take[MAXN], last[MAXN];

bool cmp(const Link a, const Link b) { return a.point < b.point; }

bool topoLogicalSort() {
    int num = 0, i;
    std::fill(take, take + n, -1);
    std::priority_queue<int, std::vector<int>, std::greater<int>> q;
    for (i = 0; i < n; i++)
        if (inDegree[i] == 0) {
            q.push(i);
            take[i] = 0;
        }
    while (q.size()) {
        int u = q.top();
        q.pop();
        s.push(u);
        num++;
        for (i = 0; i < G[u].size(); i++) {
            int v = G[u][i].point;
            if (take[v] < take[u] + G[u][i].len)
                take[v] = take[u] + G[u][i].len;
            if (--inDegree[v] == 0)
                q.push(v);
        }
    }
    return num == n;
}

void outPaths() {
    if (!topoLogicalSort()) {
        printf("No");
        return;
    }
    printf("Yes");
    int big = -1, i;
    for (i = 0; i < n; i++)
        if (big < take[i])
            big = take[i];
    std::fill(last, last + n, big);
    while (s.size()) {
        int u = s.top();
        s.pop();
        for (int i = 0; i < G[u].size(); i++) {
            int v = G[u][i].point, w = G[u][i].len;
            if (last[u] > last[v] - w)
                last[u] = last[v] - w;
        }
    }
    for (int i = 0; i < n; i++) {
        std::sort(G[i].begin(), G[i].end(), cmp);
        for (int j = 0; j < G[i].size(); j++) {
            int v = G[i][j].point, w = G[i][j].len;
            int start = take[i];
            int margin = last[v] - w;
            if (start == margin)
                printf("\n%d %d", i, v);
        }
    }
}

int main() {
    int i, x;
    scanf("%d%d", &n, &m);
    for (i = 0; i < m; i++) {
        scanf("%d%d%d", &x, &l.point, &l.len);
        G[x].push_back(l);
        inDegree[l.point]++;
    }
    outPaths();
    return 0;
}
