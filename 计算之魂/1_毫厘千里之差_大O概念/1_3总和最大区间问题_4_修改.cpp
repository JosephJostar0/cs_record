#include <iostream>
int main() {
    int N, i, left, right, marginL = 0, marginR = 0;
    double current_sum, sum, next;
    scanf("%d", &N);
    scanf("%lf", &sum);
    left = 0, right = 0, marginL = 0, marginR = 0, current_sum = sum;
    for (i = 1; i < N; i++) {
        scanf("%lf", &next);
        current_sum += next;
        if (current_sum < 0) {
            if (current_sum > sum)
                sum = current_sum, marginL = left, marginR = i;
            left = i + 1, current_sum = 0;
            continue;
        }
        right = i;
        if (current_sum > sum)
            sum = current_sum, marginR = right, marginL = left;
    }
    printf("sum:%.2f left:%d right:%d", sum, marginL, marginR);
    return 0;
}
