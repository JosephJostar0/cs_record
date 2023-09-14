#include <iostream>
#define MAXN 100001
long long arr[MAXN], bottom, top, sum;
int main() {
    int N;
    scanf("%d", &N);
    scanf("%lld", arr);
    bottom = arr[0], top = arr[0];
    for (int i = 1; i < N; i++) {
        scanf("%lld", arr + i);
        if (arr[i] < bottom)
            bottom = arr[i];
        if (arr[i] > top)
            top = arr[i];
    }
    for (int i = 0; i < N; i++)
        if (arr[i] != top && arr[i] != bottom)
            sum += arr[i];
    printf("%lld", sum, top, bottom);
    return 0;
}
