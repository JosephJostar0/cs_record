#include <iostream>
int K;
int stepOn(int n) {
    if (n <= 1)
        return n == 1 ? 1 : 0;
    int i, sum = 0;
    for (i = 1; i <= K; i++)
        sum += stepOn(n - i);
    return sum;
}

int main() {
    int N;
    scanf("%d%d", &N, &K);
    printf("sum:%d", stepOn(N));
    return 0;
}
