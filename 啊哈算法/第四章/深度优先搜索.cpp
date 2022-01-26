#include<iostream>
#include<vector>
#include<map>
using namespace std;
map<int, int> m;
vector<int> v;
int N;

void dfs(int step) {
	int i, j, k;
	if (step == N) {
		for (i = 0; i < N; i++)
			cout << v[i];
		cout << endl;
		return;
	}
	for (i = 1; i <= N; i++) {
		if (m[i] == 0) {
			m[i] = 1;
			v.push_back(i);
			dfs(step + 1);
			m[i] = 0;
			v.pop_back();
		}
	}
}

int main() {
	cout << "请输入本次排列的最大数:";
	cin >> N;
	dfs(0);
	return 0;
}
