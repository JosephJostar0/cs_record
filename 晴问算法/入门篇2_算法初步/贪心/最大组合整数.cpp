#include <iostream>
#include <string>
int main() {
    int num[10] = {0}, i;
    std::string ans;
    for (i = 0; i < 10; i++)
        scanf("%d", num + i);
    for (i = 9; i >= 0; i--)
        while (num[i]--)
            ans.push_back((char)('0' + i));
    while (ans.front() == '0' && ans.size() > 1)
        ans.erase(ans.begin());
    printf("%s", ans.c_str());
    return 0;
}
