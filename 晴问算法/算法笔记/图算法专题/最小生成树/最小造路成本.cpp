#include <algorithm>
#include <iostream>
#include <vector>
#define MAXN 100
#define MAXE 10000
class Edge {
public:
    int u, v;
    int cost;
} edge;
std::vector<Edge> E;
int n, m, father[MAXN];

bool cmp(const Edge a, const Edge b) { return a.cost < b.cost; }

int findFather(int x) {
    int a = x;
    while (father[x] != -1)
        x = father[x];
    while (father[a] != -1) {
        int z = a;
        a = father[a];
        father[z] = x;
    }
    return x;
}

int kruskal() {
    std::fill(father, father + n, -1);
    std::sort(E.begin(), E.end(), cmp);
    int ans = 0, count = 0;
    for (int i = 0; i < E.size(); i++) {
        int faU = findFather(E[i].u);
        int faV = findFather(E[i].v);
        if (faU != faV) {
            father[faU] = faV;
            ans += E[i].cost;
            count++;
            if (count == n - 1)
                break;
        }
    }
    return count == n - 1 ? ans : -1;
}

int main() {
    int i, j;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            scanf("%d", &edge.cost);
            if (i != j)
                edge.u = i, edge.v = j, E.push_back(edge);
        }
    printf("%d", kruskal());
    return 0;
}
