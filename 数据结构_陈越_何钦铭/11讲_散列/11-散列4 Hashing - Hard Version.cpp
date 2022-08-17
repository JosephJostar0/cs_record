#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
#define MAXN 1000
int map[MAXN], take[MAXN];
int main() {
    int N, i, mod, flag = 0, j;
    scanf("%d", &N);
    std::vector<int> alter[MAXN], v;
    std::unordered_map<int, int> fun;
    for (i = 0; i < N; i++) {
        scanf("%d", map + i);
        if (map[i] >= 0) {
            mod = map[i] % N;
            v.push_back(map[i]);
            alter[mod].push_back(map[i]);
            fun[map[i]] = i;
        }
    }
    std::sort(v.begin(), v.end());
    while (!v.empty()) {
        std::vector<int>::iterator it;
        for (it = v.begin(); it != v.end(); it++) {
            i = *it;
            mod = i % N;
            if (fun[i] == mod)
                break;
            for (j = mod; j % N != fun[i]; j++)
                if (!take[j % N])
                    break;
            if (j % N == fun[i])
                break;
        }
        if (flag)
            printf(" ");
        printf("%d", i);
        v.erase(it);
        flag = 1;
        take[fun[i]] = 1;
    }
    return 0;
}
