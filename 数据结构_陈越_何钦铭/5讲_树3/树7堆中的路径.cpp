#include <iostream>
int heap[10001], high = 1;
void upAdjust() {
    int son = (high - 1) / 2, dad = high - 1;
    while (son) {
        if (heap[son] < heap[dad])
            break;
        std::swap(heap[son], heap[dad]);
        dad = son;
        son /= 2;
    }
}

void push(int value) {
    heap[high++] = value;
    upAdjust();
}

void output(int id) {
    printf("%d", heap[id]);
    for (int i = id >> 1; i; i >>= 1)
        printf(" %d", heap[i]);
}

int main() {
    int N, M, i, index;
    scanf("%d %d\n", &N, &M);
    for (i = 0; i < N; i++) {
        scanf("%d", &index);
        push(index);
    }
    for (i = 0; i < M; i++) {
        scanf("%d", &index);
        output(index);
        printf("\n");
    }
    return 0;
}
