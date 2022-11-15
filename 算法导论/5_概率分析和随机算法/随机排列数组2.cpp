#include <ctime>
#include <iostream>
#define NUM 10
void randomize_in_place(int a[]) {
    for (int i = 0; i < NUM; i++)
        std::swap(a[i], a[i + rand() % (NUM - i)]);
}

int main() {
    srand((unsigned)time(NULL));

    int a[NUM];
    for (int i = 0; i < NUM; i++)
        a[i] = i;

    randomize_in_place(a);

    for (int i = 0; i < NUM; i++)
        printf("%d ", a[i]);

    return 0;
}
