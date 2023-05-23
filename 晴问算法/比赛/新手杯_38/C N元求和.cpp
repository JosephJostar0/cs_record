#include <iostream>
#include <set>
#define MAXN 10
int arr[MAXN], n;
std::set<int> s;
void dfs(int step = 0, int temp = 0) {
    if (step == n) {
        s.insert(temp);
        return;
    }
    dfs(step + 1, temp + arr[step]);
    dfs(step + 1, temp - arr[step]);
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", arr + i);
    dfs();
    for (auto it : s)
        printf("%d\n", it);
    return 0;
}
