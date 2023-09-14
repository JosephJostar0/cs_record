#include <algorithm>
#include <iostream>
#include <vector>
#define MAXN 100 + 1
#define MAXV 1000 + 1
int n, V, dp[MAXN][MAXV], w[MAXN], c[MAXN], flag;
std::vector<int> temp;
std::vector<std::vector<int>> ans;

void dfs(int id, int weight) {
    if (!id || !weight) {
        ans.push_back(temp);
        return;
    }
    int ok = 0;
    if (weight >= w[id] && (dp[id - 1][weight - w[id]] + c[id] == dp[id][weight])) {
        temp.push_back(id);
        dfs(id - 1, weight - w[id]);
        temp.pop_back();
        ok = 1;
    }
    if (dp[id][weight] == dp[id - 1][weight])
        dfs(id - 1, weight), ok = 1;
    if (!ok)
        dfs(id - 1, weight);
}

int main() {
    scanf("%d%d", &n, &V);
    int i, j;
    for (i = 1; i <= n; i++)
        scanf("%d", w + i);
    for (i = 1; i <= n; i++)
        scanf("%d", c + i);
    for (i = 1; i <= n; i++)
        for (j = 1; j <= V; j++) {
            if (j < w[i])
                dp[i][j] = dp[i - 1][j];
            else
                dp[i][j] = std::max(dp[i - 1][j], dp[i - 1][j - w[i]] + c[i]);
        }
    printf("%d\n", dp[n][V]);
    dfs(n, V);
    for (i = 0; i < ans.size(); i++)
        std::reverse(ans[i].begin(), ans[i].end());
    std::sort(ans.begin(), ans.end());
    printf("%d", ans[0][0]);
    for (i = 1; i < ans[0].size(); i++)
        printf(" %d", ans[0][i]);
    return 0;
}
