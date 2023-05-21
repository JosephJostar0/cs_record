#include <iostream>
#include <stack>
class Node {
public:
    int data;
    Node *left, *right;
    Node() { data = -1, left = NULL, right = NULL; }
    Node(int d) { data = d, left = NULL, right = NULL; }
};

Node *make_node(int data) {
    Node *temp = new Node(data);
    return temp;
}

Node *init_tree() {
    Node *root = make_node(1);
    root->left = make_node(2);
    root->right = make_node(3);
    root->left->left = make_node(4);
    root->left->right = make_node(5);
    root->right->left = make_node(6);
    root->right->left->right = make_node(7);
    return root;
}

void cycle_order(Node *root) {
    if (root == NULL)
        return;

    bool flag = true;
    Node *last = root;
    std::stack<Node *> s;
    s.push(root);
    while (!s.empty()) {
        std::stack<Node *> temp;
        while (!s.empty()) {
            Node *current = s.top();
            s.pop();
            printf("%d ", current->data);

            Node *p[2] = {current->left, current->right};
            for (int cnt = 0, i = flag ? 0 : 1; cnt < 2; cnt++, i = (i + 1) % 2)
                if (p[i])
                    temp.push(p[i]);
        }
        s = temp;
        flag = !flag;
    }
}

int main() {
    Node *root = init_tree();
    cycle_order(root);
    return 0;
}
