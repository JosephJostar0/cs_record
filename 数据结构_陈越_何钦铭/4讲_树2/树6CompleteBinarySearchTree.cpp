#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
int pow(int a, int x) {
    if (x == 0)
        return 1;
    if (x & 1)
        return a * pow(a, x - 1);
    int s = pow(a, x / 2);
    return s * s;
}

int getIndex(int size) {
    if (!size)
        return 0;
    int i = 0, k = 0;
    for (i = 0; i < size; i++) {
        k = pow(2, i) - 1;
        if (2 * k + pow(2, i + 1) >= size - 1)
            break;
    }
    return size - k - 1 - std::max(0, size - 1 - 2 * k - pow(2, i));
}

int main() {
    int n, i, t;
    bool flag = false;
    std::vector<int> v;
    std::queue<std::vector<int>> q;
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d", &t);
        v.push_back(t);
    }
    std::sort(v.begin(), v.end());
    q.push(v);
    while (!q.empty()) {
        v = q.front();
        q.pop();
        t = getIndex(v.size());
        if (flag)
            printf(" ");
        printf("%d", v[t]);
        flag = true;
        std::vector<int> v0(v.begin(), v.begin() + t);
        std::vector<int> v1(v.begin() + t + 1, v.end());
        if (v0.size())
            q.push(v0);
        if (v1.size())
            q.push(v1);
    }
    return 0;
}
