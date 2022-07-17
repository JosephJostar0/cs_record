#include <stdio.h>
int father[10001], network[10001];
int findFather(int x) {
    int f = x;
    while (father[f] >= 0)
        f = father[f];
    while (father[x] >= 0) {
        int a = x;
        x = father[x];
        father[a] = f;
    }
    return f;
}

void Union(int a, int b) {
    int x = findFather(a);
    int y = findFather(b);
    if (x != y) {
        if (father[x] < father[y])
            father[x] += father[y], father[y] = x;
        else
            father[y] += father[x], father[x] = y;
    }
}

int main() {
    int N, i, p, q, ans = 0;
    char line[16], how;
    scanf("%d\n", &N);
    for (i = 1; i <= N; i++)
        father[i] = -1;
    while (1) {
        gets(line);
        if (line[0] == 'S')
            break;
        sscanf(line, "%c %d %d", &how, &p, &q);
        if (how == 'I')
            Union(p, q);
        else {
            if (findFather(p) == findFather(q))
                printf("yes\n");
            else
                printf("no\n");
        }
    }
    for (i = 1; i <= N; i++) {
        int f = findFather(i);
        if (!network[f]++)
            ans++;
    }
    if (ans == 1)
        printf("The network is connected.");
    else
        printf("There are %d components.", ans);
    return 0;
}
