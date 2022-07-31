#include <algorithm>
#include <iostream>
int main() {
    int n, arr[100000], i;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%d", arr + i);
    std::sort(arr, arr + n);
    printf("%d", arr[0]);
    for (i = 1; i < n; i++)
        printf(" %d", arr[i]);
    return 0;
}
