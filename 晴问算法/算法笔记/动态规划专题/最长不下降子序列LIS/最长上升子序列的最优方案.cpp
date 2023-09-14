#include <iostream>
#define MAXN 100
int arr[MAXN], dp[MAXN], left[MAXN];
void dfs(int x) {
    if (left[x] != x)
        dfs(left[x]);
    if (x != left[x])
        printf(" ");
    printf("%d", arr[x]);
}

int main() {
    int n, i, ans = 0, temp;
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d", arr + i);
        dp[i] = 1, left[i] = i;
        for (int j = 0; j < i; j++)
            if (arr[j] <= arr[i] && dp[j] + 1 > dp[i])
                dp[i] = dp[j] + 1, left[i] = j;
        ans = dp[i] > dp[ans] ? i : ans;
    }
    printf("%d\n", dp[ans]);
    dfs(ans);
    return 0;
}
