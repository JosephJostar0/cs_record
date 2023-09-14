#include <algorithm>
#include <iostream>
int n, m, dis[100][100], visit[100];

bool isCircle(int id) {
    visit[id] = 0;
    for (int i = 0; i < n; i++)
        if (dis[id][i]) {
            if (visit[i] == -1 && isCircle(i))
                return true;
            else if (visit[i] == 0)
                return true;
        }
    visit[id] = 1;
    return false;
}

int main() {
    scanf("%d%d", &n, &m);
    int i, x, y;
    std::fill(visit, visit + n, -1);
    for (i = 0; i < m; i++) {
        scanf("%d%d", &x, &y);
        dis[x][y] = 1;
    }
    for (i = 0; i < n; i++)
        if (visit[i] == -1 && isCircle(i))
            break;
    std::cout << (i != n ? "Yes" : "No");
    return 0;
}
