#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#define INF 0xbadbeef
int N, D;
int distance[100][100], pre[100], result[100], visit[100], way[100];
std::vector<int> first, bank;

class Node {
public:
    int x, y;
} node[100];

int getDis(int a) { return node[a].x * node[a].x + node[a].y * node[a].y; }

int getDis(int a, int b) {
    int x = node[a].x - node[b].x;
    int y = node[a].y - node[b].y;
    return x * x + y * y;
}

bool check(int id) {
    if (abs(node[id].x) >= 50 || abs(node[id].y) >= 50)
        return false;
    if (getDis(id) <= 7.5 * 7.5)
        return false;
    return true;
}

bool cmp(int a, int b) { return getDis(a) < getDis(b); }

void dfs(int id) {
    if (result[id] != -1)
        dfs(result[id]);
    printf("%d %d\n", node[id].x, node[id].y);
}

int Dijkstra(int index) {
    std::fill(pre, pre + N, -1);
    std::fill(way, way + N, INF);
    std::fill(visit, visit + N, 0);
    way[index] = 1;
    int point = INF, m = INF;
    for (int i = 0; i < N; i++) {
        int MIN = INF, u = -1;
        for (int j = 0; j < N; j++)
            if (!visit[j] && way[j] < INF)
                u = j, MIN = way[j];
        if (u == -1)
            break;
        visit[u] = 1;
        for (int v = 0; v < N; v++)
            if (!visit[v] && distance[u][v])
                if (way[v] > way[u] + 1)
                    way[v] = way[u] + 1, pre[v] = u;
    }
    for (int i = 0; i < bank.size(); i++)
        if (way[bank[i]] < m)
            m = way[bank[i]], point = bank[i];
    return point;
}

int main() {
    scanf("%d %d", &N, &D);
    double margin = (double)D + 7.5;
    margin *= margin;
    int i, j, ans = INF, need;
    for (i = 0; i < N; i++) {
        scanf("%d %d", &node[i].x, &node[i].y);
        if (!check(i)) {
            i--, N--;
            continue;
        }
        if ((double)getDis(i) <= margin)
            first.push_back(i);
        if (abs(node[i].x) >= 50 - D || abs(node[i].y) >= 50 - D)
            bank.push_back(i);
    }
    if (margin >= 50 * 50) {
        printf("1");
        return 0;
    }
    if (bank.empty() || first.empty()) {
        printf("0");
        return 0;
    }
    for (i = 0; i < N; i++)
        for (j = i; j < N; j++)
            distance[i][j] = distance[j][i] = (getDis(i, j) <= D * D) ? 1 : 0;
    std::sort(first.begin(), first.end(), cmp);
    for (i = 0; i < first.size(); i++) {
        int temp = Dijkstra(first[i]);
        if (temp != INF && way[temp] < ans) {
            ans = way[temp];
            need = temp;
            for (j = 0; j < N; j++)
                result[j] = pre[j];
        }
    }
    if (ans == INF) {
        printf("0");
        return 0;
    }
    printf("%d\n", ans + 1);
    dfs(need);
    return 0;
}
