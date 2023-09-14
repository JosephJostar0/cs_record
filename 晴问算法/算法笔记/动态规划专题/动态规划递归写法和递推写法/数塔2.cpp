#include <iostream>
int nums[101][101];
int main() {
    int n, i, j;
    scanf("%d", &n);
    for (i = 1; i <= n; i++)
        for (j = 1; j <= i; j++)
            scanf("%d", &nums[i][j]);
    for (i = n - 1; i >= 1; i--)
        for (j = 1; j <= i; j++)
            nums[i][j] += std::max(nums[i + 1][j + 1], nums[i + 1][j]);
    printf("%d", nums[1][1]);
    return 0;
}
