#include <iostream>
int  a[100][100];       //�洢��ͼ��Ϣ
int  book[100];         //��¼��Щ���߹���
int  bottom = 0x3f3f3f; //��¼��̵�·��Ϊ�೤
int  num;               //��ͼ�Ľ����
int  order = 5;         //Ŀ�ĵ�ַ
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
    int edge; //�ߵ���Ŀ
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
    printf("��̾���Ϊ:%d\n", bottom);
    return 0;
}
