#include <algorithm>
#include <iostream>
#include <vector>
#define MAXN 100
class Edge {
public:
    int u, v, cost;
} edge;
std::vector<Edge> v;
int n, k, father[MAXN];

bool cmp(const Edge a, const Edge b) { return a.cost < b.cost; }

int findFather(int x) {
    int a = x;
    while (father[x] != -1)
        x = father[x];
    while (father[a] != -1) {
        int temp = a;
        a = father[a];
        father[temp] = x;
    }
    return x;
}

int kruskal() {
    int ans = 0, count = 0;
    for (int i = 0; i < v.size(); i++) {
        int faU = findFather(v[i].u), faV = findFather(v[i].v);
        if (faU != faV) {
            father[faU] = faV;
            count++;
            ans += v[i].cost;
            if (count == n - k)
                break;
        }
    }
    return count == n - k ? ans : -1;
}

int main() {
    int i, j, t;
    scanf("%d%d", &n, &k);
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            scanf("%d", &edge.cost);
            if (i != j)
                edge.u = i, edge.v = j, v.push_back(edge);
        }
    std::fill(father, father + n, -1);
    std::sort(v.begin(), v.end(), cmp);
    scanf("%d", &t);
    for (i = 1; i < k; i++) {
        scanf("%d", &j);
        father[j] = t;
    }
    printf("%d", kruskal());
    return 0;
}
