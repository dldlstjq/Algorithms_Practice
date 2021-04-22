/*
드래곤 커브를 그리는것이 관건이었다.
처음 생각난것은 재귀를 사용해야하는지 아니면 어떤 규칙성이 있는지를 파악하려 했다.
재귀는 아닌것 같아서 0,1,2,3 순서에 규칙이 있는지 파악했는데 바로 발견하지는 못했다.
다시 보니 0에서 시작하면 선분이 1방향이 되고 1->2 2->3 3->0 으로 반복되는 것이 보였다.

이 방향을 한곳에 저장해 y,x 좌표를 바꿔가며 그리면 드래곤 커브가 완성된다.
규칙을 빨리 찾으면 비교적 빨리 풀 수 있는 문제인데 못찾으면 시간이 많이 걸릴것 같다.
*/

#include<iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 100 + 1;
int map[MAX][MAX];
int N;

//0,1,2,3 순서
int dy[4] = { 0,-1,0,1 };
int dx[4] = { 1,0,-1,0 };


int main(int argc, char** argv) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;
	for (int i = 0; i < N; ++i) {
		int x, y, d, g;
		cin >> x >> y >> d >> g;

		map[y][x] = 1;
		vector<int> curve;
		curve.push_back(d);
		//g세대만큼 방향을 구해서 curve에 저장한다.
		for (int j = 0; j < g; ++j) {
			vector<int>tmp = curve;
			for (int k = tmp.size() - 1; k >= 0; --k)
				curve.push_back((tmp[k] + 1) % 4);
		}

		for (int j = 0; j < curve.size(); ++j) {
			y = y + dy[curve[j]];
			x = x + dx[curve[j]];

			//범위내에만 표시
			if (0 <= y && y < MAX && 0 <= x && x < MAX)
				map[y][x] = 1;
		}
	}

	int ret = 0;
	for (int i = 0; i < MAX; ++i) {
		for (int j = 0; j < MAX; ++j) {
			if (map[i][j] == 1 && map[i][j + 1] == 1 &&
				map[i + 1][j] == 1 && map[i + 1][j + 1] == 1)
				ret++;
		}
	}
	cout << ret;


	return 0;
}