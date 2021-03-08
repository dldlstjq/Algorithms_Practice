/*
2580_스도쿠 문제와 입력만 다를뿐이지 똑같은 문제인 줄 알고 접근을 똑같이 했다가 해결하지 못했다.
스도쿠 문제에서는 하나의 해만 출력하고 종료하면 되지만 여기서는 여러개의 테스트케이스가 있기 때문에
출력하고 종료가 되지 않았다. 이 부분을 해결하지 못했고 애초에 문제자체도 도미노 타일을 이용해야 되는데
그냥 숫자 하나씩 넣어보는 방식으로 접근했다.

도미노 타일을 이용하기 위해서는 타일의 이용여부를 나타내는 visited 배열이 하나 더 필요하다.
그리고 타일을 회전시킬 수 있기 때문에 두 방향에 대해 전부 검사해야한다.
현재 좌표와 오른쪽, 아래 좌표 모두 검사해서 없는 숫자라면 백트래킹을 진행한다.
숫자를 뒤집는 경우도 고려해줘야 하기 때문에 스도쿠문제보단 더 까다롭다.


*/

#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX = 9;

int sudoku[MAX][MAX];

int row[MAX][MAX + 1];
int col[MAX][MAX + 1];
int square[MAX][MAX + 1];
bool visited[MAX + 1][MAX + 1]; //이미 있는 타일 파악. {1, 2}~~{8, 9}
int dy[2] = { 0, 1 }, dx[2] = { 1, 0 };

bool flag;
void init() {
    flag = false;
    memset(sudoku, 0, sizeof(sudoku));
    memset(row, 0, sizeof(row));
    memset(col, 0, sizeof(col));
    memset(square, 0, sizeof(square));
    memset(visited, 0, sizeof(visited));
}

//3x3 사각형의 좌표.
int calc_idx(int y, int x) {
    return (y / 3 * 3) + (x / 3);
}

void solve(int num) {
    //이미 답을 찾은 경우
    if (flag)
        return;

    //num이 81이면 출력
    if (num == 81) {
        flag = true;
        for (int i = 0; i < MAX; ++i) {
            for (int j = 0; j < MAX; ++j) {
                cout << sudoku[i][j];
            }
            cout << "\n";
        }
        return;
    }

    int y = num / 9;
    int x = num % 9;

    if (sudoku[y][x] == 0) {
        // 오른쪽, 아래에 대한 검사(왼쪽, 위는 이미 재귀 중에 채워지므로 pass)
        for (int dir = 0; dir < 2; ++dir) {
            int ny = y + dy[dir];
            int nx = x + dx[dir];
            //범위 밖인 경우
            if (ny >= 9 || nx >= 9)continue;
            //해당 칸이 이미 채워진 경우
            if (sudoku[ny][nx] != 0)continue;

            //도미노 (1,2) (1,3) ... (8, 9)까지 검사
            for (int i = 1; i < 9; ++i) {
                for (int j = i + 1; j <= 9; ++j) {
                    //해당 도미노가 안쓰인 경우
                    if (!visited[i][j]) {
                        visited[i][j] = true;
                        //i, j순으로 넣어줄 때
                        if (!row[y][i] && !col[x][i] && !square[calc_idx(y, x)][i] &&
                            !row[ny][j] && !col[nx][j] && !square[calc_idx(ny, nx)][j]) {
                            sudoku[y][x] = i;
                            sudoku[ny][nx] = j;
                            row[y][i] = col[x][i] = square[calc_idx(y, x)][i] = true;
                            row[ny][j] = col[nx][j] = square[calc_idx(ny, nx)][j] = true;
                            solve(num + 1);
                            sudoku[y][x] = 0;
                            sudoku[ny][nx] = 0;
                            row[y][i] = col[x][i] = square[calc_idx(y, x)][i] = false;
                            row[ny][j] = col[nx][j] = square[calc_idx(ny, nx)][j] = false;
                        }
                        //j, i순으로 뒤집어서 넣을줄 때
                        if (!row[y][j] && !col[x][j] && !square[calc_idx(y, x)][j] &&
                            !row[ny][i] && !col[nx][i] && !square[calc_idx(ny, nx)][i]) {
                            sudoku[y][x] = j;
                            sudoku[ny][nx] = i;
                            row[y][j] = col[x][j] = square[calc_idx(y, x)][j] = true;
                            row[ny][i] = col[nx][i] = square[calc_idx(ny, nx)][i] = true;
                            solve(num + 1);
                            sudoku[y][x] = 0;
                            sudoku[ny][nx] = 0;
                            row[y][j] = col[x][j] = square[calc_idx(y, x)][j] = false;
                            row[ny][i] = col[nx][i] = square[calc_idx(ny, nx)][i] = false;
                        }
                        visited[i][j] = false;
                    }
                }

            }
        }


    }
    else
        solve(num + 1);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int cnt = 1;
    while (1) {
        int n;
        cin >> n;
        if (n == 0)
            break;

        //초기화
        init();

        //입력. 열의 경우 0부터 시작하기 위해 c1-1을 인덱스로 넣었다.
        for (int i = 0; i < n; ++i) {
            int u, v;
            string lu, lv;
            cin >> u >> lu >> v >> lv;

            //(u,v) (v,u) 타일은 이미 썼다.
            visited[u][v] = true;
            visited[v][u] = true;
            int r1 = lu[0] - 'A';
            int c1 = lu[1] - '0' - 1;
            int r2 = lv[0] - 'A';
            int c2 = lv[1] - '0' - 1;

            //숫자표시
            sudoku[r1][c1] = u;
            sudoku[r2][c2] = v;
            //가로, 세로 표시
            row[r1][u] = col[c1][u] = true;
            row[r2][v] = col[c2][v] = true;
            square[calc_idx(r1, c1)][u] = true;
            square[calc_idx(r2, c2)][v] = true;
        }
        //1~9까지 숫자를 좌표에 입력
        for (int i = 1; i <= 9; ++i) {
            string str;
            cin >> str;
            int r = str[0] - 'A';
            int c = str[1] - '0' - 1;
            sudoku[r][c] = i;
            row[r][i] = true;
            col[c][i] = true;
            square[calc_idx(r, c)][i] = true;
        }

        cout << "Puzzle " << cnt++ << "\n";
        solve(0);
    }
    return 0;
}