#include<iostream>
class Node{
public:
    int x, y;
}s[100];
int a[51][51], book[51][51];
int top = 0;
int m, n, flag = 0;
void dfs(int x, int y, int front){
    int i;
    if(x == m && y == n + 1){
        flag = 1;
        for(i = 1; i <= top; i++)
            printf("(%d, %d) ", s[i].x, s[i].y);
        return;
    }
    if(x < 1 || x > m || y < 1 || y > n)
        return;
    if(book[x][y] == 1)
        return;
    book[x][y] = 1;
    top++;
    s[top].x = x;
    s[top].y = y;
    if(a[x][y] == 5 || a[x][y] == 6){
        if(front == 1)
            dfs(x, y + 1, 1);
        else if(front == 2)
            dfs(x + 1, y, 2);
        else if(front == 3)
            dfs(x, y + 1, 3);
        else
            dfs(x + 1, y, 4);
    }
    else if(a[x][y] >= 1 && a[x][y] <= 4){
        if(front == 1){
            dfs(x + 1, y, 2);
            dfs(x - 1, y, 4);
        }
        else if(front == 2){
            dfs(x, y + 1, 1);
            dfs(x, y - 1, 3);
        }
        else if(front == 3){
            dfs(x + 1, y, 4);
            dfs(x - 1, y, 2);
        }
        else{
            dfs(x, y + 1, 1);
            dfs(x, y - 1, 3);
        }
    }
    book[x][y] = 0;
    top --;
}
int main(){
    int i, j, num = 0;
    std::cin>>m>>n;
    for(i = 1; i <= m; i++)
        for(j = 1; j <= n; j++)
            std::cin>>a[i][j];
    dfs(1, 1, 1);
    if(flag == 0)
        printf("impossible\n");
    return 0;
}
