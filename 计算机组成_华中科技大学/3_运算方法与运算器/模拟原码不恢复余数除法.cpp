#include <iostream>
int getSignFlag(unsigned int a, unsigned int b) {
    int sa = (a >> 31), sb = (b >> 31);
    return (sa ^ sb);
}

void outHex(int t) {
    if (t < 0)
        printf("1."), t *= -1;
    else
        printf("0.");
    printf("%08x", t);
}

void outResult(int t, int SF = 0) {
    if (SF)
        printf("1.%08x", t);
    else
        printf("0.%08x", t);
}

void myDiv(int a, int b) {
    int SF = getSignFlag(a, b);
    int x = std::abs(a), y = std::abs(b);
    if (x > y)
        std::swap(x, y), std::swap(a, b);
    int quotient = 0;

    for (int i = 0, next = -1; i <= 32; i++) {
        x += next * y;
        if (x > 0)
            next = -1, quotient += 1;
        else if (x < 0)
            next = 1;
        else {
            quotient += 1;
            while (i < 32)
                quotient <<= 1, i++;
            break;
        }
        if (i != 32)
            x <<= 1, quotient <<= 1;
    }
    while (x < 0)
        x += y;

    outHex(a), printf(" / "), outHex(b), printf(" = ");
    outResult(quotient, SF), printf("...");
    outResult(x), printf("*2^-32");
}

int main() {
    int x, y;
    printf("please enter x and y both of which should be integer, separated by a space:\n");
    scanf("%d%d", &x, &y);
    if (x == 0x80000000 || y == 0x80000000 || (std::abs(x) == std::abs(y))) {
        printf("x or y out of range!");
        return 0;
    }
    myDiv(x, y);
    return 0;
}
