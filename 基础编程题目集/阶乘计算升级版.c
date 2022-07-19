#include <stdio.h>
/**
 * @brief 自定义bigInt类型
 * 其中，len表示bigInt有多少位
 * data按从低位到高位的顺序存储大整数
 */
struct BigInteger {
    int data[3000];
    int len;
};
typedef struct BigInteger bigInt;

/**
 * @brief Get the BigInt object
 * 利用这个函数把int类型转变成bigInt类型
 * @param num int类型
 * @return bigInt
 */
bigInt getBigInt(int num) {
    bigInt big;
    big.len = 0;
    do {
        big.data[big.len++] = num % 10;
        num /= 10;
    } while (num);
    return big;
}

/**
 * @brief Multiply bigInt by int
 * 利用这个函数做bigInt与int的乘法
 * @param big bigInt类型
 * @param a int类型
 * @return bigInt
 */
bigInt bigMul(bigInt big, int a) {
    int plus = 0, i;
    for (i = 0; i < big.len; i++) {
        big.data[i] *= a;
        big.data[i] += plus;
        plus = big.data[i] / 10;
        big.data[i] %= 10;
    }
    while (plus) {
        big.data[big.len++] = plus % 10;
        plus /= 10;
    }
    return big;
}

void Print_Factorial(const int N) {
    if (N < 0) {
        printf("Invalid input");
        return;
    }
    bigInt big = getBigInt(1);
    int i;
    for (i = N; i; i--)
        big = bigMul(big, i);
    for (i = big.len - 1; i >= 0; i--)
        printf("%d", big.data[i]);
}

int main() {
    int N;
    scanf("%d", &N);
    Print_Factorial(N);
    return 0;
}