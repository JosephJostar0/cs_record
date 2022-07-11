#include <iostream>
int main() {
    int n, m, i, p, q, chu[101] = {0}, ru[101] = {0};
    scanf("%d%d", &n, &m);
    for (i = 0; i < m; i++) {
        scanf("%d%d", &p, &q);
        chu[p]++, ru[q]++;
    }
    printf("%d %d", ru[0], chu[0]);
    for (i = 1; i < n; i++)
        printf("\n%d %d", ru[i], chu[i]);
    return 0;
}
