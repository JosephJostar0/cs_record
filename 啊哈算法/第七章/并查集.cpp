#include <iostream>
int  f[1001] = {0}, n, m, sum = 0;
void init() {
    int i;
    for (i = 1; i <= n; i++)
        f[i] = i;
}

//寻找爹地，擒贼先擒王原则
int getFather(int v) {
    if (f[v] == v)
        return v;
    f[v] = getFather(f[v]);
    return f[v];
}

//合并两个子集,靠左原则
void merge(int v, int u) {
    int t1, t2;
    t1 = getFather(v);
    t2 = getFather(u);
    if (t1 != t2)
        f[t2] = t1;
}

int main() {
    int i, x, y;
    std::cin >> n >> m;
    init();
    for (i = 1; i <= m; i++) {
        std::cin >> x >> y;
        merge(x, y);
    }
    for (i = 1; i <= n; i++)
        if (f[i] == i)
            sum++;
    std::cout << sum << std::endl;
    return 0;
}
