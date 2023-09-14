#include <iostream>
void downAdjust(int heap[], int low, int high) {
    int dad = low, son = 2 * low;
    while (son <= high) {
        if (son + 1 <= high && heap[son] <= heap[son + 1])
            son++;
        if (heap[dad] >= heap[son])
            return;
        std::swap(heap[dad], heap[son]);
        dad = son;
        son = dad * 2;
    }
}

void createHeap(int heap[], int low, int high) {
    for (int i = high / 2; i >= low; i--)
        downAdjust(heap, i, high);
}

int main() {
    int n, heap[1003], i;
    scanf("%d", &n);
    for (i = 1; i <= n; i++)
        scanf("%d", heap + i);
    createHeap(heap, 1, n);
    printf("%d", heap[1]);
    for (i = 2; i <= n; i++)
        printf(" %d", heap[i]);
    return 0;
}
