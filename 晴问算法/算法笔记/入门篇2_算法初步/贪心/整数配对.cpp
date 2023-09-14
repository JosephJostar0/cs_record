#include <algorithm>
#include <iostream>
int main() {
    int m, n, i, j, ans = 0;
    int s[10000], t[10000];
    scanf("%d%d", &n, &m);
    for (i = 0; i < n; i++)
        scanf("%d", s + i);
    for (i = 0; i < m; i++)
        scanf("%d", t + i);
    std::sort(s, s + n), std::sort(t, t + m);
    for (i = 0, j = 0; i < n && j < m; j++)
        if (s[i] <= t[j])
            i++, ans++;
    printf("%d", ans);
    return 0;
}
