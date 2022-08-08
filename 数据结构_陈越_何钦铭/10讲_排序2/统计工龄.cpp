#include <iostream>
int cnt[51];
int main() {
    int N, i, year;
    scanf("%d", &N);
    for (i = 0; i < N; i++)
        scanf("%d", &year), cnt[year]++;
    for (i = 0; i <= 50; i++)
        if (cnt[i])
            printf("%d:%d\n", i, cnt[i]);
    return 0;
}
