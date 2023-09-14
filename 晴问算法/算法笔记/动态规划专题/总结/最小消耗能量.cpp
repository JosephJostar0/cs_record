#include <iostream>
#define MAXN 10000 + 1
int height[MAXN], dp[MAXN];
int getDP(int n) {
    if (n <= 1 || dp[n])
        return dp[n];
    int one = getDP(n - 1) + std::abs(height[n] - height[n - 1]);
    int two = getDP(n - 2) + std::abs(height[n] - height[n - 2]);
    dp[n] = std::min(one, two);
    return dp[n];
}

int main() {
    int n, i;
    scanf("%d", &n);
    for (i = 1; i <= n; i++)
        scanf("%d", height + i);
    printf("%d", getDP(n));
    return 0;
}
