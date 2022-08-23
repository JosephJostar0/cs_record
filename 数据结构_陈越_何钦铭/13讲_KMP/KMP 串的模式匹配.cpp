#include <iostream>
#include <string>
#define MAXN 1000000
int next[MAXN];
void getNext(std::string str) {
    int j = -1, len = str.size(), i;
    next[0] = -1;
    for (i = 1; i < len; i++) {
        while (j != -1 && str[i] != str[j + 1])
            j = next[j];
        if (str[i] == str[j + 1])
            j++;
        next[i] = j;
    }
}

void KMP(std::string text, std::string pat) {
    int j = -1, n = text.size(), m = pat.size(), i;
    getNext(pat);
    for (i = 0; i < n; i++) {
        while (j != -1 && text[i] != pat[j + 1])
            j = next[j];
        if (text[i] == pat[j + 1])
            j++;
        if (j == m - 1)
            break;
    }
    if (j == m - 1) {
        pat += text.substr(i + 1, n);
        std::cout << pat << std::endl;
    } else
        std::cout << "Not Found\n";
}

int main() {
    std::cin.tie(NULL);
    std::cout.tie(NULL);
    std::cout.sync_with_stdio(false);
    std::cin.sync_with_stdio(false);

    std::string str, pat;
    int N, i;
    std::cin >> str >> N;
    for (i = 0; i < N; i++) {
        std::cin >> pat;
        KMP(str, pat);
    }
    return 0;
}
