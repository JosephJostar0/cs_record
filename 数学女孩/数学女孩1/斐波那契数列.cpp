#include <iostream>
int Fibonacci(int n) {
    if (n == 1 || n == 2)
        return 1;
    return Fibonacci(n - 1) + Fibonacci(n - 2);
}
int main() {
    int n, k;
    std::cin >> n;
    k = Fibonacci(n);
    printf("The %dth(st,nd,rd) term in the sequence is %d", n, k);
    return 0;
}
