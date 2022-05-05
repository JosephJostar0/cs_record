#include <iostream>
class MaxSum {
public:
    double sum;
    int left, right;
    void setAll(double s, int l, int r) { sum = s, left = l, right = r; }
    MaxSum(double s = -0xbadbeef, int l = -1, int r = -1) { setAll(s, l, r); }
};

MaxSum findMax(double nums[], int p, int q) {
    MaxSum ms;
    if (p == q) {
        ms.setAll(nums[p], p, q);
        return ms;
    }
    MaxSum Lms = findMax(nums, p, (p + q) / 2);
    MaxSum Rms = findMax(nums, (p + q) / 2 + 1, q);
    if (Lms.right == Rms.left - 1) {
        if (Lms.sum > 0 && Rms.sum > 0)
            ms.setAll(Lms.sum + Rms.sum, Lms.left, Rms.right);
        else if (Lms.sum > Rms.sum)
            ms = Lms;
        else
            ms = Rms;
    } else {
        int t;
        double sum = Lms.sum + Rms.sum;
        for (t = Lms.right + 1; t < Rms.left; t++)
            sum += nums[t];
        ms.setAll(sum, Lms.left, Rms.right);
        if (ms.sum < Lms.sum)
            ms = Lms;
        if (ms.sum < Rms.sum)
            ms = Rms;
    }
    return ms;
}

int main() {
    int N, i;
    double *nums;
    scanf("%d", &N);
    nums = (double *)malloc(sizeof(double) * N);
    for (i = 0; i < N; i++)
        scanf("%lf", &nums[i]);
    MaxSum ms = findMax(nums, 0, N - 1);
    printf("sum:%.2f left:%d right:%d", ms.sum, ms.left, ms.right);
    return 0;
}
