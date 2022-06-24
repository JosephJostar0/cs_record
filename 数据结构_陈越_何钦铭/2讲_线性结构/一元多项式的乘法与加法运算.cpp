#include <iostream>
int a[2][2001] = {0}, b[2][2001] = {0};
void input(int x) {
    int i, top, p, q;
    scanf("%d", &top);
    for (i = 0; i < top; i++) {
        scanf("%d%d", &p, &q);
        a[x][q] = p;
    }
}

void output(int x) {
    int i, j;
    for (i = 2000, j = 1; i >= 0; i--)
        if (b[x][i]) {
            if (!j)
                printf(" ");
            printf("%d %d", b[x][i], i);
            j = 0;
        }
    if (j)
        printf("0 0");
    printf("\n");
}

int main() {
    int i, j;
    input(0), input(1);

    for (i = 0; i < 1001; i++)
        for (j = 0; j < 1001; j++)
            b[0][i + j] += a[0][i] * a[1][j];
    output(0);

    for (i = 0; i < 1001; i++)
        if (a[0][i] || a[1][i])
            b[1][i] = a[0][i] + a[1][i];
    output(1);
    return 0;
}
