/*
6장의 BOARDCOVER랑 비슷한 문제.
가지치기 조건을 찾는 것과 네가지 회전 형태를 미리 만들어 보는 것이 핵심
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

//게임판의 정보
int boardH, boardW;
vector<string> board;
//게임판의 각 칸이 덮였는지를 나타낸다. 1이면 검은 칸이거나 이미 덮은 칸, 0이면 빈 칸
int covered[10][10];
//지금까지 찾은 최적해
int best;

//블록의 각 회전된 형태를 상대 좌표의 목록으로 저장해 둔다.
vector<vector<pair<int, int>>> rotations;
//블록의 크기
int blockSize;
//2차원 배열 arr을 시게방향으로 90도 돌린 결과를 반환한다.
vector<string> rotate(const vector<string>& arr) {
	//가로와 세로가 뒤바뀐 벡터 생성
	vector<string> ret(arr[0].size(), string(arr.size(), ' '));
	for (int i = 0; i < arr.size(); ++i)
		for (int j = 0; j < arr[0].size(); ++j)
			ret[j][arr.size() - i - 1] = arr[i][j];	//90도 회전
	return ret;
}

//block의 네 가지 회전 형태를 만들고 이들을 상대 좌표의 목록으로 변환한다.
void generateRotations(vector<string> block) {
	rotations.clear();
	rotations.resize(4);	//네가지 회전
	for (int rot = 0; rot < 4; ++rot) {
		int originY = -1, originX = -1;
		for (int i = 0; i < block.size(); ++i)
			for (int j = 0; j < block[i].size(); ++j)
				if (block[i][j] == '#') {
					if (originY == -1) {
						//가장 윗줄 맨 왼쪽에 있는 칸이 '원점'이 된다.
						originY = i;
						originX = j;
					}
					//각 칸의 위치를 원점으로부터의 상대좌표로 표현한다.
					rotations[rot].push_back({ i - originY,j - originX });
				}
		//블록을 시계방향으로 90도 회전한다.
		block = rotate(block);
	}

	//네 가지 회전 형태 중 중복이 있을 경우 이를 제거한다.
	sort(rotations.begin(), rotations.end());
	rotations.erase(unique(rotations.begin(), rotations.end()),
		rotations.end());
	//블록이 몇 칸 짜리인지 저장해 둔다.
	blockSize = rotations[0].size();
}

//(y,x)를 왼쪽 위칸으로 해서 주어진 블록을 delta=1이면 놓고, -1이면 없앤다.
//블록을 놓을 때 이미 놓인 블록이나 검은 칸과 겹치면 거짓을, 아니면 참을 반환한다.
bool set(int y, int x, const vector<pair<int, int>>& block, int delta) {
	//placed: 지금까지 놓은 블록의 수
	bool result = true;
	for (int i = 0; i < block.size(); ++i) {
		//범위 내에 있다면
		if (y + block[i].first >= 0 && y + block[i].first < boardH && x + block[i].second >= 0
			&& x + block[i].second < boardW) {
			covered[y + block[i].first][x + block[i].second] += delta;
			result = result && (covered[y + block[i].first][x + block[i].second] == 1);
		}
		else
			result = false;
	}
	return result;
}

//놓을 수 있는 블록의 수는 단순히 남은 빈 칸의 수를 블록의 크기로 나눈 것
//거기에 이미 놓은 수를 더했을 때 기존 최적해보다 적을 경우 최적해
int blockPrune(int placed) {	//가지치기
	int cnt = 0;
	for (int i = 0; i < boardH; ++i)
		for (int j = 0; j < boardW; ++j)
			cnt += !(covered[i][j]) ? 1 : 0;
	return ((cnt / blockSize) + placed <= best);
}

//placed: 지금까지 놓은 블록의 수
void search(int placed) {
	if (blockPrune(placed))	//가지치기
		return;
	//아직 채우지 못한 빈 칸 중 가장 윗줄 왼쪽에 있는 칸을 찾는다.
	int y = -1, x = -1;
	for (int i = 0; i < boardH; ++i) {
		for (int j = 0; j < boardW; ++j) {
			if (covered[i][j] == 0) {
				y = i;
				x = j;
				break;
			}
		}
		if (y != -1)
			break;
	}
	//기저 사례:게임판의 모든 칸을 처리한 경우
	if (y == -1) {
		best = max(best, placed);
		return;
	}
	//이 칸을 덮는다.
	for (int i = 0; i < rotations.size(); ++i) {
		if (set(y, x, rotations[i], 1))
			search(placed + 1);
		//다시 없앤다.
		set(y, x, rotations[i], -1);
	}
	//이 칸을 덮지 않고 막아둔다
	covered[y][x] = 1;
	search(placed);
	covered[y][x] = 0;
}

int solve() {
	best = 0;
	//covered 배열 초기화
	for (int i = 0; i < boardH; ++i)
		for (int j = 0; j < boardW; ++j)
			covered[i][j] = (board[i][j] == '#' ? 1 : 0);
	search(0);
	return best;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int c;
	cin >> c;
	while (c--) {
		board.clear();
		vector<string> block;
		int blockH, blockW;	//블록의 세로, 가로 크기
		cin >> boardH >> boardW >> blockH >> blockW;

		//보드판 입력
		for (int j = 0; j < boardH; ++j) {
			string temp;
			cin >> temp;
			board.push_back(temp);
		}
		//블록 입력
		for (int j = 0; j < blockH; ++j) {
			string temp;
			cin >> temp;
			block.push_back(temp);
		}
		generateRotations(block);
		cout << solve() << "\n";
	}

	return 0;
}