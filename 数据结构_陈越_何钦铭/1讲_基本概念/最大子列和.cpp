#include <iostream>
int main() {
    int N, i, left, right, marginL = 0, marginR = 0;
    int current_sum, sum, num[100001];
    scanf("%d", &N);
    for (i = 0; i < N; i++)
        scanf("%d", num + i);
    left = num[0] > 0 ? 0 : 1, right = 0, marginL = 0, marginR = 0, current_sum = num[0] > 0 ? num[0] : 0, sum = num[0];
    for (i = 1; i < N; i++) {
        current_sum += num[i];
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
    if (sum >= 0)
        printf("%d %d %d", sum, num[marginL], num[marginR]);
    else
        printf("%d %d %d", 0, num[0], num[N - 1]);
    return 0;
}
