#include <ctime>
#include <iostream>
#include <queue>
template <class T>
class Node {
private:
    T v;
    int height;
    Node *left, *right;

public:
    Node() { left = NULL, right = NULL, height = 1; }
    T getValue() { return v; }
    void updateHeight();
    int getBalanceFactor();
    void setValue(T value) { v = value; }

    template <class C>
    friend int getHeight(Node<C> *root);

    template <class C>
    friend Node<C> *makeNode(C v);

    template <class C>
    friend bool search(Node<C> *root, T key);

    template <class C>
    friend void lTurn(Node<C> *&root);

    template <class C>
    friend void rTurn(Node<C> *&root);

    template <class C>
    friend void insert(Node<C> *&root, C v);

    template <class C>
    friend void inOrder(Node<C> *root);

    template <class C>
    friend void levelOrder(Node<C> *root);
};

template <class T>
int getHeight(Node<T> *root) {
    if (!root)
        return 0;
    return root->height;
}

template <class T>
int Node<T>::getBalanceFactor() {
    return getHeight(left) - getHeight(right);
}

template <class T>
void Node<T>::updateHeight() {
    height = std::max(getHeight(left), getHeight(right)) + 1;
}

template <class T>
Node<T> *makeNode(T v) {
    Node<T> *node = new Node<T>;
    node->setValue(v);
    return node;
}

template <class T>
bool search(Node<T> *root, T key) {
    if (!root)
        return false;
    if (key == root->v)
        return true;
    else if (key < root->v)
        return search(root->left, key);
    else
        return search(root->right, key);
}

template <class T>
void lTurn(Node<T> *&root) {
    if (!root->right)
        return;
    Node<T> *temp = root->right;
    root->right = temp->left;
    temp->left = root;
    temp->updateHeight();
    root->updateHeight();
    root = temp;
}

template <class T>
void rTurn(Node<T> *&root) {
    if (!root->left)
        return;
    Node<T> *temp = root->left;
    root->left = temp->right;
    temp->right = root;
    temp->updateHeight();
    root->updateHeight();
    root = temp;
}

template <class T>
void insert(Node<T> *&root, T v) {
    if (!root) {
        root = makeNode(v);
        return;
    }
    if (v < root->v) {
        insert(root->left, v);
        root->updateHeight();
        if (root->getBalanceFactor() == 2) {
            if (root->left->getBalanceFactor() == 1) // ll型
                rTurn(root);
            else if (root->left->getBalanceFactor() == -1) // lr型
                lTurn(root->left), rTurn(root);
        }
    } else {
        insert(root->right, v);
        root->updateHeight();
        if (root->getBalanceFactor() == -2) {
            if (root->right->getBalanceFactor() == -1) // rr
                lTurn(root);
            else if (root->right->getBalanceFactor() == 1) // rl
                rTurn(root->right), lTurn(root);
        }
    }
}

template <class T>
void inOrder(Node<T> *root) {
    if (!root)
        return;
    inOrder(root->left);
    std::cout << root->v << ' ';
    inOrder(root->right);
}

template <class T>
void levelOrder(Node<T> *root) {
    std::queue<Node<T> *> q;
    Node<T> *temp;
    q.push(root);
    while (!q.empty()) {
        temp = q.front();
        q.pop();
        std::cout << temp->v << ' ';
        if (temp->left)
            q.push(temp->left);
        if (temp->right)
            q.push(temp->right);
    }
}

int main() {
    srand(time(NULL));
    int i;
    Node<int> *root = makeNode(10);
    for (i = 0; i < 5; i++) {
        insert(root, i);
        levelOrder(root);
        printf("\n");
    }
    printf("\n\n");
    for (i = 11; i < 31; i += 3)
        insert(root, i);
    for (i = 0; i < 10; i++)
        insert(root, (int)rand() % 24);
    inOrder(root);
    printf("\n\n");
    levelOrder(root);
    return 0;
}
