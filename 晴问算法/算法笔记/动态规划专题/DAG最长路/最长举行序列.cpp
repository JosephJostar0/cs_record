#include <iostream>
#define MAXN 100
#define INF 0xbadbeef
class Square {
public:
    int x, y;
} s;
int n, tar, G[MAXN][MAXN], dp[MAXN];
Square squ[MAXN];
bool cmp(Square a, Square b) { return (a.x < b.x && a.y < b.y) || (a.y < b.x && a.x < b.y); }

int dag(int x) {
    if (dp[x])
        return dp[x];
    for (int i = 0; i < n; i++)
        if (G[x][i])
            dp[x] = std::max(dp[x], dag(i) + G[x][i]);
    return dp[x];
}

int main() {
    scanf("%d", &n);
    int i, j;
    for (i = 0; i < n; i++) {
        scanf("%d%d", &squ[i].x, &squ[i].y);
        for (int j = 0; j < i; j++) {
            if (cmp(squ[i], squ[j]))
                G[j][i] = 1;
            else if (cmp(squ[j], squ[i]))
                G[i][j] = 1;
        }
    }
    for (i = 0, j = 0; i < n; i++)
        j = std::max(dag(i), j);
    printf("%d", j + 1);
    return 0;
}
