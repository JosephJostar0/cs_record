#include <iostream>
int startPoint[20], endPoint[20];
int first[10], next[20];
int mark[10], back[10];
int m, n, root, id = 0, sum = 0;
void dfs(int current, int father) {
    int i, son = 0;
    mark[current] = ++id;
    back[current] = id;
    for (i = first[current]; i != 0; i = next[i]) {
        if (mark[endPoint[i]] == 0) {
            son++;
            dfs(endPoint[i], current);
            back[current] = std::min(back[current], back[endPoint[i]]);
            if (back[endPoint[i]] > mark[current])
                printf("%d-%d\n", current, endPoint[i]);
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
    return 0;
}
