#include <iostream>
#include <queue>
int main() {
    std::priority_queue<int, std::vector<int>, std::greater<int>> q;
    int N, i, t, ans = 0;
    scanf("%d", &N);
    for (i = 0; i < N; i++) {
        scanf("%d", &t);
        q.push(t);
    }
    while (q.size() > 1) {
        t = q.top();
        q.pop();
        i = q.top();
        q.pop();
        q.push(t + i);
        ans += t + i;
    }
    printf("%d", ans);
    return 0;
}
