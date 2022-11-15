#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#define NUM 10
int p[NUM];
bool cmp(int a, int b) {
    if (p[a] != p[b])
        return p[a] < p[b];
    return a < b;
}

void permute_by_sorting(int a[]) {
    int top = (int)pow(NUM, 3);
    for (int i = 0; i < NUM; i++)
        p[i] = 1 + rand() % top;
    std::sort(a, a + NUM, cmp);
}

int main() {
    srand((unsigned)time(NULL));

    int a[NUM];
    for (int i = 0; i < NUM; i++)
        a[i] = i;

    permute_by_sorting(a);

    for (int i = 0; i < NUM; i++)
        printf("%d ", a[i]);

    return 0;
}
