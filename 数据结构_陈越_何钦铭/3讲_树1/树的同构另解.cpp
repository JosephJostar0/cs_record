#include <iostream>
int N;
class Node {
public:
    char letter;
    int  left, right;
    Node() { left = right = -1; }
} nodes[2][11];

int input(int t) {
    scanf("%d\n", &N);
    char l, r, line[10];
    int  flag[11] = {0}, i;
    for (i = 0; i < N; i++) {
        std::cin.getline(line, 10);
        sscanf(line, "%c %c %c", &nodes[t][i].letter, &l, &r);
        if (l != '-') {
            nodes[t][i].left       = (int)l - (int)'0';
            flag[nodes[t][i].left] = 1;
        }
        if (r != '-') {
            nodes[t][i].right       = (int)r - (int)'0';
            flag[nodes[t][i].right] = 1;
        }
    }
    for (i = 0; i < N; i++)
        if (!flag[i])
            break;
    return i;
}

bool checkTree(int r1, int r2) {
    if (r1 != -1 && r2 != -1) {
        int  t1[2] = {nodes[0][r1].left, nodes[0][r1].right}, t2[2] = {nodes[1][r2].left, nodes[1][r2].right};
        bool f = (nodes[0][r1].letter == nodes[1][r2].letter);
        return f && ((checkTree(t1[0], t2[0]) && checkTree(t1[1], t2[1])) ||
                     (checkTree(t1[0], t2[1]) && checkTree(t1[1], t2[0])));
    } else if (r1 == r2)
        return true;
    return false;
}

int main() {
    int root[2], i;
    for (i = 0; i < 2; i++)
        root[i] = input(i);
    if (checkTree(root[0], root[1]))
        printf("Yes");
    else
        printf("No");
    return 0;
}
