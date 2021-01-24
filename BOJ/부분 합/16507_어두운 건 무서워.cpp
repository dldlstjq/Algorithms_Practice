/*
2차원 배열에서의 부분합을 이용해서 넓이를 나눠주면 된다.
1차원 배열과 달리 전체 합을 계산하는 psum을 잘 알고 있어야
문제를 풀 수 있다. 잘 기억해야 겠다.

*/

#include <iostream>
using namespace std;

int r, c, q;
int psum[1001][1001];

int partialSum(int r1, int c1, int r2, int c2) {
	int ret = psum[r2][c2];
	if (r1 > 0)ret -= psum[r1 - 1][c2];
	if (c1 > 0)ret -= psum[r2][c1 - 1];
	if (r1 > 0 && c1 > 0)ret += psum[r1 - 1][c1 - 1];
	return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> r >> c >> q;
	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j) {
			int num;
			cin >> num;
			psum[i + 1][j + 1] = psum[i][j + 1] + psum[i + 1][j] - psum[i][j] + num;
		}
	}

	//부분합을 구해서 넓이를 나눠준다.
	for (int i = 0; i < q; ++i) {
		int r1, c1, r2, c2;
		cin >> r1 >> c1 >> r2 >> c2;
		cout << partialSum(r1, c1, r2, c2) / ((r2 - r1 + 1) * (c2 - c1 + 1)) << "\n";
	}

	return 0;
}