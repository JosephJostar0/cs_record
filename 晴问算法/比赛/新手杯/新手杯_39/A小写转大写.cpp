#include <iostream>
int main() {
    char c;
    scanf("%c", &c);
    printf("%c", char(c + 'A' - 'a'));
    return 0;
}
