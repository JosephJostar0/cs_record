#include <iostream>
using namespace std;
#define MAXN 1001
int n, arr[MAXN], top = 0, dp[MAXN][2];
bool isGCD1(int a, int b) {
    if (a < b)
        swap(a, b);
    if (b == 0)
        return a == 1;
    return isGCD1(b, a % b);
}
int main() {
    ios::sync_with_stdio(false);
    cout.tie(NULL);
    cin.tie(NULL);
    int i, j, current;
    bool flag;
    cin >> n;
    for (i = 0; i < n; i++)
        cin >> arr[i];
    for (i = 0; i < n; i++) {
        dp[i][0] = dp[i][1] = 1;
        for (j = 0; j < i; j++) {
            if (isGCD1(arr[i], arr[j]))
                dp[i][0] = max(dp[i][0], dp[j][1] + 1);
            else
                dp[i][1] = max(dp[i][1], dp[j][0] + 1);
        }
        top = max(top, max(dp[i][0], dp[i][1]));
    }
    cout << top;
    return 0;
}
