#include <iostream>
bool flag = false;
class Node {
public:
    int data, height;
    Node *left, *right;
    Node() { height = 1, left = NULL, right = NULL; }
};

int getHeight(Node *root) {
    if (!root)
        return 0;
    return root->height;
}

int getBalanceFactor(Node *root) { return getHeight(root->left) - getHeight(root->right); }

void updateHeight(Node *root) { root->height = std::max(getHeight(root->left), getHeight(root->right)) + 1; }

void lTurn(Node *&root) {
    if (!root || !root->right)
        return;
    Node *temp = root->right;
    root->right = temp->left;
    temp->left = root;
    updateHeight(root);
    updateHeight(temp);
    root = temp;
}

void rTurn(Node *&root) {
    if (!root || !root->left)
        return;
    Node *temp = root->left;
    root->left = temp->right;
    temp->right = root;
    updateHeight(root);
    updateHeight(temp);
    root = temp;
}

void insert(Node *&root, int value) {
    if (!root) {
        root = new Node;
        root->data = value;
        return;
    }
    if (value < root->data) {
        insert(root->left, value);
        updateHeight(root);
        if (getBalanceFactor(root) == 2) {
            if (getBalanceFactor(root->left) == 1)
                rTurn(root);
            else
                lTurn(root->left), rTurn(root);
        }
    } else {
        insert(root->right, value);
        updateHeight(root);
        if (getBalanceFactor(root) == -2) {
            if (getBalanceFactor(root->right) == -1)
                lTurn(root);
            else
                rTurn(root->right), lTurn(root);
        }
    }
}

void preOrder(Node *root) {
    if (!root)
        return;
    if (flag)
        printf(" ");
    printf("%d", root->data);
    flag = true;
    preOrder(root->left);
    preOrder(root->right);
}

int main() {
    int n, i, t;
    scanf("%d\n%d", &n, &i);
    Node *root = new Node;
    root->data = i;
    for (i = 1; i < n; i++) {
        scanf("%d", &t);
        insert(root, t);
    }
    preOrder(root);
    return 0;
}
