/*
백트래킹을 이용한 문제이다.
핵심은 가로, 세로, 작은 정사각형 모두 1~9까지의 숫자가 있는지 없는지 검사해서 아니면 다시 물리는 것이다.
안 그래도 재귀함수에 약한데 그걸 적용한 알고리즘이라 하니 더 어렵게 느껴졌다.
재귀함수는 많은 연습이 필요할 것 같다.
*/

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
    int y = cnt / MAX;
    int x = cnt % MAX;

    if (cnt == 81) {
        for (int i = 0; i < MAX; i++) {
            for (int j = 0; j < MAX; j++) {
                cout << sudoku[i][j] << " ";
            }
            cout << "\n";
        }
        exit(0);
    }

    //백트래킹
    if (sudoku[y][x] == 0) {
        for (int i = 1; i <= 9; i++) {
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
    else
        dfs(cnt + 1);

}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    for (int i = 0; i < MAX; ++i) {
        for (int j = 0; j < MAX; ++j) {
            cin >> sudoku[i][j];
            if (sudoku[i][j] != 0) {
                ROW[i][sudoku[i][j]] = true;
                COL[j][sudoku[i][j]] = true;
                SQUARE[(i / 3) * 3 + (j / 3)][sudoku[i][j]] = true;
            }
        }
    }

    dfs(0);

    return 0;
}