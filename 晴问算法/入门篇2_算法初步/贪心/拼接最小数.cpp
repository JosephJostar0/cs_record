#include <algorithm>
#include <iostream>
#include <string>
bool cmp(std::string a, std::string b) { return a + b < b + a; }
int main() {
    std::string strs[10000], ans;
    int n, i;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
        std::cin >> strs[i];
    std::sort(strs, strs + n, cmp);
    for (i = 0; i < n; i++)
        ans += strs[i];
    while (ans[0] == '0' && ans.size() > 1)
        ans.erase(ans.begin());
    std::cout << ans;
    return 0;
}
