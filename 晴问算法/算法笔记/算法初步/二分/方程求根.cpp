#include <iostream>
const double eps = 1e-3;
double f(double x) { return x * (x * (x + 1) + 1); }
int main() {
    double left = -10, right = 10, mid, a;
    scanf("%lf", &a);
    while (right - left > eps) {
        mid = (right + left) / 2;
        if (f(mid) > a)
            right = mid;
        else
            left = mid;
    }
    printf("%.2f", (left + right) / 2);
    return 0;
}
