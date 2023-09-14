#include <iostream>
const int two[] = {2, 4, 8, 6}, three[] = {3, 9, 7, 1};
int main() {
    int x, y;
    scanf("%d%d", &x, &y);
    x = x == 0 ? 1 : two[(x - 1) % 4];
    y = y == 0 ? 1 : three[(y - 1) % 4];
    printf("%d", (x * y) % 10);
    return 0;
}
