#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
std::unordered_map<long long, int> map;
std::vector<long long> v;
bool cmp(long long a, long long b) {
    if (map[a] != map[b])
        return map[a] > map[b];
    return a < b;
}

int main() {
    int N, i;
    long long call, take;
    scanf("%d", &N);
    for (i = 0; i < N; i++) {
        scanf("%lld%lld", &call, &take);
        if (!map[call])
            v.push_back(call);
        if (!map[take])
            v.push_back(take);
        map[call]++, map[take]++;
    }
    std::sort(v.begin(), v.end(), cmp);
    int top = map[v[0]], cnt = 1;
    printf("%lld %d", v[0], top);
    for (i = 1; i < N; i++, cnt++)
        if (map[v[i]] != top)
            break;
    if (cnt > 1)
        printf(" %d", cnt);
    return 0;
}
