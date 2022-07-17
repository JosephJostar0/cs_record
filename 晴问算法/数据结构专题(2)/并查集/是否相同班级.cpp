#include <algorithm>
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
    int i, m, n, p, q, k;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++)
        father[i] = -1;
    for (i = 0; i < m; i++) {
        scanf("%d%d", &p, &q);
        Union(p, q);
    }
    scanf("%d", &k);
    for (i = 0; i < k; i++) {
        scanf("%d%d", &p, &q);
        if (findFather(p) == findFather(q))
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}
