#include <iostream>
#include <string>
using namespace std;
#define MAXN 100 + 1
string s1, s2;
int dp[MAXN][MAXN];
int DP(int x, int y) {
    if (!x || !y || dp[x][y])
        return dp[x][y];
    int cnt0 = 1 + std::min(DP(x - 1, y), DP(x, y - 1));
    int cnt1 = DP(x - 1, y - 1) + (s1[x - 1] == s2[y - 1] ? 0 : 1);
    dp[x][y] = std::min(cnt0, cnt1);
    return dp[x][y];
}

int main() {
    cin.tie(NULL);
    cin.sync_with_stdio(false);
    int i, j;
    std::cin >> s1 >> s2;
    for (i = 0; i <= s1.size(); i++)
        dp[i][0] = i;
    for (i = 0; i <= s2.size(); i++)
        dp[0][i] = i;
    cout << DP(s1.size(), s2.size());
    return 0;
}
