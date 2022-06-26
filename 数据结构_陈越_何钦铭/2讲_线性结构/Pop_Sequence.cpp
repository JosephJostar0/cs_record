#include <iostream>
int main() {
    int M, N, K, a[1001], i, j, t, size;
    bool flag = true;
    scanf("%d%d%d", &M, &N, &K);
    for (j = 0; j < K; j++) {
        for (i = 0; i < N; i++)
            scanf("%d", a + i);
        flag = true;
        for (i = 0; flag && i < N; i++, size = 0)
            for (t = i + 1; flag && t < N; t++) {
                if (a[t] < a[i]) {
                    if (a[t - 1] < a[i])
                        if (a[t] > a[t - 1])
                            flag = false;
                    size++;
                }
                if (size == M)
                    flag = false;
            }
        if (flag)
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}
