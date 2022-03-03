#include <iostream>
int  sum = 0, n;
void howMany(int step, int plus, int bracket) {
    if (plus > bracket)
        return;
    if (step == 2 * n) {
        if (plus == n)
            sum++;
        return;
    }
    if (plus < n)
        howMany(step + 1, plus + 1, bracket);
    howMany(step + 1, plus, bracket + 1);
}
int main() {
    std::cin >> n;
    howMany(0, 0, 0);
    printf("There are %d combinations", sum);
    return 0;
}
