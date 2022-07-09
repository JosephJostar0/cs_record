#include <iostream>
void upAdjust(int heap[], int low, int high) {
    int dad = high / 2, son = high;
    while (dad >= low) {
        if (heap[dad] > heap[son])
            break;
        std::swap(heap[dad], heap[son]);
        son = dad;
        dad /= 2;
    }
}

int main() {
    int n, heap[1003], i;
    scanf("%d", &n);
    scanf("%d", heap + 1);
    for (i = 2; i <= n; i++) {
        scanf("%d", heap + i);
        upAdjust(heap, 1, i);
    }
    printf("%d", heap[1]);
    for (i = 2; i <= n; i++)
        printf(" %d", heap[i]);
    return 0;
}
