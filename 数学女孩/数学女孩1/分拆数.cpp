#include <iostream>
int  num = 0, pay;
void howMany(int coin, int residue) {
    int t = residue;
    if (residue == 0) {
        num++;
        return;
    }
    if (coin > residue)
        return;
    for (int i = 0; coin * i <= residue; i++) {
        t = residue - coin * i;
        howMany(coin + 1, t);
    }
}
int main() {
    std::cin >> pay;
    howMany(1, pay);
    printf("there are %d ways of pay\n", num);
    return 0;
}
