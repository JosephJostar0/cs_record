#include <iostream>
int  a[100][100];       //存储地图信息
int  book[100];         //记录哪些点走过了
int  bottom = 0x3f3f3f; //记录最短的路径为多长
int  num;               //地图的结点数
int  order = 5;         //目的地址
void dfs(int x, int distance = 0) {
    int i;
    if (distance > bottom)
        return;
    if (x == order) {
        if (bottom > distance)
            bottom = distance;
        return;
    }
    for (i = 1; i <= num; i++) {
        if (i == x || book[i] == 1)
            continue;
        if (a[x][i] >= 0x3f3f3f)
            continue;
        book[i] = 1;
        dfs(i, distance + a[x][i]);
        book[i] = 0;
    }
}
int main() {
    int edge; //边的数目
    int i, j, k;
    std::cin >> num >> edge;
    for (i = 1; i <= num; i++)
        for (j = 1; j <= num; j++) {
            if (i != j)
                a[i][j] = 0x3f3f3f;
            else
                a[i][j] = 0;
        }
    for (i = 1; i <= edge; i++) {
        std::cin >> j >> k;
        std::cin >> a[j][k];
    }
    book[1] = 1;
    dfs(1);
    printf("最短距离为:%d\n", bottom);
    return 0;
}
