#include <iostream>
int father[101], check[101];

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
    for (i = 1; i <= n; i++)
        father[i] = -1;
    for (i = 0; i < m; i++) {
        scanf("%d%d", &p, &q);
        Union(p, q);
    }
    for (i = 1; i <= n; i++) {
        int f = findFather(i);
        if (!check[f])
            check[f] = 1, ans++;
    }
    printf("%d", ans);
    return 0;
}
