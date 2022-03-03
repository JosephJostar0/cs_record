#include <iostream>
int howMany(int num) {
    if (num <= 1)
        return 1;
    int sum = 0;
    for (int i = 1; i <= num; i++)
        sum += howMany(i - 1) * howMany(num - i);
    return sum;
}
int main() {
    int num, sum;
    std::cin >> num;
    sum = howMany(num);
    printf("There are %d combinations", sum);
    return 0;
}
