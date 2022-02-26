#include <iostream>
#include <stack>
int a[100][100];       //�洢��ͼ��Ϣ
int book[100];         //��¼��Щ���߹���
int bottom = 0x3f3f3f; //��¼��̵�·��Ϊ�೤
int num;               //��ͼ�Ľ����
int edge;              //�ߵ���Ŀ
int order = 5;         //Ŀ�ĵ�ַ
class Node {
public:
    int  me;
    int  next;
    int  distance;
    void set(int i, int j = 1, int k = 0) { me = i, next = j, distance = k; }
} Nodes;
int main() {
    int  i, j, k, now;
    Node node;
    std::cin >> num >> edge;
    std::stack<Node> nodes;
    for (i = 1; i <= num; i++)
        for (j = 1; j <= num; j++) {
            if (i == j)
                a[i][j] = 0;
            else
                a[i][j] = 0x3f3f3f;
        }
    for (i = 0; i < edge; i++) {
        std::cin >> j >> k;
        std::cin >> a[j][k];
    }
    book[1] = 1;
    node.set(1, 2);
    nodes.push(node);
    while (nodes.size()) {
        if (nodes.top().distance > bottom) {
            book[nodes.top().me] = 0;
            nodes.pop();
            if (nodes.size()) {
                node = nodes.top();
                node.next++;
                nodes.pop();
                nodes.push(node);
            }
        } else if (nodes.top().me == order) {
            if (bottom > nodes.top().distance)
                bottom = nodes.top().distance;
            nodes.pop();
            if (nodes.size()) {
                node = nodes.top();
                nodes.pop();
                node.next++;
                nodes.push(node);
            }
        }
        if (nodes.size() == 0)
            break;
        i = nodes.top().next;
        j = nodes.top().me;
        if (i <= num && book[i] == 0 && a[j][i] < 0x3f3f3f && i != j) {
            node.set(i, 2, nodes.top().distance + a[j][i]);
            nodes.push(node);
        } else {
            while (nodes.size()) {
                node = nodes.top();
                node.next++;
                nodes.pop();
                if (node.next <= num) {
                    nodes.push(node);
                    break;
                }
            }
        }
    }
    printf("��̾���Ϊ:%d\n", bottom);
    return 0;
}
