#include<iostream>
#include<stack>
class Note {
public:
    //水管1-6
    int x, y, next, mine;
    bool flag;
    void set(int i, int j, int k, int my, bool type = false) {
        x = i, y = j, next = k, mine = my, flag = type;
    }
};
int a[51][51], book[51][51];
int m, n;
int main() {
    //1水从左进，2水从上进，3水从右进，4水从下进
    int i, j, how, x, y;
    bool over = false;
    std::stack<Note> notes;
    Note note;
    std::cin >> m >> n;
    for (i = 1; i <= m; i++)
        for (j = 1; j <= n; j++)
            std::cin >> a[i][j];
    note.set(1, 1, 1, 1);
    notes.push(note);
    how = 1;
    while (notes.size() && !over) {
        while (!over) {
            x = notes.top().x;
            y = notes.top().y;
            how = notes.top().next;
            if (how == 1)
                y += 1;
            else if (how == 2)
                x += 1;
            else if (how == 3)
                y -= 1;
            else
                x -= 1;
            if (x == m && y == n + 1) {
                over = true;
                break;
            }
            if (x > m || x < 1 || y > n || y < 1)
                break;
            if (a[x][y] == 0 || book[x][y] == 1)
                break;
            if (a[x][y] >= 5) {
                if (how == 1 || how == 3)
                    a[x][y] = 5;
                else
                    a[x][y] = 6;
                note.set(x, y, how, how);
            }
            else {
                if (how == 1) {
                    a[x][y] = 3;
                    note.set(x, y, 2, how, true);
                }
                else if (how == 2) {
                    a[x][y] = 1;
                    note.set(x, y, 1, how, true);
                }
                else if (how == 3) {
                    a[x][y] = 1;
                    note.set(x, y, 4, how, true);
                }
                else {
                    a[x][y] = 2;
                    note.set(x, y, 1, how, true);
                }
            }
            notes.push(note);
            book[x][y] = 1;
        }
        while (notes.size() && !over) {
            note = notes.top();
            x = note.x, y = note.y;
            notes.pop();
            if (note.flag) {
                if (note.mine == 1) {
                    a[x][y] = 4;
                    note.set(x, y, 4, note.mine);
                }
                else if (note.mine == 2) {
                    a[x][y] = 4;
                    note.set(x, y, 3, note.mine);
                }
                else if (note.mine == 3) {
                    a[x][y] = 2;
                    note.set(x, y, 2, note.mine);
                }
                else {
                    a[x][y] = 3;
                    note.set(x, y, 3, note.mine);
                }
                notes.push(note);
                if (over)
                    exit(2);
                break;
            }
            else
                book[x][y] = 0;
        }
    }
    if (over) {
        printf("有解,用了%d步:\n", notes.size());
        std::stack<Note> alter;
        while(notes.size()){
            alter.push(notes.top());
            notes.pop();
        }
        while(alter.size()){
            note = alter.top();
            printf("(%d, %d) ", note.x, note.y);
            alter.pop();
        }
    }
    else
        printf("哎呀呀无解啦\n");
    return 0;
}
