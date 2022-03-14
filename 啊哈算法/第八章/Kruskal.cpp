#include <algorithm>
#include <iostream>
class Edge {
public:
    int begin;
    int end;
    int weight;
} edge[10];
int m, n; // m个顶点n条边
int f[7] = {0};

bool cmp(Edge a, Edge b) { return a.weight < b.weight; }

int getFather(int t) {
    if (f[t] == t)
        return t;
    f[t] = getFather(f[t]);
    return f[t];
}

void merge(int a, int b) {
    int left  = getFather(a);
    int right = getFather(b);
    if (left != right)
        f[right] = left;
}

int main() {
    int  i, j, k;
    int  head, cost = 0, count = 0;
    bool flag = true;
    std::cin >> m >> n;
    for (i = 0; i < n; i++)
        std::cin >> edge[i].begin >> edge[i].end >> edge[i].weight;
    for (i = 0; i <= m; i++) //初始化并查集
        f[i] = i;
    std::sort(edge, edge + n, cmp);
    for (head = 0; head <= n; head++) {
        if (getFather(edge[head].begin) == getFather(edge[head].end))
            continue;
        merge(edge[head].begin, edge[head].end);
        cost += edge[head].weight;
        count++;
        if (count == n - 1)
            break;
    }
    std::cout << cost << std::endl;
    return 0;
}
