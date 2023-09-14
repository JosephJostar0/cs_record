#include <algorithm>
#include <iostream>
int father[101], check[101], rank[101], high[101];

int findFather(int x) {
    int t = x;
    while (father[t] != -1)
        t = father[t];
    while (father[x] != -1) {
        int a = x;
        x = father[x];
        father[a] = t;
    }
    return t;
}

void Union(int a, int b) {
    int x = findFather(a);
    int y = findFather(b);
    if (x != y)
        father[x] = b;
}

int main() {
    int i, m, n, p, q, ans = 0;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) {
        father[i] = -1;
        scanf("%d", rank + i);
    }
    for (i = 0; i < m; i++) {
        scanf("%d%d", &p, &q);
        Union(p, q);
    }
    for (i = 1; i <= n; i++) {
        int f = findFather(i);
        if (!check[f])
            ans++, check[f] = 1;
        high[f] = std::max(high[f], rank[i]);
    }
    std::sort(high, high + 1 + n, std::greater<int>());
    printf("%d\n%d", ans, high[0]);
    for (i = 1; i < ans; i++)
        printf(" %d", high[i]);
    return 0;
}
