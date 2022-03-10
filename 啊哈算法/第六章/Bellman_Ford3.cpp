#include <iostream>
#include <queue>
#include <vector>
#define INF 0xbadbeef
class Edge {
public:
    int end;
    int weight;
};
int main() {
    int  m, n; // m个顶点，n条边
    int  i, j, k, t;
    int  book[10], count = 0, distance[10];
    Edge node;
    for (i = 0; i < 10; i++)
        book[i] = 0, distance[i] = INF;
    std::vector<Edge> table[10];
    std::queue<int>   que;
    std::cin >> m >> n;
    for (i = 0; i < n; i++) {
        std::cin >> j >> node.end >> node.weight;
        table[j].push_back(node);
    }
    distance[1] = 0;
    que.push(1);
    book[1] = 1;
    while (que.size() && count <= (m - 1) * n) {
        i = que.front();
        que.pop();
        book[i] = 0;
        for (j = 0; j < table[i].size(); j++) {
            count++;
            node = table[i][j];
            if (distance[node.end] > distance[i] + node.weight) {
                distance[node.end] = distance[i] + node.weight;
                if (book[node.end] == 0) {
                    book[node.end] = 1;
                    que.push(node.end);
                }
            }
        }
    }
    if (count > (m - 1) * n)
        std::cout << "Wrong!!\n";
    else
        for (i = 1; i <= m; i++)
            printf("%d ", distance[i]);
    return 0;
}
