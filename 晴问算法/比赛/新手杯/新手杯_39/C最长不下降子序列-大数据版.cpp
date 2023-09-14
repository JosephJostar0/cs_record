#include <algorithm>
#include <iostream>
#include <vector>
#define MAXN 100000
int arr[MAXN], n, len;
std::vector<int> piles;
int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", arr + i);
        if (piles.empty() || arr[i] >= piles.back())
            piles.push_back(arr[i]);
        else {
            auto it = std::upper_bound(piles.begin(), piles.end(), arr[i]);
            *it = arr[i];
        }
    }
    printf("%d", piles.size());
    return 0;
}
