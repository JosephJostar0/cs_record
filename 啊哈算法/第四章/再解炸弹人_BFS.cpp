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
char a[21][21];//�洢��ͼ
int book[21][21];//�ж��߹��õ���û
int m, n;//��ͼ��С
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
    int top, endx, endy;//��¼��ը������������
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
    printf("��ը���ŵ�(%d, %d)��,����ʹ��������������Ϊ%d\n", endx, endy, top);
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