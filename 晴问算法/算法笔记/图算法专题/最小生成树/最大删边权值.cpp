#include <algorithm>
#include <iostream>
#define MAXN 100
#define MAXE 10000
class Edge {
public:
    int u, v;
    int cost;
} E[MAXN];
int n, m, father[MAXN];
int sum;

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
    std::sort(E, E + m, cmp);
    int ans = 0, count = 0;
    for (int i = 0; i < m; i++) {
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
    return count == n - 1 ? sum - ans : -1;
}

int main() {
    int i;
    scanf("%d%d", &n, &m);
    for (i = 0; i < m; i++) {
        scanf("%d%d%d", &E[i].u, &E[i].v, &E[i].cost);
        sum += E[i].cost;
    }
    printf("%d", kruskal());
    return 0;
}
