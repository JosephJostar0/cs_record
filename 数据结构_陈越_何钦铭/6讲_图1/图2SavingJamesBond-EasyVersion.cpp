#include <iostream>
int N, visit[101];
double D;
class Posi {
public:
    int x, y;
} map[101];

int getDis(int x1, int y1, int x2 = 0, int y2 = 0) {
    int x = x2 - x1, y = y2 - y1;
    return x * x + y * y;
}

bool dfs(int id) {
    visit[id] = 1;
    int x = map[id].x, y = map[id].y, i;
    if (getDis(x, y, x, 50) <= D || getDis(x, y, 50, y) <= D)
        return true;
    for (i = 0; i < N; i++)
        if (!visit[i] && getDis(x, y, map[i].x, map[i].y) <= D)
            if (dfs(i))
                return true;
    return false;
}

int main() {
    scanf("%d%lf", &N, &D);
    int i;
    double margin = (D + 7.5) * (D + 7.5);
    D *= D;
    for (i = 0; i < N; i++)
        scanf("%d%d", &map[i].x, &map[i].y);
    for (i = 0; i < N; i++)
        if (!visit[i] && getDis(map[i].x, map[i].y) <= margin)
            if (dfs(i)) {
                printf("Yes");
                return 0;
            }
    printf("No");
    return 0;
}
