#include <cstring>
#include <iostream>
void downAdjust(int heap[], int low, int high) {
    int dad = low, son = 2 * low;
    while (son <= high) {
        if (son + 1 <= high && heap[son] > heap[son + 1])
            son++;
        if (heap[dad] < heap[son])
            return;
        std::swap(heap[dad], heap[son]);
        dad = son;
        son = dad * 2;
    }
}

void upAdjust(int heap[], int high) {
    int dad = high / 2, son = high;
    while (dad >= 1) {
        if (heap[dad] <= heap[son])
            break;
        std::swap(heap[dad], heap[son]);
        son = dad;
        dad /= 2;
    }
}

int main() {
    int n, heap[101], i, k, data, high = 0;
    char line[32];
    bool flag;
    scanf("%d %d\n", &n, &k);
    for (i = 0; i < n; i++) {
        std::cin.getline(line, 32);
        flag = strcmp(line, "Print") == 0;
        if (high < k) {
            if (flag)
                printf("-1\n");
            else {
                sscanf(line, "Push %d", &data);
                heap[++high] = data;
                upAdjust(heap, high);
            }
        } else {
            if (flag)
                printf("%d\n", heap[1]);
            else {
                sscanf(line, "Push %d", &data);
                if (data > heap[1])
                    heap[1] = data;
                downAdjust(heap, 1, high);
            }
        }
    }
    return 0;
}
