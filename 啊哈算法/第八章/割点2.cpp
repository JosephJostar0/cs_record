#include <iostream>
int first[10], next[20];
int startPoint[20], endPoint[20];
int mark[10], back[10], cutPoint[10], id = 0;
int m, n, root;
void dfs(int current, int father) {
    int i, son = 0;
    id++;
    mark[current] = id;
    back[current] = id;
    for (i = first[current]; i > 0; i = next[i]) {
        if (mark[endPoint[i]] == 0) {
            son++;
            dfs(i, current);
            back[current] = std::min(back[current], back[endPoint[i]]);
            if (back[endPoint[i]] >= back[current])
                cutPoint[current] = 1;
            if (current == root && son >= 2)
                cutPoint[current] = 1;
        } else if (endPoint[i] != father)
            back[current] = std::min(back[current], back[endPoint[i]]);
    }
}

int main() {
    int i, j;
    std::cin >> m >> n;
    for (i = 1; i <= n; i++)
        std::cin >> startPoint[i] >> endPoint[i];
    for (i = n + 1; i <= 2 * n; i++) {
        startPoint[i] = endPoint[i - n];
        endPoint[i] = startPoint[i - n];
    }
    for (i = 1; i <= 2 * n; i++) {
        next[i] = first[startPoint[i]];
        first[startPoint[i]] = i;
    }
    root = 1;
    dfs(1, root);
    for (i = 1; i <= m; i++)
        if (cutPoint[i] == 1)
            std::cout << i << ' ';
    return 0;
}
