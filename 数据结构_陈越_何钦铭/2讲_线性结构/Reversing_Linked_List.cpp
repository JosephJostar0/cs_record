#include <iostream>
#include <stack>
#include <vector>
using namespace std;
class Node {
public:
    int data;
    int next;
    int add;
} nodes[100000], n;
vector<stack<Node>> v;

int main() {
    int i, N, K, next;
    bool flag = false;
    cin >> next >> N >> K;
    stack<Node> s;
    for (i = 0; i < N; i++) {
        cin >> n.add >> n.data >> n.next;
        nodes[n.add] = n;
    }
    while (next != -1) {
        s.push(nodes[next]);
        next = nodes[next].next;
        if (s.size() == K)
            while (s.size()) {
                n = s.top();
                s.pop();
                if (flag)
                    printf("%05d\n%05d %d ", n.add, n.add, n.data);
                else
                    printf("%05d %d ", n.add, n.data), flag = true;
            }
    }
    for (K = s.size(), i = 0; s.size(); s.pop())
        n = s.top(), nodes[i++] = n;
    for (i = K - 1; i >= 0; i--) {
        n = nodes[i];
        if (flag)
            printf("%05d\n%05d %d ", n.add, n.add, n.data);
        else
            printf("%05d %d ", n.add, n.data), flag = true;
    }
    printf("-1");
    return 0;
}
