#include <cstring>
#include <iostream>
#include <stack>
bool flag = false;
class Node {
public:
    int sons[2], current;
    Node() { sons[0] = 0, sons[1] = 0, current = 0; }
} nodes[31];

void postOrder(int root) {
    if (root) {
        postOrder(nodes[root].sons[0]);
        postOrder(nodes[root].sons[1]);
        if (flag)
            printf(" ");
        printf("%d", root);
        flag = true;
    }
}

int main() {
    int N, i, d, dad = 0;
    char work[8];
    scanf("%d", &N);
    std::stack<int> s;
    for (i = 0; i < 2 * N; i++) {
        scanf("%s", work);
        if (!strcmp(work, "Push")) {
            scanf("%d", &d);
            nodes[dad].sons[nodes[dad].current] = d;
            s.push(d);
            dad = d;
        } else {
            dad = s.top();
            s.pop();
            if (!s.empty())
                nodes[s.top()].current = 1;
        }
    }
    postOrder(nodes[0].sons[0]);
    return 0;
}
