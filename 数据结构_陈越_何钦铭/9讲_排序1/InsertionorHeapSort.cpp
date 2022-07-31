#include <algorithm>
#include <iostream>
int n, origin[100], arr[100], copy[100];

bool isInsert() {
    int before = arr[0], i, margin;
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

void downAdjust(int margin) {
    int dad = 0, son = dad * 2 + 1;
    while (son < margin) {
        if (son + 1 < margin && arr[son] < arr[son + 1])
            son++;
        if (arr[dad] >= arr[son])
            break;
        std::swap(arr[dad], arr[son]);
        dad = son;
        son = son * 2 + 1;
    }
}

void moreHeap() {
    int margin, i;
    for (i = n - 1; i >= 0; i--)
        if (arr[i] < arr[0])
            break;
    margin = i;
    std::swap(arr[0], arr[margin]);
    downAdjust(margin);
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
        printf("Heap Sort\n");
        moreHeap();
        printf("%d", arr[0]);
        for (i = 1; i < n; i++)
            printf(" %d", arr[i]);
    }
    return 0;
}
