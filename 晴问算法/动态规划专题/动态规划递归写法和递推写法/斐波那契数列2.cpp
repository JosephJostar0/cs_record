#include <iostream>
int memory[10001];
int F(int n) {
    if (memory[n])
        return memory[n];
    memory[n] = (F(n - 1) + F(n - 2)) % 10007;
    return memory[n];
}
int main() {
    memory[1] = memory[2] = 1;
    int n;
    scanf("%d", &n);
    printf("%d", F(n));
    return 0;
}
