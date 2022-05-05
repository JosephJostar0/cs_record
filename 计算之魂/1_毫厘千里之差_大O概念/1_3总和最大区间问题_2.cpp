#include <iostream>
int main() {
    int N, i;
    double *nums;
    scanf("%d", &N);
    nums = (double *)malloc(sizeof(double) * N);
    for (i = 0; i < N; i++)
        scanf("%lf", &nums[i]);
    int p, q, left, right;
    double sum, max_sum = nums[0] - 1;
    for (p = 0; p < N; p++) {
        sum = 0;
        for (q = p; q < N; q++) {
            sum += nums[q];
            if (sum > max_sum)
                max_sum = sum, left = p, right = q;
        }
    }
    printf("sum:%.2f left:%d right:%d", max_sum, left, right);
    free(nums);
    return 0;
}
