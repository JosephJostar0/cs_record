#include <iostream>
int main() {
    long long x;
    scanf("%lld", &x);
    if (x % 2)
        x *= 2;
    if (x % 3)
        x *= 3;
    printf("%lld", x);
    return 0;
}
