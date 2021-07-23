/*
단순히 방향에 따라 주사위 면의 숫자만 바꿔주면 될 것 같아 쉽게 생각했다.

처음엔 6개 면이 4방향으로 이동하기 때문에 전체 24가지 경우가 있는 줄 알고 24가지 경우 모두 구현했다.
제대로 된 정답이 안나와서 모든 면을 바꾸기 보다 전개도의 수를 배열의 인덱스로 설정해서 그 값만 바꾸는 방식으로 헀는데도 잘 안됐다.

움직였을 때 이전 위치가 현재의 위치 어디로 이동하는지는 파악한 후 값을 넣어줄 때 반대로 넣는 실수도 하면서 시간이 너무 오래걸렸다.
*/

/*
2021.07.22 주사위 평면도를 2차원 배열에 넣고 이동할때마다 바뀌는 면의 숫자를 적절하게 옮겼다.
처음 풀 때와 달리 빨리 해결할 수 있었지만 dx, dy설정이 헷갈렸고 copy에서 주사위 평면도 가로, 세로를 넣어줘야하는데
N, M 을 넣어줘서 복사가 제대로 안됐다. 조금만 더 침착하게 하면 빨리 풀 수 있는데 너무 성급하게 하면 안될 것 같다.

*/
#include <iostream>
using namespace std;

const int MAX = 20 + 1;
int N, M;
int x, y, K;
int map[MAX][MAX];
int tmp[4][3];
int dice[4][3];

int dx[4] = { 0,0,-1,1 };
int dy[4] = { 1,-1,0,0 };

void copy() {
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 3; ++j)
            tmp[i][j] = dice[i][j];
}

void north() {
    dice[0][1] = tmp[1][1];
    dice[1][1] = tmp[2][1];
    dice[2][1] = tmp[3][1];
    dice[3][1] = tmp[0][1];
}

void south() {
    dice[0][1] = tmp[3][1];
    dice[1][1] = tmp[0][1];
    dice[2][1] = tmp[1][1];
    dice[3][1] = tmp[2][1];
}

void east() {
    dice[1][0] = tmp[3][1];
    dice[1][1] = tmp[1][0];
    dice[1][2] = tmp[1][1];
    dice[3][1] = tmp[1][2];
}

void west() {
    dice[1][0] = tmp[1][1];
    dice[1][1] = tmp[1][2];
    dice[1][2] = tmp[3][1];
    dice[3][1] = tmp[1][0];
}

void move(int dir) {
    x += dx[dir];
    y += dy[dir];

    if (!(0 <= x && x < N && 0 <= y && y < M)) {
        x -= dx[dir];
        y -= dy[dir];
        return;
    }


    switch (dir) {
    case 0:east(); break;
    case 1:west(); break;
    case 2:north(); break;
    case 3:south();
    }

    // 이동칸에 쓰여있는 수가 0이면 주사위 바닥면에 있는 수가 칸에 복사
    if (!map[x][y]) {
        map[x][y] = dice[3][1];
    }

    // 0이 아니면 칸에 쓰여있는 수가 주사위 바닥면으로 복사
    else {
        dice[3][1] = map[x][y];
        map[x][y] = 0;
    }
    cout << dice[1][1] << "\n";
}

int main(int argc, char** argv) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M >> x >> y >> K;

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            cin >> map[i][j];

    for (int i = 0; i < K; ++i) {
        int order;
        cin >> order;
        copy();
        move(order - 1);
    }

    return 0;
}


/////////////////////////////////////////

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