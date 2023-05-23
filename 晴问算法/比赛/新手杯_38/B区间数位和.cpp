#include <iostream>
int main() {
    int a, b, sum = 0, c;
    scanf("%d%d", &a, &b);
    for (int i = a; i <= b; i++)
        for (int k = i; k > 0; k /= 10)
            sum += k % 10;
    printf("%d", sum);
    return 0;
}
