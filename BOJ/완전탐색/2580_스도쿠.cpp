/*
백트래킹을 이용한 문제이다.
핵심은 가로, 세로, 작은 정사각형 모두 1~9까지의 숫자가 있는지 없는지 검사해서 아니면 다시 물리는 것이다.
안 그래도 재귀함수에 약한데 그걸 적용한 알고리즘이라 하니 더 어렵게 느껴졌다.
재귀함수는 많은 연습이 필요할 것 같다.
*/

// 2021.07.02 백트래킹 연습에 스도쿠만한게 없는것 같다. 3가지 경우 모두 확인해야한다는 점을 생각하면 그나마 생각하기 수월할 것 같다.

#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
#define MAX 9
int sudoku[MAX][MAX];
//Row[a][b] = true 의 의미는 " a번째 가로줄에 b라는 숫자는 이미 존재합니다. "
//Col[a][b] = true 의 의미는 " a번째 세로줄에 b라는 숫자는 이미 존재합니다."
//Square[a][b] = true 의 의미는 "a번째 사각형에 b라는 숫자는 이미 존재합니다."
bool ROW[MAX][MAX];
bool COL[MAX][MAX];
bool SQUARE[MAX][MAX];

void dfs(int cnt) {
    //cnt를 기준으로 각 칸의 좌표를 계산한다.
    //cnt의 범위는 0~80
    int y = cnt / MAX;
    int x = cnt % MAX;

    //cnt가 81이라는 것은 모든 칸의 계산이 끝난것이므로
    //출력하고 종료한다.
    if (cnt == 81) {
        for (int i = 0; i < MAX; i++) {
            for (int j = 0; j < MAX; j++) {
                cout << sudoku[i][j] << " ";
            }
            cout << "\n";
        }
        exit(0);
    }

    //칸이 비어있으면 하나씩 넣으면서 백트래킹 시도
    if (sudoku[y][x] == 0) {
        for (int i = 1; i <= 9; i++) {
            //(y,x)에 해당하는 행, 열, 3x3 작은 사각형에 1~9 중 없는 숫자가 있으면 집어넣는다.
            if (ROW[y][i] == false && COL[x][i] == false && SQUARE[(y / 3) * 3 + (x / 3)][i] == false) {
                ROW[y][i] = true;
                COL[x][i] = true;
                SQUARE[(y / 3) * 3 + (x / 3)][i] = true;
                sudoku[y][x] = i;
                dfs(cnt + 1);
                sudoku[y][x] = 0;
                ROW[y][i] = false;
                COL[x][i] = false;
                SQUARE[(y / 3) * 3 + (x / 3)][i] = false;
            }
        }
    }
    //숫자가 있으면 다음 칸으로 진행
    else
        dfs(cnt + 1);

}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    for (int i = 0; i < MAX; ++i) {
        for (int j = 0; j < MAX; ++j) {
            cin >> sudoku[i][j];
            //해당 좌표가 0이 아닌경우 각 행, 열, 작은 사각형에 대해 숫자가 있는지 체크
            if (sudoku[i][j] != 0) {
                ROW[i][sudoku[i][j]] = true;
                COL[j][sudoku[i][j]] = true;
                //작은 3x3사각형. 왼쪽 위에서부터 0,1,2...,맨 오른쪽 밑은 8
                SQUARE[(i / 3) * 3 + (j / 3)][sudoku[i][j]] = true;
            }
        }
    }

    dfs(0);

    return 0;
}