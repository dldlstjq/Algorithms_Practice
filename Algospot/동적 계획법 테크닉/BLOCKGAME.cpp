﻿/*
TICTACTOE와 비슷하게 보드의 모든 경우의 수를 미리 계산해놓고 푸는 문제.
보드를 5*5 배열로 표현하지 않고 비트 시프트 연산을 이용해 25자리로 만들어 표현.
비트에 대해 이해하지 않으면 조금 어렵지 않을까 싶다.
*/

#include <iostream>
#include <vector>
#include <cstring>
#include <bitset>

using namespace std;

vector<int> moves;
inline int cell(int y, int x) {
	return 1 << (y * 5 + x);
}
//게임판에 놓을 수 있는 블록들의 위치를 미리 계산한다.
void precalc() {
	//세 칸짜리 L자 모양 블록들을 계산한다.
	//세 칸짜리는 무조건 가로 세로 두칸씩 먹음
	for (int y = 0; y < 4; ++y)
		for (int x = 0; x < 4; ++x) {
			vector<int> cells;
			for (int dy = 0; dy < 2; ++dy)
				for (int dx = 0; dx < 2; ++dx)
					cells.push_back(cell(y + dy, x + dx));
			int square = cells[0] + cells[1] + cells[2] + cells[3];	//정사각형을 만들어
			for (int i = 0; i < 4; ++i)
				moves.push_back(square - cells[i]);	//하나의 칸을 빼주면 L자 모양
		}
	//두 칸 짜리 블록들을 계산한다.
	//두 칸짜리는 가로가 한 칸이라면 세로가 두 칸, 세로가 한 칸이라면 가로가 두 칸 
	for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 4; ++j) {
			moves.push_back(cell(i, j) + cell(i, j + 1));
			moves.push_back(cell(j, i) + cell(j + 1, i));
		}
}

char cache[1 << 25];
//현재 게임판 상태가 board일 때 현재 차례인 사람이 승리할지 여부를 반환한다.
//(y,x)칸에 블록이 있다. <=> (y*5+x)번 비트가 켜져 있다.
char play(int board) {
	//메모이제이션
	char& ret = cache[board];
	if (ret != -1)
		return ret;
	ret = 0;
	//모든 수를 고려한다.
	for (int i = 0; i < moves.size(); ++i)
		//이 수를 이 게임판에 놓을 수 있는가 확인
		if ((moves[i] & board) == 0)	//아직 보드에 놓여지지 않았고
			if (!play(board | moves[i])) {	//게임판에 놓을 수 없는 경우
				ret = 1;	//마지막으로 놓은 사람이 자신이므로 이겼다.
				break;
			}
	return ret;
}
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	precalc();
	int c;
	cin >> c;
	while (c--) {
		memset(cache, -1, sizeof(cache));
		int board = 0;
		//보드 초기화
		for (int i = 0; i < 5; ++i)
			for (int j = 0; j < 5; ++j) {
				char space;
				cin >> space;
				if (space == '#')
					board += cell(i, j);
			}
		if (play(board))
			cout << "WINNING" << "\n";
		else
			cout << "LOSING" << "\n";
	}

	return 0;
}