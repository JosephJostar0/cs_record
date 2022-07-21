#include <iostream>
#define INF 0xbeef
int N, M, S, D, visit[500];
class Node {
public:
    int len, price;
    Node() { len = INF, price = INF; }
    void set(int a, int b) { len = a, price = b; }
} node[500][500], result[500];

void dijkstra(int s) {
    result[s].set(0, 0);
    for (int i = 0; i < N; i++) {
        int minL = INF, minP = INF, u = -1;
        for (int j = 0; j < N; j++)
            if (!visit[j]) {
                if (result[j].len < minL)
                    u = j, minL = result[j].len, minP = result[j].price;
                else if (result[j].len == minL && result[j].price < minP)
                    u = j, minL = result[j].len, minP = result[j].price;
            }
        if (u == -1)
            break;
        visit[u] = 1;
        for (int v = 0; v < N; v++)
            if (!visit[v]) {
                if (result[v].len > result[u].len + node[u][v].len)
                    result[v].set(result[u].len + node[u][v].len, result[u].price + node[u][v].price);
                else if (result[v].len == result[u].len + node[u][v].len)
                    if (result[v].price > result[u].price + node[u][v].price)
                        result[v].price = result[u].price + node[u][v].price;
            }
    }
}

int main() {
    int i, x, y;
    scanf("%d %d %d %d", &N, &M, &S, &D);
    for (i = 0; i < M; i++) {
        scanf("%d %d", &x, &y);
        scanf("%d %d", &node[x][y].len, &node[x][y].price);
        node[y][x].len = node[x][y].len;
        node[y][x].price = node[x][y].price;
    }
    dijkstra(S);
    printf("%d %d", result[D].len, result[D].price);
    return 0;
}
