/*
게임판의 왼쪽 위 칸에서 시작해서 게임판의 맨 오른쪽 아래 칸에 도착할 수 있는지를 판별하는 프로그램
칸에 적혀 있는 숫자만큼 오른쪽 혹은 밑으로 내려갈 수 있습니다.

완전탐색을 이용하면 경로 개수가 n에 따라 지수적으로 늘어나기 때문에
n=100이면 시간초과가 난다.

동적 게획법의 메모이제이션을 적용해야 한다.
*/

#include <iostream>
#include <cstring>

using namespace std;

int n, board[100][100];
int cache[100][100];

int jump(int y, int x) {
	//기저 사례: 게임판 밖을 벗어나는 경우
	if (y >= n || x >= n)
		return 0;
	//기저 사례: 마지막 칸에 도착하는 경우
	if (y == n - 1 && x == n - 1)
		return 1;
	//메모이제이션
	int& ret = cache[y][x];
	if (ret != -1)
		return ret;
	int jumpSize = board[y][x];
	return ret = (jump(y + jumpSize, x) || jump(y, x + jumpSize));
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;
	while (t--) {
		cin >> n;
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				cin >> board[i][j];

		memset(cache, -1, sizeof(cache));

		if (jump(0, 0) == 1)
			cout << "YES" << "\n";
		else
			cout << "NO" << "\n";
	}
	return 0;
}