#include<iostream>
#include<queue>
class Note{
public:
    int x;
    int y;
    void set(int a, int b){
        x = a, y = b;
    }
};
char a[21][21];//存储地图
int book[21][21];//判断走过该点了没
int m, n;//地图大小
int getNum(int x, int y){
    int i, sum = 0;
    for(i = x; i >= 0 && a[i][y] != '#'; i--)
        if(a[i][y] == 'G')
            sum++;
    for(i = x + 1; i < m && a[i][y] != '#'; i++)
        if(a[i][y] == 'G')
            sum++;
    for(i = y; i >= 0 && a[x][i] != '#'; i--)
        if(a[x][i] == 'G')
            sum++;
    for(i = y + 1; i < n && a[x][i] != '#'; i++)
        if(a[x][i] == 'G')
            sum++;
    return sum;
}
int main(){
    std::queue<Note> notes;
    Note note;
    int next[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int startx, starty, x, y, num;
    int i, j;
    int top, endx, endy;//记录能炸死的最大敌人数
    std::cin>>m>>n>>startx>>starty;
    for(i = 0; i < m; i++)
        for(j = 0; j < n; j++)
            std::cin>>a[i][j];
    top = getNum(startx, starty);
    x = startx, y = starty;
    endx = x, endy = y;
    note.set(x, y);
    notes.push(note);
    while(notes.size()){
        for(i = 0; i < 4; i++){
            x = notes.front().x + next[i][0];
            y = notes.front().y + next[i][1];
            if(x < 0 || x >= m || y < 0 || y >= n)
                continue;
            if(a[x][y] == '.' && book[x][y] == 0){
                book[x][y] = 1;
                note.set(x, y);
                notes.push(note);
                num = getNum(x, y);
                if(num > top){
                    top = num;
                    endx = x;
                    endy = y;
                }
            }
        }
        notes.pop();
    }
    printf("把炸弹放到(%d, %d)处,可以使消灭敌人数达最大为%d\n", endx, endy, top);
    return 0;
}
/**
 * 
#############
#GG.GGG#GGG.#
###.#G#G#G#G#
#.......#..G#
#G#.###.#G#G#
#GG.GGG.#.GG#
#G#.#G#.#.#.#
##G...G.....#
#G#.#G###.#G#
#...G#GGG.GG#
#G#.#G#G#.#G#
#GG.GGG#G.GG#
#############
 * 
 */