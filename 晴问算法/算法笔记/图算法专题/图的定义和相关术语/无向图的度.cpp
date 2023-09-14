#include <iostream>
int main() {
    int n, m, i, p, q, du[101] = {0};
    scanf("%d%d", &n, &m);
    for (i = 0; i < m; i++) {
        scanf("%d%d", &p, &q);
        du[p]++, du[q]++;
    }
    printf("%d", du[0]);
    for (i = 1; i < n; i++)
        printf(" %d", du[i]);
    return 0;
}
