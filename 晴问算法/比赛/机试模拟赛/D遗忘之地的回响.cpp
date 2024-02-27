#include <algorithm>
#include <iostream>
using namespace std;
#define MAXN 17
typedef long long LL;
int n, arr[MAXN];
LL ans = 1e12;
void dfs(int step = 0, LL h1 = 0, LL h2 = 0) {
    if (step == n) {
        ans = min(ans, abs(h1 - h2));
        return;
    }
    dfs(step + 1, h1 + arr[step], h2);
    dfs(step + 1, h1, h2 + arr[step]);
}
int main() {
    ios::sync_with_stdio(false);
    cout.tie(NULL);
    cin.tie(NULL);
    int i;
    cin >> n;
    for (i = 0; i < n; i++)
        cin >> arr[i];
    sort(arr, arr + n);
    dfs();
    cout << ans;
    return 0;
}