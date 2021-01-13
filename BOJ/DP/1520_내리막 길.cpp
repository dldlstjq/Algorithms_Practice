/*
정답률이 낮아보여 어려울 것 같았는데 생각보다 쉬웠다.
(0,0)부터 시작해서 (m-1,n-1)에 도달하면 1을 리턴해서 해당 칸의
숫자와 더해주는 식으로 구현했다.

종만북을 보기 전 이 문제를 접했다면 무작정 dfs돌렸다가
시간초과나서 못풀었을 확률이 120%였을 것 같다.
그래도 공부했다는 티가 나는 것 같아 조금은 뿌듯했다.
*/

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int m, n;
int map[501][501];
int cache[501][501];
int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };

int solve(int y, int x) {
	//기저 사례: 지도 맨 밑에 도착하면 ok
	if (y == m - 1 && x == n - 1)
		return 1;
	int& ret = cache[y][x];
	if (ret != -1)return ret;
	ret = 0;

	for (int i = 0; i < 4; ++i) {
		int nextY = y + dy[i];
		int nextX = x + dx[i];
		//이동할 좌표가 범위 안에 들어오고
		if (0 <= nextY && nextY < m &&
			0 <= nextX && nextX < n) {
			//현재 좌표(y,x)보다 크기가 작으면 이동한다.
			if (map[y][x] > map[nextY][nextX]) {
				ret += solve(nextY, nextX);
			}
		}
	}
	return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	memset(cache, -1, sizeof(cache));
	cin >> m >> n;
	for (int i = 0; i < m; ++i)
		for (int j = 0; j < n; ++j)
			cin >> map[i][j];

	cout << solve(0, 0);

	return 0;
}