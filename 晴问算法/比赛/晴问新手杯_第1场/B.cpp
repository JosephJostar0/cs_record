#include <iostream>
int main() {
    long long A, B;
    char c;
    scanf("%lld%c%lld", &A, &c, &B);
    switch (c) {
    case '+':
        printf("%lld", A + B);
        break;
    case '-':
        printf("%lld", A - B);
        break;
    default:
        break;
    }
    return 0;
}
