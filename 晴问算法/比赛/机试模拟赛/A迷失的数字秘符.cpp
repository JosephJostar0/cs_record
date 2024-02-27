#include <iostream>
#include <string>
using namespace std;
const int MAXD = 10;
int cnt[MAXD] = {0};
int main() {
    string s;
    cin >> s;
    for (int i = 0; i < s.length(); i++) {
        cnt[s[i] - '0']++;
    }
    if (cnt[0] != s.length() &&
        (cnt[0] >= 2 || (cnt[2] >= 1 && cnt[5] >= 1) || (cnt[5] >= 1 && cnt[0] >= 1) || (cnt[7] >= 1 && cnt[5] >= 1))) {
        printf("Yes");
    } else {
        printf("No");
    }
    return 0;
}