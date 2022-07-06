#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
std::unordered_map<char, std::vector<int>> map[2];
char letter[2][10];

void input(int t) {
    int N, i;
    char p, q, line[8];
    scanf("%d", &N);
    getchar();
    for (i = 0; i < N; i++) {
        std::cin.getline(line, 8);
        sscanf(line, "%c %c %c", &letter[t][i], &p, &q);
        map[t][letter[t][i]].push_back(0);
        if (p != '-')
            map[t][letter[t][i]].push_back((int)(p - '0'));
        if (q != '-')
            map[t][letter[t][i]].push_back((int)(q - '0'));
    }
}

int main() {
    input(0), input(1);
    int i, t;
    char c;
    for (i = (int)'A'; i <= (int)'Z'; i++) {
        c = (char)i;
        if (map[0].find(c) == map[0].end() || map[1].find(c) == map[1].end())
            if (map[0].find(c) != map[1].find(c))
                break;
        if (map[0][c].size() != map[1][c].size())
            break;
        for (t = 1; t < map[0][c].size(); t++) {
            if (letter[0][map[0][c][t]] != letter[1][map[1][c][1]]) {
                if (map[0][c].size() == 3) {
                    if (letter[0][map[0][c][t]] != letter[1][map[1][c][2]])
                        break;
                } else
                    break;
            }
        }
    }
    if (i <= (int)'Z')
        printf("No");
    else
        printf("Yes");
    return 0;
}
