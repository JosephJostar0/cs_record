#include <iostream>
#define MAXN 100
int dp[MAXN + 1][MAXN + 1];
char s1[MAXN + 1], s2[MAXN + 1];
int main() {
    int i, j;
    scanf("%s\n%s", s1 + 1, s2 + 1);
    for (i = 1; s1[i]; i++)
        for (j = 1; s2[j]; j++) {
            if (s1[i] == s2[j])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = std::max(dp[i][j - 1], dp[i - 1][j]);
        }
    printf("%d", dp[i - 1][j - 1]);
    return 0;
}
