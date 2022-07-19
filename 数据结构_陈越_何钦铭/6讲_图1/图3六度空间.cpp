#include <iostream>
#include <queue>
#include <vector>
int map[1001][1001], N;
std::vector<int> v;

int getNum(int id) {
    std::queue<int> q;
    q.push(id);
    v[id] = 1;
    int last = id, tail, step = 0, ans = 1, t, i;
    while (!q.empty()) {
        t = q.front(), q.pop();
        for (i = 1; i <= N; i++)
            if (!v[i] && map[t][i])
                v[i] = 1, tail = i, q.push(i), ans++;
        if (t == last)
            last = tail, step++;
        if (step > 5)
            return ans;
    }
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
