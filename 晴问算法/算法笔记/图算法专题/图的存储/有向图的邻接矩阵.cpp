#include <iostream>
int map[100][100];
int main() {
    int n, m, i, x, y;
    scanf("%d%d", &n, &m);
    for (i = 0; i < m; i++) {
        scanf("%d%d", &x, &y);
        map[x][y] = 1;
    }
    for (x = 0; x < n; x++) {
        printf("%d", map[x][0]);
        for (y = 1; y < n; y++)
            printf(" %d", map[x][y]);
        printf("\n");
    }
    return 0;
}
