#include <iostream>
int main() {
    int num;
    std::cin >> num;
    double sum = 1;
    for (double i = 2 * num, j = num; i > num; i--, j--)
        sum *= i / j;
    sum /= (num + 1);
    printf("There are %.0f combinations", sum);
    return 0;
}
