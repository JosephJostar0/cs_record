#include <iostream>
using namespace std;
#define MAXN 201
int n, m, G[MAXN][MAXN], visit[MAXN][MAXN], current = 0;
void dfs(int x, int y) {
    if (x < 0 || x >= n || y < 0 || y >= m || visit[x][y] || !G[x][y])
        return;
    visit[x][y] = 1;
    if (G[x][y] < 0)
        current = -1;
    if (current >= 0)
        current += G[x][y];
    dfs(x - 1, y);
    dfs(x + 1, y);
    dfs(x, y - 1);
    dfs(x, y + 1);
}
int main() {
    ios::sync_with_stdio(false);
    cout.tie(NULL);
    cin.tie(NULL);
    cin >> n >> m;
    int i, j, top = 0;
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            cin >> G[i][j];
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++, current = 0)
            if (!visit[i][j]) {
                dfs(i, j);
                top = max(top, current);
            }
    std::cout << top;
    return 0;
}
