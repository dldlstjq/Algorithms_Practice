/*
우선 문제 이해부터 제대로 하지 못했다.
0초부터 시작하여 X초가 되면 방향을 바꾸는 것인데
X초 만큼 움직이면 다시 0초부터 그 다음 X초동안 움직이는 걸로 이해해 에제의 답을 도통 이해할 수 없었다.

처음 접근했던 방법은
무식하게 뱀의 머리와 꼬리의 좌표를 저장하고
움직이는 만큼 머리와 꼬리를 이동 시킨후 뱀의 몸통은 -1로 보드에 표현했다.
하지만 뱀의 몸통 전체를 움직이게 하는데 한계가 있었고 결국 해결할 수 없었다.
다른 사람들은 덱을 이용해서 문제를 해결했다.
*/

#include <iostream> 
#include <vector> 
#include <string> 
#include <deque>
using namespace std;

const int MAX = 100; 
typedef struct { 
	int y, x; 
}Dir; 
Dir moveDir[4] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} }; //E S W N

int N, K, L; 
bool visited[MAX][MAX];
bool apple[MAX][MAX];

int main(void) { 
	ios_base::sync_with_stdio(0);
	cin.tie(0); 
	cin >> N; 
	cin >> K; 
	for (int k = 0; k < K; k++) { 
		int y, x; 
		cin >> y >> x;
		apple[y - 1][x - 1] = true; 
	} 
	cin >> L; 
	deque<pair<int, char>> turn;
	for (int l = 0; l < L; l++) { 
		int X;
		char C;
		cin >> X >> C;
		turn.push_back({ X, C }); 
	} 

	int sec = 0;
	int idx = 0; //초기 오른쪽 
	deque<pair<int, int>> snake; 
	snake.push_back({ 0, 0 }); //초기 위치
	visited[0][0] = true;

	while (1) { 
		sec++; 
		pair<int, int> before = snake.back();
		pair<int, int> cur = {before.first + moveDir[idx].y, before.second + moveDir[idx].x };
		//뱀의 머리가 몸에 부딪히거나, 범위를 벗어날 경우 
		if (visited[cur.first][cur.second] || !(0 <= cur.first && cur.first < N && 0 <= cur.second && cur.second < N)) { 
			cout << sec << "\n"; break;
		} 

		visited[cur.first][cur.second] = true; 
		snake.push_back(cur); 
		//사과가 있는 위치면 꼬리 그대로 
		if (apple[cur.first][cur.second]) 
			apple[cur.first][cur.second] = false;
		//사과 없으면 꼬리가 있던 칸을 지운다 
		else {
			pair<int, int> tail = snake.front();
			visited[tail.first][tail.second] = false; 
			snake.pop_front(); 
		}

		//마지막에 방향 전환
		if (turn.size() && turn.front().first == sec) {
			if (turn.front().second == 'L') 
				idx = (idx + 3) % 4;
			else idx = (idx + 1) % 4; turn.pop_front(); 
		} 
	} 
	return 0;
}