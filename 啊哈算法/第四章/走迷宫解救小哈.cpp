#include<iostream>
using namespace std;
					// 向右走  下     左     上
int nextStep[4][2] = { {0,1},{1,0},{0,-1},{-1,0} };//方便走下一步
int mini = 0x3f3f3f3f;//记录最小的步数
int m, n;//m行n列的迷宫
int a[51][51];//记录地图的信息
int book[51][51];//记录哪些点走过了，且全局变量自动初始化为0
int p, q;//出口的坐标

void dfs(int x, int y, int step) {
	if (x == p && y == q) {
		if (step < mini)
			mini = step;
		return;
	}
	int k;
	int nx, ny;
	for (k = 0; k < 4; k++) {
		nx = x + nextStep[k][0];
		ny = y + nextStep[k][1];
		if (nx<1 || nx>m || ny<1 || ny>n)
			continue;
		if (a[nx][ny] == 1 || book[nx][ny] == 1)
			continue;
		book[nx][ny] = 1;
		dfs(nx, ny, step + 1);
		book[nx][ny] = 0;
	}
}

int main() {
	int x, y;//入口坐标
	cout << "请依次输入这个迷宫的行和列：";
	cin >> m >> n;
	cout << "请输入这个迷宫的结构，其中0表示空地，1表示障碍物\n";
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++)
			cin >> a[i][j];
	cout << "请输入迷宫入口的坐标(从1,1开始):";
	cin >> x >> y;
	cout << "请输入迷宫出口的坐标:";
	cin >> p >> q;
	
	book[x][y] = 1;
	dfs(x, y, 0);

	cout << "\n所需的最短步数为: " << mini << " 步\n";
	return 0;
}
