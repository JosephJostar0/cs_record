#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long LL;
#define MAXN 17
#define MAXT (LL)(16 * 1e9)
int main() {
    ios::sync_with_stdio(false);
    cout.tie(NULL);
    cin.tie(NULL);

    LL total = 0, target, arr[MAXN];
    int i, j, n;

    cin >> n;
    for (i = 0; i < n; i++) {
        cin >> arr[i];
        arr[i] += (LL)1e9;
        total += arr[i];
    }
    target = total / 2;
    vector<bool> dp(MAXT, false);
    dp[0] = true;
    for (i = 0; i < n; i++)
        for (j = target; j >= 0; j--)
            if (j >= arr[i])
                dp[j] = dp[j] || dp[j - arr[i]];
    for (i = target; i >= 0; i--)
        if (dp[i])
            break;
    cout << abs(total - 2 * i);
    return 0;
}
