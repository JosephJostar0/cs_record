#include <algorithm>
#include <iostream>
int arr[100000];
int main() {
    int N, i, temp, last = 1, ans = 0;
    scanf("%d", &N);
    for (i = 0; i < N; i++)
        scanf("%d", &temp), arr[temp] = i;
    while (true) {
        if (arr[0] != 0)
            std::swap(arr[0], arr[arr[0]]);
        else {
            while (last < N && arr[last] == last)
                last++;
            if (last == N)
                break;
            std::swap(arr[0], arr[last]);
        }
        ans++;
    }
    printf("%d", ans);
    return 0;
}
