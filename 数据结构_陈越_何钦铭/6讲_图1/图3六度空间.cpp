#include <iostream>
#include <queue>
#include <vector>
int map[1001][1001], N;
std::vector<int> v;

int bfs(std::queue<int> q, int step = 0) {
    if (step > 5)
        return 0;
    std::queue<int> q1;
    int t, i;
    while (!q.empty()) {
        t = q.front(), q.pop();
        for (i = 1; i <= N; i++)
            if (!v[i] && map[t][i])
                q1.push(i), v[i] = 1;
    }
    return q1.size() + bfs(q1, step + 1);
}

int getNum(int id) {
    std::queue<int> q;
    q.push(id);
    v[id] = 1;
    return 1 + bfs(q);
}

int main() {
    int M, i, p, q;
    scanf("%d%d", &N, &M);
    for (i = 0; i < M; i++) {
        scanf("%d%d", &p, &q);
        map[p][q] = map[q][p] = 1;
    }
    for (i = 1; i <= N; i++) {
        v.clear();
        v.resize(N + 1, 0);
        p = getNum(i);
        printf("%d: %.2f%\n", i, (double)p / N * 100);
    }
    return 0;
}
