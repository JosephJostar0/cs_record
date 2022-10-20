#include <iostream>
#include <vector>
class Martix {
public:
    std::vector<std::vector<int>> v;
    Martix() {}
    Martix(int n, int m) {
        v.resize(n);
        for (int i = 0; i < n; i++)
            v[i].resize(m, 0);
    }
    void resize(int n, int m) {
        v.resize(n);
        for (int i = 0; i < n; i++)
            v[i].resize(m, 0);
    }
};

Martix multi(Martix A, Martix B) {
    Martix C(A.v.size(), B.v[0].size());
    if (A.v[0].size() != B.v.size())
        return C;
    for (int i = 0; i < A.v.size(); i++)
        for (int j = 0; j < B.v[0].size(); j++)
            for (int k = 0; k < B.v.size(); k++)
                C.v[i][j] += A.v[i][k] * B.v[k][j];
    return C;
}

int main() {
    Martix A(2, 2), B(2, 1), C;
    A.v[0][0] = 1, A.v[0][1] = 2, A.v[1][0] = 3, A.v[1][1] = 4;
    B.v[0][0] = 1, B.v[1][0] = 2;
    C = multi(A, B);
    for (int i = 0; i < C.v.size(); i++) {
        for (int j = 0; j < C.v[0].size(); j++)
            printf("%d ", C.v[i][j]);
        printf("\n");
    }
    return 0;
}
