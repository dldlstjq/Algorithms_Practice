#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

//turn이 한 줄을 만들었는지를 반환한다.
bool isFinished(const vector<string>& board, char turn) {
	//가로
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (board[i][j] != turn)
				break;
			if (j == 2)
				return true;
		}
	}
	//세로
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (board[j][i] != turn)
				break;
			if (j == 2)
				return true;
		}
	}
	//대각선 ↘
	for (int i = 0; i < 3; ++i) {
		if (board[i][i] != turn)
			break;
		if (i == 2)
			return true;
	}
	//대각선 ↙
	for (int i = 0; i < 3; ++i) {
		if (board[i][2 - i] != turn)
			break;
		if (i == 2)
			return true;
	}
	return false;
}

//틱택토 게임판이 주어질때 [0,19682] 범위의 정수로 변환한다.
int bijection(const vector<string>& board) {
	int ret = 0;
	for (int y = 0; y < 3; ++y)
		for (int x = 0; x < 3; ++x) {
			ret = ret * 3;
			if (board[y][x] == 'o')
				++ret;
			else if (board[y][x] == 'x')
				ret += 2;
		}
	return ret;
}

//cache[]는 -2로 초기화한다. 함수의 반환값이 -1이 될수도 있기 떄문.
//3^9=19682(모든 판이 x인 경우)
int cache[19683];
//내가 이길 수 있으면 1을, 비길 수 있으면 0을, 지면 -1을 리턴한다.
int canWin(vector<string>& board, char turn) {
	//기저사례: 마지막에 상대가 둬서 한 줄이 만들어진 경우
	if (isFinished(board, 'o' + 'x' - turn))
		return -1;
	int& ret = cache[bijection(board)];
	if (ret != 2)
		return ret;
	//모든 반환 값의 min을 취하자.
	int minValue = 2;
	for (int y = 0; y < 3; ++y)
		for (int x = 0; x < 3; ++x)
			if (board[y][x] == '.') {
				board[y][x] = turn;
				minValue = min(minValue, canWin(board, 'o' + 'x' - turn));
				board[y][x] = '.';
			}
	//플레이할 수 없거나, 어떻게 해도 비기는 것이 최선인 경우
	if (minValue == 2 || minValue == 0)
		return ret = 0;
	//최선이 상대가 이기는 거라면 난 무조건 지고, 상대가 지는 거라면 난 이긴다.
	return ret = -minValue;
}
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	vector<string> board;
	for (int i = 0; i < 19683; i++)
		cache[i] = -2; //캐시 초기화(-2로는 memset X)

	int c;
	cin >> c;
	while (c--) {


		board.clear();
		int placed = 0;	//다음 순서 계산을 위해
		for (int i = 0; i < 3; ++i) {
			string cell;
			cin >> cell;
			for (int j = 0; j < 3; ++j)
				if (cell[j] != '.')
					placed++;
			board.push_back(cell);
		}

		char start = 'x';
		if (placed % 2 == 1)//x부터 시작하므로
			start = 'o';

		switch (canWin(board, start)) {
		case-1:
			cout << (char)('x' + 'o' - start) << "\n";
			break;
		case 0:
			cout << "TIE" << "\n";
			break;
		case 1:
			cout << start << "\n";
			break;
		}
	}

	return 0;
}