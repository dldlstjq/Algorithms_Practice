/*
조합 게임에서의 동적 계획법 풀이이다.
DP가 정말 다양하게 활용되고 있다는 사실을 보면서 알게된다.
DP를 많이 풀어봐야겠다.
*/

#include <iostream>
#include <algorithm>

using namespace std;

const int EMPTY = -987654321;
int n, board[50];
int cache[50][50];
int play(int left, int right) {
	//기저 사례: 모든 수가 다 없어졌을 때
	if (left > right)
		return 0;
	int& ret = cache[left][right];
	if (ret != EMPTY)
		return ret;
	//수를 가져가는 경우
	ret = max(board[left] - play(left + 1, right),
		board[right] - play(left, right - 1));
	//수를 없애는 경우
	if (right - left + 1 >= 2) {
		ret = max(ret, -play(left + 2, right));	//왼쪽 두개 지우는 경우
		ret = max(ret, -play(left, right - 2));	//오른쪽 두개 지우는 경우
	}
	return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int c;
	cin >> c;
	while (c--) {
		for (int i = 0; i < 50; i++)
			for (int j = 0; j < 50; j++)
				cache[i][j] = EMPTY;

		cin >> n;
		for (int i = 0; i < n; ++i)
			cin >> board[i];

		cout << play(0, n - 1) << "\n";
	}

	return 0;
}