#include <algorithm>
#include <iostream>
int main() {
    int W, box[100000], n, i, maxW;
    scanf("%d%d", &n, &W);
    for (i = 0; i < n; i++)
        scanf("%d", box + i);
    std::sort(box, box + n);
    for (i = 0, maxW = W; box[i] <= W && i < n; i++)
        W -= box[i];
    printf("%d %d", i, maxW - W);
    return 0;
}
