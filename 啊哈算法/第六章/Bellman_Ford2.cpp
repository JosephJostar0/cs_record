#include <iostream>
#include <queue>
#define INF 0xbadbeef
int main() {
    int m, n; // m个顶点,n条边
    int start[10], end[10], weight[10], distance[10];
    int first[11], next[11], book[10], count = 0;
    int i, j;
    std::cin >> m >> n;
    for (i = 0; i <= m; i++)
        first[i] = -1, distance[i] = INF, book[i] = 0;
    distance[1] = 0;
    for (i = 0; i < n; i++) {
        std::cin >> start[i] >> end[i] >> weight[i];
        next[i]         = first[start[i]];
        first[start[i]] = i;
    }
    std::queue<int> que;
    que.push(1);
    book[1] = 1;
    while (que.size()) {
        i = que.front();
        que.pop();
        book[i] = 0;
        for (j = first[i]; j >= 0; j = next[j]) {
            count++;
            if (distance[end[j]] > distance[start[j]] + weight[j]) {
                distance[end[j]] = distance[start[j]] + weight[j];
                if (book[end[j]] == 0) {
                    que.push(end[j]);
                    book[end[j]] = 1;
                }
            }
        }
        if (count > (m - 1) * n)
            break;
    }
    if (count > (m - 1) * n)
        std::cout << "有负权值回路\n";
    else
        for (i = 1; i <= m; i++)
            printf("%d ", distance[i]);
    return 0;
}
