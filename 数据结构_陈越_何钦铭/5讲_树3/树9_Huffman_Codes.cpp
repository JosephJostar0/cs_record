#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
std::unordered_map<char, int> map;
std::unordered_map<std::string, int> check;

int main() {
    int N, M, i, j, k, sum = 0, act;
    char letter, line[64], code[64];
    bool flag;
    std::priority_queue<int, std::vector<int>, std::greater<int>> q;
    std::string str;
    scanf("%d\n", &N);
    for (i = 0; i < N; i++) {
        scanf("%c %d", &letter, &j);
        getchar();
        map[letter] = j;
        q.push(j);
    }
    while (q.size() > 1) {
        i = q.top(), q.pop();
        j = q.top(), q.pop();
        q.push(i + j);
        sum += i + j;
    }
    scanf("%d\n", &M);
    for (i = 0; i < M; i++) {
        act = 0, flag = true, check.clear();
        for (j = 0; j < N; j++) {
            str.clear();
            std::cin.getline(line, 64);
            sscanf(line, "%c %s", &letter, code);
            for (k = 0; code[k]; k++) {
                str.push_back(code[k]);
                check[str]++;
            }
            if (check[str] > 1)
                flag = false;
            act += str.size() * map[letter];
        }
        if (flag && act == sum)
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}
