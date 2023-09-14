#include <cstring>
#include <iostream>
void upAdjustMax(int heap[], int high) {
    int dad = high / 2, son = high;
    while (dad >= 1) {
        if (heap[dad] >= heap[son])
            break;
        std::swap(heap[dad], heap[son]);
        son = dad;
        dad /= 2;
    }
}

void downAdjustMax(int heap[], int low, int high) {
    int dad = low, son = 2 * low;
    while (son <= high) {
        if (son + 1 <= high && heap[son] < heap[son + 1])
            son++;
        if (heap[dad] >= heap[son])
            return;
        std::swap(heap[dad], heap[son]);
        dad = son;
        son = dad * 2;
    }
}

void upAdjustMin(int heap[], int high) {
    int dad = high / 2, son = high;
    while (dad >= 1) {
        if (heap[dad] <= heap[son])
            break;
        std::swap(heap[dad], heap[son]);
        son = dad;
        dad /= 2;
    }
}

void downAdjustMin(int heap[], int low, int high) {
    int dad = low, son = 2 * low;
    while (son <= high) {
        if (son + 1 <= high && heap[son] > heap[son + 1])
            son++;
        if (heap[dad] <= heap[son])
            return;
        std::swap(heap[dad], heap[son]);
        dad = son;
        son = dad * 2;
    }
}

int main() {
    int n, heap[2][10001] = {0}, i, data, high[2] = {0}, sum = 0;
    double mid = 0;
    char line[32];
    bool flag;
    scanf("%d\n", &n);
    for (i = 0; i < n; i++) {
        std::cin.getline(line, 32);
        flag = strcmp(line, "Print") == 0;
        if (flag)
            printf("%.1f\n", mid);
        else {
            sscanf(line, "Push %d", &data);
            if (data <= mid) {
                heap[0][++high[0]] = data;
                upAdjustMax(heap[0], high[0]);
            } else {
                heap[1][++high[1]] = data;
                upAdjustMin(heap[1], high[1]);
            }
            if (high[0] - high[1] > 1) {
                heap[1][++high[1]] = heap[0][1];
                upAdjustMin(heap[1], high[1]);
                heap[0][1] = heap[0][high[0]--];
                downAdjustMax(heap[0], 1, high[0]);
            } else if (high[1] - high[0] > 1) {
                heap[0][++high[0]] = heap[1][1];
                upAdjustMax(heap[0], high[0]);
                heap[1][1] = heap[1][high[1]--];
                downAdjustMin(heap[1], 1, high[1]);
            }
            sum++;
            if (sum & 1)
                mid = (double)(high[0] > high[1] ? heap[0][1] : heap[1][1]);
            else
                mid = ((double)(heap[0][1] + heap[1][1])) / 2;
        }
    }
    return 0;
}
