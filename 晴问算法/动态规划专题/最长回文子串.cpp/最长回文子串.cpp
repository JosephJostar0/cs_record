#include <cstring>
#include <iostream>
#define MAXN 100
int dp[MAXN][MAXN];
char s[MAXN];
int main() {
    scanf("%s", s);
    int i, j, ans = 1, size = strlen(s);
    for (i = 0; s[i]; i++) {
        dp[i][i] = 1;
        if (s[i] == s[i + 1])
            dp[i][i + 1] = 1, ans = 2;
    }
    for (i = 2; i < size; i++)
        for (j = 0; j < size - i; j++)
            if (s[j] == s[j + i])
                if (dp[j + 1][j + i - 1])
                    dp[j][j + i] = 1, ans = i + 1;
    printf("%d", ans);
    return 0;
}
