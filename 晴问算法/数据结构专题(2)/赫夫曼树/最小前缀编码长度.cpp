#include <iostream>
#include <queue>
int count[256];
int main() {
    char line[101];
    std::cin.getline(line, 101);
    int i, j, ans = 0;
    for (i = 0; line[i]; i++)
        count[(int)line[i]]++;
    std::priority_queue<int, std::vector<int>, std::greater<int>> q;
    for (i = 0; i < 256; i++)
        if (count[i])
            q.push(count[i]);
    while (q.size() > 1) {
        i = q.top(), q.pop();
        j = q.top(), q.pop();
        q.push(i + j);
        ans += i + j;
    }
    printf("%d", ans);
    return 0;
}
