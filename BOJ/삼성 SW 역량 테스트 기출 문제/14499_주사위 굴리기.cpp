/*
단순히 방향에 따라 주사위 면의 숫자만 바꿔주면 될 것 같아 쉽게 생각했다.

처음엔 6개 면이 4방향으로 이동하기 때문에 전체 24가지 경우가 있는 줄 알고 24가지 경우 모두 구현했다.
제대로 된 정답이 안나와서 모든 면을 바꾸기 보다 전개도의 수를 배열의 인덱스로 설정해서 그 값만 바꾸는 방식으로 헀는데도 잘 안됐다.

움직였을 때 이전 위치가 현재의 위치 어디로 이동하는지는 파악한 후 값을 넣어줄 때 반대로 넣는 실수도 하면서 시간이 너무 오래걸렸다.
*/

#include <iostream>
using namespace std;

const int MAX = 20 + 1;
int N, M, K;
int x, y;
int board[MAX][MAX];

/*
전개도를 펼쳤을 때
  2
4 1 3
  5
  6
*/
//전개도의 숫자가 dice와 tmp의 인덱스이다. 가장 윗면은 dice[1]
int dice[7];
int tmp[7];

//동서남북 순
int dx[4] = { 0,0,-1,1 };
int dy[4] = { 1,-1,0,0 };

void copy() {
    for (int i = 1; i < 7; ++i)
        tmp[i] = dice[i];
}

void change(int row, int col) {
    if (board[row][col] == 0)
        board[row][col] = dice[6];
    else {
        dice[6] = board[row][col];
        board[row][col] = 0;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M >> x >> y >> K;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            cin >> board[i][j];

    int nx = x;
    int ny = y;

    for (int i = 0; i < K; ++i) {
        int dir;
        cin >> dir;
        dir -= 1;

        copy();

        nx = x + dx[dir];
        ny = y + dy[dir];

        //바깥으로 나가면 무시
        if (!(0 <= nx && nx < N && 0 <= ny && ny < M))
            continue;

        //방향에 따라 주사위 면의 값을 바꿔준다.
        if (dir == 0) {
            dice[3] = tmp[1]; dice[4] = tmp[6];
            dice[6] = tmp[3]; dice[1] = tmp[4];
        }

        else if (dir == 1) {
            dice[4] = tmp[1]; dice[3] = tmp[6];
            dice[6] = tmp[4]; dice[1] = tmp[3];
        }

        else if (dir == 2) {
            dice[1] = tmp[5]; dice[6] = tmp[2];
            dice[2] = tmp[1]; dice[5] = tmp[6];
        }

        else if (dir == 3) {
            dice[1] = tmp[2]; dice[6] = tmp[5];
            dice[2] = tmp[6]; dice[5] = tmp[1];
        }

        change(nx, ny);

        //맨 윗면이 dice[1]
        cout << dice[1] << "\n";
        x = nx; y = ny;
    }

    return 0;
}