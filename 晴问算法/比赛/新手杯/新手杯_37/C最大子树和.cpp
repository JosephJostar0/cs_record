#include <iostream>
#include <vector>
#define MAXN 10000
#define BOTTOM -1000000001
int n;
long long node[MAXN], top = BOTTOM;
std::vector<int> edge[MAXN];
long long dfs(int root, int dad = -1) {
    long long sum = node[root];
    for (auto it : edge[root])
        if (it != dad)
            sum += dfs(it, root);
    if (sum > top)
        top = sum;
    return sum;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%lld", node + i);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    dfs(0);
    printf("%lld", top);
    return 0;
}
