#include <iostream>
int memory[10001];
int main() {
    memory[1] = memory[2] = 1;
    int n;
    scanf("%d", &n);
    for (int i = 3; i <= n; i++)
        memory[i] = (memory[i - 1] + memory[i - 2]) % 10007;
    printf("%d", memory[n]);
    return 0;
}
