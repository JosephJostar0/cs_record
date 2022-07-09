#include <iostream>
bool check(int tree[], int input[], int high) {
    if (high == -1)
        return true;
    if (tree[0] != input[0])
        return false;
    int i, l[2] = {0}, r[2] = {0}, left[2][11], right[2][11];
    for (i = 1; i <= high; i++) {
        if (tree[i] <= tree[0])
            left[0][l[0]++] = tree[i];
        else
            right[0][r[0]++] = tree[i];
        if (input[i] <= input[0])
            left[1][l[1]++] = input[i];
        else
            right[1][r[1]++] = input[i];
    }
    return (l[0] == l[1]) && check(left[0], left[1], l[0] - 1) && check(right[0], right[1], r[0] - 1);
}

int main() {
    int i, N, turn, tree[11], input[11];
    while (true) {
        scanf("%d", &N);
        if (!N)
            break;
        scanf("%d", &turn);
        for (i = 0; i < N; i++)
            scanf("%d", tree + i);
        while (turn) {
            turn--;
            for (i = 0; i < N; i++)
                scanf("%d", input + i);
            if (check(tree, input, N - 1))
                printf("Yes\n");
            else
                printf("No\n");
        }
    }
    return 0;
}
