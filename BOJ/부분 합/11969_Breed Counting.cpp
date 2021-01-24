/*
1차원 배열에 소를 집어넣고 a~b까지 하나씩 세면 시간초과가 난다.
소를 입력 받을 때 1,2,3번 소를 하나씩 체크해서 구간 합을 구해야
정답을 받을 수 있다.
1,2,3번을 구간합으로 어떻게 받아야 할 지 잠깐 헷갈렸는데
2차원 배열로 구현하면 됐다.
*/

#include <iostream>

using namespace std;

const int MAX = 100000 + 1;
int cow[4][MAX];
int n, q;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> q;
	for (int i = 1; i <= n; ++i) {
		int num;
		cin >> num;

		cow[num][i]++;	//해당하는 번호의 소 증가
		//구간 합 계산
		cow[1][i] += cow[1][i - 1];
		cow[2][i] += cow[2][i - 1];
		cow[3][i] += cow[3][i - 1];
	}

	for (int i = 0; i < q; ++i) {
		int a, b;
		cin >> a >> b;
		cout << cow[1][b] - cow[1][a - 1] << ' ';
		cout << cow[2][b] - cow[2][a - 1] << ' ';
		cout << cow[3][b] - cow[3][a - 1] << "\n";
	}
	return 0;
}