#include <algorithm>
#include <iostream>
int n, origin[100], arr[100], copy[100], margin;

bool isInsert() {
    int before = arr[0], i;
    for (i = 1; i < n; before = arr[i], i++)
        if (arr[i] < before)
            break;
    std::sort(copy, copy + i);
    margin = i;
    for (i = 0; i < n; i++)
        if (arr[i] != copy[i])
            return false;
    if (margin < n)
        std::sort(copy, copy + margin + 1);
    return true;
}

bool isRight(int len) {
    for (int i = 0; i < n; i += len)
        std::sort(origin + i, origin + std::min(i + len, n));
    for (int i = 0; i < n; i++)
        if (origin[i] != arr[i])
            return false;
    return true;
}

void moreMerge() {
    int i, len = 2;
    while (!isRight(len))
        len *= 2;
    len *= 2;
    for (i = 0; i < n - 1; i += len)
        std::sort(arr + i, arr + std::min(i + len, n));
}

int main() {
    int i;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%d", copy + i), origin[i] = copy[i];
    for (i = 0; i < n; i++)
        scanf("%d", arr + i);
    if (isInsert()) {
        printf("Insertion Sort\n");
        printf("%d", copy[0]);
        for (i = 1; i < n; i++)
            printf(" %d", copy[i]);
    } else {
        printf("Merge Sort\n");
        moreMerge();
        printf("%d", arr[0]);
        for (i = 1; i < n; i++)
            printf(" %d", arr[i]);
    }
    return 0;
}
