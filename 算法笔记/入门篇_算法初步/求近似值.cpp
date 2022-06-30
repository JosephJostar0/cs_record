#include <iostream>
const double eps = 1e-5;
double f(double x) { return x * x; }
// x^2-2=0
double calSqrt() {
    double left = 1, right = 2, mid;
    while (right - left > eps) {
        mid = (right + left) / 2;
        if (f(mid) > 2)
            right = mid;
        else
            left = mid;
    }
    return (left + right) / 2;
}
int main() {
    printf("%f\n", calSqrt());
    return 0;
}
