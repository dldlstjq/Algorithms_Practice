/*
미로찾기 문제는 BFS로 해결할 수 있어 BFS로 접근했다.
열쇠 여부를 6비트로 표현해 열쇠가 있으면 1로 두고 없으면 0으로 표시한다.
문제는 열쇠를 얻지 못하는 경로로 가서 문에 접근하면 갈 수 없어야 하는데
다른 경로에서 획득한 열쇠의 정보가 그대로 반영되어 문에 갈 수 있게 되면서
정확한 답이 나오지 않았다.

이걸 해결할 수 없어 풀지 못했는데 visited라는 잊고 있었던 변수를 사용해서
열쇠를 얻었는지 못 얻었는지 표시했다.
단순히 모든 미로를 탐색해야 한다고 생각해서 visited를 간과하고 있었는데
조금만 더 생각해보면 풀 수 있지 않았을까 생각했다.
*/

#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

const int MAX = 50;
int n, m;
int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };
char maze[MAX][MAX];
bool visited[1 << 6][MAX][MAX]; //key, y, x

int solve(int y, int x) {
	//(y,x) (move, key)로 표현
	queue<pair<pair<int, int>, pair<int, int>>> q;
	q.push({ { y,x }, {0,0} });
	visited[0][y][x] = true;
	while (!q.empty()) {
		int nowY = q.front().first.first;
		int nowX = q.front().first.second;
		int move = q.front().second.first;
		int key = q.front().second.second;
		q.pop();

		//출구
		if (maze[nowY][nowX] == '1')
			return move;

		for (int i = 0; i < 4; ++i) {
			int nextY = nowY + dy[i];
			int nextX = nowX + dx[i];

			//미로 범위 안에 있고 방문하지 않았으면서 벽이 아닌 경우
			if (0 <= nextY && nextY < n && 0 <= nextX && nextX < m
				&& !visited[key][nextY][nextX] && maze[nextY][nextX] != '#') {
				//., 0, 1이면 갈 수 있다
				if (maze[nextY][nextX] == '.' || maze[nextY][nextX] == '0' || maze[nextY][nextX] == '1') {
					visited[key][nextY][nextX] = true;
					q.push({ {nextY, nextX}, {move + 1, key } });
				}
				//열쇠를 잡고 이동한다.
				else if ('a' <= maze[nextY][nextX] && maze[nextY][nextX] <= 'f') {
					int new_key = key | (1 << (maze[nextY][nextX] - 'a'));
					if (!visited[new_key][nextY][nextX]) {
						visited[key][nextY][nextX] = true;
						visited[new_key][nextY][nextX] = true;
						q.push({ { nextY,nextX, }, {move + 1,new_key } });
					}

				}
				//대응하는 열쇠가 있으면 갈 수 있다
				else if ('A' <= maze[nextY][nextX] && maze[nextY][nextX] <= 'F') {
					if (key & 1 << (maze[nextY][nextX] - 'A')) {
						visited[key][nextY][nextX] = true;
						q.push({ { nextY,nextX, }, {move + 1,key } });
					}
				}
			}
		}

	}
	return -1;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m;

	int y = 0, x = 0;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j) {
			cin >> maze[i][j];
			if (maze[i][j] == '0')
				y = i, x = j;
		}
	cout << solve(y, x);
	return 0;
}