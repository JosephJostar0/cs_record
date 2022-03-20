#include <iostream>
int startPoint[20], endPoint[20];
int first[10], next[20];
int book[10], match[5];
int m, n, sum = 0;

bool dfs(int node) {
    int i;
    for (i = first[node]; i != 0; i = next[i]) {
        if (book[endPoint[i]] == 0) {
            book[endPoint[i]] = 1;
            if (match[endPoint[i]] == 0 || dfs(match[endPoint[i]])) {
                match[endPoint[i]] = node;
                return true;
            }
        }
    }
    return false;
}

int main() {
    int i, j;
    std::cin >> m >> n;
    for (i = 1; i <= n; i++) {
        std::cin >> startPoint[i] >> endPoint[i];
        next[i] = first[startPoint[i]];
        first[startPoint[i]] = i;
    }
    for (i = 1; i <= m; i++) {
        for (j = 1; j <= m; j++)
            book[j] = 0;
        if (dfs(i))
            sum++;
    }
    std::cout << sum;
    return 0;
}
