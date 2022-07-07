#include <iostream>
#include <queue>
class Node {
public:
    int data;
    int child[2];
    Node() { data = -1, child[0] = -1, child[1] = -1; }
} nodes[10];
int son[10];

int main() {
    int N, i, t;
    bool flag = false;
    char line[4], p, q;
    scanf("%d", &N);
    getchar();
    for (i = 0; i < N; i++) {
        nodes[i].data = i;
        std::cin.getline(line, 4);
        sscanf(line, "%c %c", &p, &q);
        if (p != '-') {
            nodes[i].child[0] = (int)(p - '0');
            son[nodes[i].child[0]] = 1;
        }
        if (q != '-') {
            nodes[i].child[1] = (int)(q - '0');
            son[nodes[i].child[1]] = 1;
        }
    }
    for (i = 0; i < N; i++)
        if (!son[i])
            break;
    t = i;
    std::queue<int> que;
    que.push(t);
    while (!que.empty()) {
        t = que.front();
        que.pop();
        for (i = 0, N = 0; i < 2; i++)
            if (nodes[t].child[i] != -1)
                que.push(nodes[t].child[i]), N++;
        if (!N) {
            if (flag)
                printf(" ");
            printf("%d", t), flag = true;
        }
    }
    return 0;
}
