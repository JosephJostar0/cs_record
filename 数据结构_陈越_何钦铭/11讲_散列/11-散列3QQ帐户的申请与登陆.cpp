#include <iostream>
#include <string>
#include <unordered_map>
typedef long long LL;
int main() {
    int N, i;
    char how, pwd[16];
    LL num;
    std::string str;
    std::unordered_map<LL, std::string> map;
    scanf("%d\n", &N);
    for (i = 0; i < N; i++) {
        scanf("%c %lld %s\n", &how, &num, pwd);
        str = pwd;
        if (how == 'L') {
            if (map.find(num) == map.end())
                printf("ERROR: Not Exist\n");
            else if (map[num] == str)
                printf("Login: OK\n");
            else
                printf("ERROR: Wrong PW\n");
        } else {
            if (map.find(num) == map.end())
                printf("New: OK\n"), map[num] = str;
            else
                printf("ERROR: Exist\n");
        }
    }
    return 0;
}
