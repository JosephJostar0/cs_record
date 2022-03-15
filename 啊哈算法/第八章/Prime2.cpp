#include <iostream>
#include <vector>
#define INF 0xBadBeef
int position[10], first[10], next[20], distance[10];
int start[20], end[20], weight[20], book[10];

class Heap {
public:
    std::vector<int> h;
    Heap() { h.push_back(0); };
    int pop();
    void siftDown(int i);
    void siftUp(int i);
    void swap(int a, int b);
} heap;

int Heap::pop() {
    h[0] = h[1];
    position[h[0]] = 0;
    h[1] = h[h.size() - 1];
    position[h[1]] = 1;
    h.pop_back();
    siftDown(1);
    return h[0];
}

void Heap::siftDown(int i) {
    int son = i * 2;
    while (son < h.size()) {
        if (son + 1 < h.size() && distance[h[son + 1]] < distance[h[son]])
            son++;
        if (distance[h[i]] > distance[h[son]]) {
            swap(i, son);
            i = son;
            son = i * 2;
        } else
            break;
    }
}

void Heap::siftUp(int i) {
    int dad = i / 2;
    while (dad) {
        if (distance[h[dad]] > distance[h[i]]) {
            swap(dad, i);
            i = dad;
            dad = i / 2;
        } else
            break;
    }
}

void Heap::swap(int a, int b) {
    int t = h[a];
    h[a] = h[b];
    h[b] = t;
    position[h[a]] = a;
    position[h[b]] = b;
}

int main() {
    int m, n;
    int cost = 0, node;
    int i, j;
    std::cin >> m >> n;
    for (i = 1; i <= m; i++)
        distance[i] = INF, heap.h.push_back(i), position[i] = i;
    distance[1] = 0;
    for (i = 1; i <= n; i++)
        std::cin >> start[i] >> end[i] >> weight[i];
    for (i = n + 1; i <= 2 * n; i++) {
        start[i] = end[i - n];
        end[i] = start[i - n];
        weight[i] = weight[i - n];
    }
    for (i = 1; i <= 2 * n; i++) {
        next[i] = first[start[i]];
        first[start[i]] = i;
    }
    for (i = first[1]; i != 0; i = next[i])
        distance[end[i]] = weight[i];
    for (i = heap.h.size() / 2; i > 0; i--)
        heap.siftDown(i);
    heap.pop();
    node = 1;
    book[1] = 1;
    while (node < m) {
        i = heap.pop();
        book[i] = 1;
        cost += distance[i];
        node++;
        for (j = first[i]; j != 0; j = next[j])
            if (book[end[j]] == 0 && distance[end[j]] > weight[j]) {
                distance[end[j]] = weight[j];
                heap.siftUp(position[end[j]]);
            }
    }
    std::cout << cost << std::endl;
    return 0;
}
