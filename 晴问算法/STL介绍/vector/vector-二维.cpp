#include <iostream>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cout.tie(NULL);
    int n;
    cin >> n;
    vector<vector<int>> vs(n, vector<int>());
    for (int i = 0; i < n; i++) {
        int j, t;
        cin >> j;
        while (j--) {
            cin >> t;
            vs[i].push_back(t);
        }
    }
    for (int i = 0; i < n; i++) {
        cout << vs[i][0];
        for (int j = 1; j < vs[i].size(); j++)
            cout << ' ' << vs[i][j];
        cout << endl;
    }
    return 0;
}
