/*
문제를 잘 읽고 이해한게 비교적 빨리 풀 수 있었던 것 같다.
먹을 수 있는 물고기를 찾았을 때 더이상 경로를 탐색하지 않고
기존 큐에 있는 좌표만 확인하는 것이 관건이었는데 다행히 쉽게 해결했다.

시간이 조금 걸렸던 부분은 물고기가 없는 부분(board[i][j]==0)은 단지 통과만 할 수 있는데
0인 부분도 물고기를 먹은 것으로 쳐서 답이 제대로 안나왔다.

디버깅 가능하니 확인할 수 있었지 프로그래머스에서 풀었으면 빨리 해결 못했을 것 같다.
*/

#include<iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;

const int MAX = 20;
int N;
int board[MAX][MAX];
bool visited[MAX][MAX];

int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };

struct Fish {
	int y, x;
	int size;
};

Fish shark;
vector<pair<int, pair<int, int>>> v;	//먹을 수 있는 물고기 저장

bool fin;
int time, fish_cnt;	//시간과 상어가 먹은 물고기 수

bool is_in(int y, int x) {
	return 0 <= y && y < N && 0 <= x && x < N;
}


//이동하는 큐 하나, 먹을 수 있는 물고기 저장 큐 하나.
bool move(Fish shark) {
	memset(visited, false, sizeof(visited));
	queue < pair<int, pair<int, int>>> q;
	q.push({ 0,{shark.y,shark.x} });
	visited[shark.y][shark.x] = true;

	bool is_fish = false;
	bool edible = false;
	while (!q.empty()) {
		int y = q.front().second.first;
		int x = q.front().second.second;
		int dist = q.front().first;

		q.pop();

		for (int i = 0; i < 4; ++i) {
			int ny = y + dy[i];
			int nx = x + dx[i];

			//범위 밖
			if (!is_in(ny, nx))
				continue;
			//이미 방문
			if (visited[ny][nx])
				continue;
			//자기보다 큰 물고기
			if (board[ny][nx] > shark.size)
				continue;

			//크기가 같거나 작은 경우
			if (board[ny][nx] <= shark.size) {
				//먹을 수 있는 물고기를 못찾았다.
				if (!edible) {
					//크기가 같으면 지나갈 수만 있다.
					if (board[ny][nx] != 0 && board[ny][nx] == shark.size) {
						visited[ny][nx] = true;
						q.push({ dist + 1,{ny,nx} });
					}
					//물고기 없는 칸 지나간다.
					else if (board[ny][nx] == 0) {
						visited[ny][nx] = true;
						q.push({ dist + 1,{ny,nx} });
					}
					//물고기가 있고 먹을 수 있으면 v에 넣는다.
					//먹을 수 있는 물고기가 있다는 edible=true로 해준다.
					else if (board[ny][nx] != 0 && board[ny][nx] < shark.size) {
						is_fish = true;
						edible = true;
						v.push_back({ dist + 1,{ny,nx} });
						visited[ny][nx] = true;
					}
				}
				//먹을 수 있는 물고기 찾았으면 큐에 push 하지 않아도 됨.
				//큐에 남아있는 물고기만 확인. 물고기 있고 먹을수 있으면 v에 푸시
				else {
					if (board[ny][nx] != 0 && board[ny][nx] < shark.size) {
						v.push_back({ dist + 1,{ny,nx} });
						visited[ny][nx] = true;
					}
				}

			}
		}

	}
	return is_fish;
}

void eat_fish() {
	//거리가 가깝고 가장 위, 왼쪽에 있는 물고기 먹는다
	sort(v.begin(), v.end());

	//정렬했을때 제일 앞에 있는 물고기 먹는다.
	int y = v[0].second.first;
	int x = v[0].second.second;
	time += v[0].first;
	fish_cnt++;

	//자기 크기와 같은 수 물고기 먹을때 마다 크기 1 증가
	if (fish_cnt == shark.size) {
		shark.size++;	//크기 증가
		fish_cnt = 0;	//먹은 물고기수는 초기화

	}
	board[shark.y][shark.x] = 0;	//기존에 상어 위치 먹은 물고기 위치로 변경
	shark.y = y;	//상어 위치 변경
	shark.x = x;
	board[y][x] = 9;
	v.clear();
}

int main(int argc, char** argv) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			cin >> board[i][j];
			if (board[i][j] == 9) {
				shark.y = i; shark.x = j; shark.size = 2;
			}

		}
	}

	while (1) {
		if (move(shark))
			//물고기 먹기
			eat_fish();

		else
			break;
	}

	cout << time;


	return 0;
}