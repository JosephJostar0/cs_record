#include <iostream>
#include <vector>
std::vector<int> link[100];
int main() {
    int n, m, i, x, y;
    scanf("%d%d", &n, &m);
    for (i = 0; i < m; i++) {
        scanf("%d%d", &x, &y);
        link[x].push_back(y);
    }
    for (i = 0; i < n; i++) {
        printf("%d(%d)", i, link[i].size());
        for (x = 0; x < link[i].size(); x++)
            printf(" %d", link[i][x]);
        printf("\n");
    }
    return 0;
}
