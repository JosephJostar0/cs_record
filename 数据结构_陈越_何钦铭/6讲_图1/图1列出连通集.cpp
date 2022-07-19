#include <iostream>
#include <queue>
int map[11][11], visit[11], N;
bool flag;

void dfs(int index) {
    printf(" %d", index);
    visit[index] = 1;
    for (int i = 0; i < N; i++)
        if (map[index][i] && !visit[i])
            dfs(i);
}

void bfs(int index) {
    std::queue<int> q;
    q.push(index);
    visit[index] = 0;
    int t, i;
    while (!q.empty()) {
        t = q.front();
        q.pop();
        printf(" %d", t);
        for (i = 0; i < N; i++)
            if (map[t][i] && visit[i])
                q.push(i), visit[i] = 0;
    }
}

int main() {
    int E, i, p, q;
    scanf("%d%d", &N, &E);
    for (i = 0; i < E; i++) {
        scanf("%d%d", &p, &q);
        map[p][q] = map[q][p] = 1;
    }
    for (i = 0; i < N; i++)
        if (!visit[i]) {
            printf("{");
            dfs(i);
            printf(" }\n");
        }
    for (i = 0; i < N; i++)
        if (visit[i]) {
            printf("{");
            bfs(i);
            printf(" }\n");
        }
    return 0;
}
