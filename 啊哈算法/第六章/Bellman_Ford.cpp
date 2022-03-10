#include <iostream>
#define INF 0xbadbeef
int main() {
    int  start[10], end[10], weight[10], distance[10];
    int  n, m; // n个结点，m条边
    int  i, j;
    bool flag;
    std::cin >> n >> m;
    for (i = 0; i < m; i++)
        std::cin >> start[i] >> end[i] >> weight[i];
    for (i = 1; i <= n; i++)
        distance[i] = INF;
    distance[1] = 0;
    for (i = 0; i < n - 1; i++) {
        flag = true;
        for (j = 0; j < m; j++)
            if (distance[end[j]] > distance[start[j]] + weight[j]) {
                distance[end[j]] = distance[start[j]] + weight[j];
                flag             = false;
            }
        if (flag)
            break;
    }
    for (i = 0; i < m; i++)
        if (distance[end[i]] > distance[start[i]] + weight[i])
            break;
    if (i != m)
        std::cout << "这个图有负权值回路！\n";
    else
        for (i = 1; i <= n; i++)
            printf("%d ", distance[i]);
    return 0;
}
