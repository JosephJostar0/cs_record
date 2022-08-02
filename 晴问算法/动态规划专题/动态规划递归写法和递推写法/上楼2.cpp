#include <iostream>
int dp[10001] = {1, 1};
int main() {
    int n;
    scanf("%d", &n);
    for (int i = 2; i <= n; i++)
        dp[i] = (dp[i - 1] + dp[i - 2]) % 10007;
    printf("%d", dp[n]);
    return 0;
}
