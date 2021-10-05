/*
벽돌깨기나 줄기세포배양 문제보다는 이해하기도 쉬웠고 구현도 쉬운편인 것 같다.
블록 모양은 방향에 따라 방향만 바꿔줬고 웜홀의 경우 페어로 존재하기 때문에 구조체를 선언해 벡터로 저장했다.
flag=false이면 웜홀의 첫번째 좌표를 저장했고 true이면 두번쨰 좌표를 저장했다.

값이 제대로 안나온게 두가지 이유였는데
1. 웜홀을 이동할때 y를 변경하니까 x값 변경시 board[y][x]값이 바뀌면서 제대로 된 값이 안들어갔다.
board[y][x]를 tmp에 저장해놓고 하니 제대로 나왔다.
y = wormhole[board[y][x]].y2;
x = wormhole[board[y][x]].x2;

2. 초기화를 제대로 안해서 시간초과가 났다. 무조건 전역이든 지역변수든 초기화를 하고 시작해야겠다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAX = 100;
int N;
int board[MAX][MAX];

int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };

struct hole {
	int y1, x1;
	int y2, x2;
	bool flag = false;
};

vector<hole> wormhole;
int ret;

bool is_in(int y, int x) {
	return 0 <= y && y < N && 0 <= x && x < N;
}

int go(int start_y, int start_x, int y, int x, int dir) {
	int sum = 0;
	while (1) {
		y += dy[dir];
		x += dx[dir];

		//블랙홀 나오면 종료
		if (board[y][x] == -1) {
			break;
		}

		//자기 위치로 돌아오면 종료
		else if (start_y == y && start_x == x)
			break;

		//벽에 부딪힌 경우
		else if (!is_in(y, x)) {
			dir = (dir + 2) % 4;	//방향 반대
			sum++;	//벽에 부딪히면 점수 추가
		}

		//블록 부딪힌 경우
		else if (board[y][x] == 1) {
			if (dir == 0 || dir == 1) {
				sum++;	//방향이 북쪽이거나 남쪽이면 반대방향 이동
				dir = (dir + 2) % 4;
			}
			else if (dir == 2) {
				sum++;
				dir = 1;
			}
			else if (dir == 3) {
				sum++;
				dir = 0;
			}
		}

		else if (board[y][x] == 2) {
			if (dir == 1 || dir == 2) {
				sum++;	//방향이 북쪽이거나 남쪽이면 반대방향 이동
				dir = (dir + 2) % 4;
			}
			else if (dir == 0) {
				sum++;
				dir = 1;
			}
			else if (dir == 3) {
				sum++;
				dir = 2;
			}
		}

		else if (board[y][x] == 3) {
			if (dir == 2 || dir == 3) {
				sum++;	//방향이 북쪽이거나 남쪽이면 반대방향 이동
				dir = (dir + 2) % 4;
			}
			else if (dir == 1) {
				sum++;
				dir = 2;
			}
			else if (dir == 0) {
				sum++;
				dir = 3;
			}
		}

		else if (board[y][x] == 4) {
			if (dir == 0 || dir == 3) {
				sum++;	//방향이 북쪽이거나 남쪽이면 반대방향 이동
				dir = (dir + 2) % 4;
			}
			else if (dir == 1) {
				sum++;
				dir = 0;
			}
			else if (dir == 2) {
				sum++;
				dir = 3;
			}
		}

		//사각형은 방향만 반대로 바꾸면 된다
		else if (board[y][x] == 5) {
			sum++;
			dir = (dir + 2) % 4;
		}

		//웜홀. 좌표만 이동하고 방향은 안바뀜
		else if (6 <= board[y][x] && board[y][x] <= 10) {
			int tmp = board[y][x];
			if (wormhole[tmp].y1 == y && wormhole[tmp].x1 == x) {
				y = wormhole[tmp].y2;
				x = wormhole[tmp].x2;
			}
			else {
				y = wormhole[tmp].y1;
				x = wormhole[tmp].x1;
			}
		}
	}
	return sum;
}

void solve(int y, int x) {
	//해당 좌표에서 4방향 전부 검사해야 한다.
	for (int i = 0; i < 4; ++i) {
		int ny = y + dy[i];
		int nx = x + dx[i];

		ret = max(ret, go(y, x, y, x, i));
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int test_case;
	int T;

	//freopen("input.txt", "r", stdin);
	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		memset(board, 0, sizeof(board));
		wormhole.clear();
		wormhole.resize(10 + 1);
		ret = 0;

		cin >> N;
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				cin >> board[i][j];

				if (6 <= board[i][j] && board[i][j] <= 10) {
					if (wormhole[board[i][j]].flag == false) {
						wormhole[board[i][j]].y1 = i;
						wormhole[board[i][j]].x1 = j;
						wormhole[board[i][j]].flag = true;
					}
					else {
						wormhole[board[i][j]].y2 = i;
						wormhole[board[i][j]].x2 = j;
					}

				}
			}
		}

		//출발 위치, 진행 방향 임의로 설정 가능-> 모든 경우를 다 고려해야한다.
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				if (board[i][j] == 0) {
					solve(i, j);
				}

			}
		}

		cout << "#" << test_case << " " << ret << "\n";
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.

}
