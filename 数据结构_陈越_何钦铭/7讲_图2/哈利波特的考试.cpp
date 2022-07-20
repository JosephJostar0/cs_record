#include <algorithm>
#include <iostream>
#define INF 0xbadbeef
int N, map[100][100];

void floyd() {
    int i, j, k;
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            for (k = 0; k < N; k++)
                if (map[j][i] != INF && map[i][k] != INF)
                    if (map[j][i] + map[i][k] < map[j][k])
                        map[j][k] = map[j][i] + map[i][k];
}

int getDis(int id) {
    int result = map[id][0];
    for (int i = 0; i < N; i++)
        if (result < map[id][i])
            result = map[id][i];
    return result;
}

int main() {
    int M, i, x, y, ans = 0, dis = INF;
    scanf("%d %d", &N, &M);
    std::fill(map[0], map[0] + 100 * 100, INF);
    for (i = 0; i < N; i++)
        map[i][i] = 0;
    for (i = 0; i < M; i++) {
        scanf("%d %d %d", &x, &y, &ans);
        map[x - 1][y - 1] = ans;
        map[y - 1][x - 1] = ans;
    }
    floyd();
    for (i = 0, ans = 0; i < N; i++) {
        x = getDis(i);
        if (x < dis)
            dis = x, ans = i + 1;
    }

    if (ans)
        printf("%d %d", ans, dis);
    else
        printf("0");
    return 0;
}
