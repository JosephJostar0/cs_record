#include <iostream>
#include <string>
using namespace std;
#define MAXN 100 + 1
string s1, s2;
int dp[MAXN][MAXN];
int main() {
    cin.tie(NULL);
    cin.sync_with_stdio(false);
    int i, j;
    cin >> s1 >> s2;
    for (i = 0; i <= s1.size(); i++)
        dp[i][0] = i;
    for (i = 0; i <= s2.size(); i++)
        dp[0][i] = i;
    for (i = 1; i <= s1.size(); i++)
        for (j = 1; j <= s2.size(); j++) {
            dp[i][j] = 1 + min(dp[i][j - 1], dp[i - 1][j]);
            dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? 0 : 1));
        }
    cout << dp[s1.size()][s2.size()];
    return 0;
}
