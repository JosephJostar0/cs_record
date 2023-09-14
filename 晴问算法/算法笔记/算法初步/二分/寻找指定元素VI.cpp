#include <iostream>
int a[100001], n;
int binarySearch(int target) {
    int left = 0, right = n - 1, mid = (right - left) / 2 + left;
    while (left <= right) {
        if (a[mid] == target)
            return mid;
        else if (a[mid] > target)
            right = mid - 1;
        else
            left = mid + 1;
        mid = (right - left) / 2 + left;
    }
    return -1;
}

int main() {
    int target, i;
    scanf("%d%d", &n, &target);
    for (i = 0; i < n; i++)
        scanf("%d", a + i);
    i = binarySearch(target);
    while (a[i + 1] == target)
        i++;
    printf("%d", i);
    return 0;
}
