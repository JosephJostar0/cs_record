//这是个错误示范。。。。
#include <iostream>
class SumMax {
public:
    int left, right;
    double sum;
    void setAll(int l, int r, double s) { left = l, right = r, sum = s; }
};
double *nums;

SumMax findSum(int Lmargin, int Rmargin) {
    SumMax sm;
    int i, cut = -1;
    double sum = 0;
    sm.setAll(Lmargin, Lmargin, nums[Lmargin]);
    for (i = Lmargin; i <= Rmargin && nums[i] <= 0; i++)
        if (nums[i] > sm.sum)
            sm.setAll(i, i, nums[i]);
    if (i >= Rmargin)
        return sm;
    Lmargin = i;
    sm.setAll(Lmargin, Lmargin, nums[Lmargin]);
    for (i = Rmargin; i >= Lmargin && nums[i] <= 0; i--)
        Rmargin = i;
    if (i == Lmargin)
        return sm;
    for (i = Lmargin; i <= Rmargin; i++) {
        sum += nums[i];
        if (sum > sm.sum)
            sm.setAll(Lmargin, i, sum);
        if (sum < 0) {
            cut = i;
            break;
        }
    }
    // for (i = sm.right, sum = 0; i >= Lmargin; i--) {
    //     sum += nums[i];
    //     if (sum > sm.sum)
    //         sm.setAll(i, sm.right, sum);
    // }
    if (cut >= 0) {
        SumMax sm2 = findSum(cut, Rmargin);
        if (sm.sum < sm2.sum)
            return sm2;
    }
    return sm;
}

int main() {
    int N, i;
    scanf("%d", &N);
    nums = (double *)malloc(sizeof(double) * N);
    for (i = 0; i < N; i++)
        scanf("%lf", &nums[i]);
    SumMax sm = findSum(0, N - 1);
    printf("sum:%.2f left:%d right:%d", sm.sum, sm.left, sm.right);
    free(nums);
    return 0;
}
