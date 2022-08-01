#include <iostream>
#include <queue>
int main() {
    std::priority_queue<int> pq;
    int n, k, i, t;
    scanf("%d%d", &n, &k);
    for (i = 0; i < n; i++) {
        scanf("%d", &t);
        if (pq.size() < k)
            pq.push(t);
        else if (t < pq.top()) {
            pq.pop();
            pq.push(t);
        }
    }
    printf("%d", pq.top());
    return 0;
}
