/*
비교적 쉽게 풀 수 있을거라고 생각했는데 그렇지 않았다.

1. 방향이 북(0), 동(1), 남(2), 서(3) 순서로 가는 것인데 
북 서 남 동 순서로 이동하게 해서 이동좌표가 제대로 맞지 않았다.

2. 현재 위치를 청소한 후 다음 왼쪽 방향을 살펴야 하는데 왼쪽방향을 먼저 살펴서 진행하는 것으로 해서 현재 위치 청소가 이뤄지지 않았다.

3. 방향 후진에서 현재 좌표에서 방향에 맞게 좌표값을 뻬면 되는데 y, x에 1을 직접적으로 더하고 빼다 제대로 된 값이 안들어갔다.
하나씩 좌표를 살펴봐도 되는데 큐를 이용해서 bfs로 풀어도 충분히 풀리는 문제였다.

이런 구현 문제는 문제 조건을 확실히 잘 해석해서 그대로 조건을 따라가야 하는 것 같다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 50 + 3;
int N, M, r, c, d;
int board[MAX][MAX];
bool clean[MAX][MAX];   //청소 여부

//북동남서 순서
int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };

int ret;
void solve(int y, int x) {
	//네 방향 모두 청소가 되어있거나 벽인지 확인. rotate=4이면 네 방향 갈 수 없다.
	int rotate = 0;
	while (1) {
		//현재 위치 청소
		if (board[y][x] == 0 && !clean[y][x]) {
			clean[y][x] = true;
			ret++;
		}

		//왼쪽방향부터 탐색
		int ny = y + dy[(d + 3) % 4];
		int nx = x + dx[(d + 3) % 4];

		if (!(0 <= ny && ny < N && 0 <= nx && nx < M))
			continue;

		//네 방향 모두 청소가 되어있거나 벽인 경우 방향 유지한채 한 칸 후진
		if (rotate == 4) {
			y = y - dy[d];
			x = x - dx[d];

			//후진한 좌표가 벽인 경우 작동 멈춘다.
			if (board[y][x] == 1)
				break;

			//벽이 아니면 rotate 초기화하고 해당 좌표에서 다시 시작
			rotate = 0;
			continue;
		}

		//빈칸이고 청소하지 않았으면 전진 후 다시 1번 진행
		if (board[ny][nx] == 0 && !clean[ny][nx]) {
			d = (d + 3) % 4;
			rotate = 0;
			y = ny; x = nx;
			continue;
		}

		//왼쪽 방향이 벽이거나 청소가 되어있으면 그 뱡향으로 회전
		else if (board[ny][nx] == 1 || clean[ny][nx] == true) {
			d = (d + 3) % 4;
			rotate++;
			continue;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> M;
	cin >> r >> c >> d;

	for (int i = 0; i < N; ++i)
		for (int j = 0; j < M; ++j)
			cin >> board[i][j];

	solve(r, c);

	cout << ret;
	return 0;
}


////////////////////////////////
//큐를 이용한 bfs 풀이
#include <iostream> 
#include <queue>
#include <vector>
#include <algorithm> 
using namespace std; 
const int MAX = 50;
typedef struct { 
	int y, x; 
}Dir; 

Dir moveDir[4] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };// N E S W 
int N, M; 
int graph[MAX][MAX]; 

int main(void) { 
	ios_base::sync_with_stdio(0); 
	cin.tie(0); 
	cin >> N >> M; 
	
	int r, c, d; 
	cin >> r >> c >> d; 
	for (int i = 0; i < N; i++) 
		for (int j = 0; j < M; j++)
			cin >> graph[i][j]; 
	
	int result = 0; 
	queue<pair<pair<int, int>, int>> q;
	q.push({ {r, c}, d });
	while (!q.empty()) { 
		int y = q.front().first.first; 
		int x = q.front().first.second;
		int dir = q.front().second; 

		if (graph[y][x] == 0) { 
			//벽과 구분 위해 
			graph[y][x] = 2;
			result++; 
		} 
		q.pop();
		
		bool flag = false; 
		for (int i = 0; i < 4; i++) {
			//좌회전을 위해 모듈러 연산 
			int nextDir = (dir + (3 - i)) % 4;
			int nextY = y + moveDir[nextDir].y;
			int nextX = x + moveDir[nextDir].x;
			if(0<=nextY && nextY < N && 0 <= nextX && nextX < M) if (!graph[nextY][nextX]) { 
				q.push({ {nextY, nextX}, nextDir});
				flag = true; break; 
			} 
		} 
		//네 방향 다 청소되어 있는 경우 
		if (!flag) { 
			int beforeY = y - moveDir[dir].y;
			int beforeX = x - moveDir[dir].x;
			if ((0 <= beforeY && beforeY < N && 0 <= beforeX && beforeX < M) && graph[beforeY][beforeX] != 1) 
				q.push({ {beforeY, beforeX}, dir });
			else 
				break; 
		} 
	}
	cout << result << "\n";
	return 0;
}
