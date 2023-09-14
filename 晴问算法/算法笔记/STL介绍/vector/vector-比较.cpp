#include <iostream>
#include <vector>
using namespace std;
vector<int> v[2];
void input(int t, int n) {
    for (int i = 0, p; i < n; i++) {
        cin >> p;
        v[t].push_back(p);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cout.tie(NULL);
    int n[2];
    cin >> n[0] >> n[1];
    input(0, n[0]), input(1, n[1]);
    if (v[0] < v[1])
        printf("Yes\n");
    else
        printf("No\n");
    return 0;
}
