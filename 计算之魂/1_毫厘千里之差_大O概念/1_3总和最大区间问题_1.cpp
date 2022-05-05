#include <iostream>
int main() {
    int N, i;
    double *nums;
    scanf("%d", &N);
    nums = (double *)calloc(N, sizeof(double));
    for (i = 0; i < N; i++)
        scanf("%lf", &nums[i]);
    int left, right;
    int p, q;
    double sum, max_sum;
    for (p = 0; p < N; p++)
        for (q = p; q < N; q++) {
            sum = 0;
            for (i = p; i <= q; i++)
                sum += nums[i];
            if (sum > max_sum)
                left = p, right = q, max_sum = sum;
        }
    printf("sum:%.2f left:%d right:%d", max_sum, left, right);
    free(nums);
    return 0;
}
