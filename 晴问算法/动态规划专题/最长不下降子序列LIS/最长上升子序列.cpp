#include <iostream>
#define MAXN 100
int arr[MAXN], dp[MAXN];
int main() {
    int n, i, ans = 0;
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d", arr + i);
        dp[i] = 1;
        for (int j = 0; j < i; j++)
            if (arr[j] <= arr[i] && dp[j] + 1 > dp[i])
                dp[i] = dp[j] + 1;
        ans = std::max(ans, dp[i]);
    }
    printf("%d", ans);
    return 0;
}
