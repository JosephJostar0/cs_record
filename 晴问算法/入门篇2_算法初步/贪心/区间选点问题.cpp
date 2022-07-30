#include <algorithm>
#include <iostream>
class Space {
public:
    int l, r;
} space[10000];

bool cmp(const Space a, const Space b) {
    if (a.l != b.l)
        return a.l > b.l;
    return a.r < b.r;
}

int main() {
    int n, i, ans = 0, margin = 100000;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%d%d", &space[i].l, &space[i].r);
    std::sort(space, space + n, cmp);
    for (i = 0; i < n; i++)
        if (space[i].r < margin)
            margin = space[i].l, ans++;
    printf("%d", ans);
    return 0;
}
