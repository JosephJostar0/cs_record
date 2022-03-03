#include <iostream>
#include <queue>
int e[50][50] = {0};
int book[50]  = {0};
class Note {
public:
    int  x;
    int  s;
    void set(int X, int S) { x = X, s = S; };
};
int main() {
    int city, airLine, start, end;
    int i, j, k;
    std::cin >> city >> airLine >> start >> end;
    Note note;
    for (i = 1; i <= city; i++)
        for (k = 1; k <= city; k++)
            e[i][k] = 99999;
    for (i = 0; i < airLine; i++) {
        std::cin >> j >> k;
        e[j][k] = 1;
        e[k][j] = 1;
    }
    std::queue<Note> notes;
    note.set(start, 0);
    notes.push(note);
    book[start] = 1;
    while (notes.size()) {
        note = notes.front();
        notes.pop();
        j = note.x;
        k = note.s;
        if (j == end)
            break;
        for (i = 1; i <= city; i++)
            if (book[i] == 0 && e[j][i] == 1) {
                note.set(i, k + 1);
                notes.push(note);
            }
    }
    printf("need %d turn", note.s);
    return 0;
}
