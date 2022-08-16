#include <iostream>
int table[10007], Msize, N;
bool isPrime(int x) {
    for (int i = 2; i * i <= x; i++)
        if (x % i == 0)
            return false;
    return x > 1;
}

void isHash(int t) {
    t %= Msize;
    int i = 1, temp = t;
    while (i < Msize && table[temp])
        temp = t + i * i, i++, temp %= Msize;
    if (i >= Msize)
        printf(" -");
    else
        table[temp] = 1, printf(" %d", temp);
}

int main() {
    int i, t;
    scanf("%d%d", &Msize, &N);
    while (!isPrime(Msize))
        Msize++;
    scanf("%d", &t);
    table[t % Msize] = 1, printf("%d", t % Msize);
    for (i = 1; i < N; i++) {
        scanf("%d", &t);
        isHash(t);
    }
    return 0;
}
