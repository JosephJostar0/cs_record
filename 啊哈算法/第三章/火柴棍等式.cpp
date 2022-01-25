#include<iostream>
#include<map>
using namespace std;

int need(int x) {//return 拼出x所需要的火柴数量
	map<int, int> match = {//匹配每个数字所需要的火柴数量
		{0,6},{1,2},{2,5},{3,5},{4,4},
		{5,5},{6,6},{7,3},{8,7},{9,6}
	};
	int n = 0;
	while (x / 10 != 0) {
		n += match[x % 10];
		x /= 10;
	}
	n += match[x];
	return n;
}

int main() {
	int num;//记录火柴的总数
	int a, b, c;//a+b=c
	int sum = 0;//记录可以拼出几个a+b=c
	int big = 0;//记录a,b,c中任意一个数能取到的最大值
	cout << "请输入火柴的总数：";
	cin >> num;
	num -= 4;//减去+和=用去的四个火柴
	for (int i = num / 6 + (num % 6 ? 1 : 0); i > 0; i--)
		big = big * 10 + 1;//计算在当前火柴下能拼出的最大数 的一个上界
	for (a = 0; a <= big; a++)
		for (b = 0; b <= big; b++) {
			c = a + b;
			if (need(a) + need(b) + need(c) == num) {
				cout << a << '+' << b << '=' << c << endl;
				sum++;
			}
		}
	cout << "总计" << sum << "个等式\n";
	return 0;
}
