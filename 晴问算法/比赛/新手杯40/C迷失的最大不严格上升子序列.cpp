#include <algorithm>
#include <iostream>
#include <vector>
#define MAXN 1000
int a[MAXN], n, ans = 0;
std::vector<int> v, place;
void lis() {
    v.clear();
    for (int i = 0; i < n; i++) {
        if (v.empty() || a[i] >= v.back())
            v.push_back(a[i]);
        else {
            auto it = std::upper_bound(v.begin(), v.end(), a[i]);
            *it = a[i];
        }
    }
    ans = v.size() > ans ? v.size() : ans;
}

void dfs(int step = 0) {
    if (step == place.size()) {
        lis();
        return;
    }
    for (int i = 0; i < 10; i++) {
        a[place[step]] = i;
        dfs(step + 1);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", a + i);
        if (a[i] == -1)
            place.push_back(i);
    }
    dfs();
    printf("%d", ans);
    return 0;
}
