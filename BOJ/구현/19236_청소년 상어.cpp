/*
재귀를 어떻게 실행해야 할지 몰라서 못풀었다.
정답이랑 비슷하게 따라했는데 답이 안나온다.
밑에 있는 코드가 비슷한 코드인데 왜 위에건 안되고 밑에건 되는지 모르겠다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;

struct Fish {
    int idx, dir;
    int y, x;
};

int ret;
Fish shark;
Fish fishes[17];
int fishtank[4][4];

int dy[8] = { -1,-1,0,1,1,1,0,-1 };
int dx[8] = { 0,-1,-1,-1,0,1,1,1 };

void solve(Fish fishes[17], int fishtank[4][4], Fish shark, int sum) {
    ret = max(ret, sum);

    //물고기 이동
    for (int i = 1; i <= 16; ++i) {
        int y = fishes[i].y;
        int x = fishes[i].x;
        int dir = fishes[i].dir;

        if (dir == 0)
            continue;

        int ny = y + dy[dir];
        int nx = x + dx[dir];

        int dircnt = 0;

        for (dircnt = 0; dircnt < 8; ++dircnt) {
            ny = y + dy[dir];
            nx = x + dx[dir];

            if (ny < 0 || ny >= 4 || nx < 0 || nx >= 4) {
                fishes[i].dir = (dir == 8) ? 0 : dir + 1;
                dir = fishes[i].dir;
                continue;
            }

            if (ny == shark.y && nx == shark.x) {
                fishes[i].dir = (dir == 8) ? 0 : dir + 1;
                dir = fishes[i].dir;
                continue;
            }
            break;
        }

        if (dircnt == 8)
            continue;

        int nextIdx = fishtank[ny][nx];

        //자리 교환
        if (nextIdx) {
            fishes[nextIdx].y = y;
            fishes[nextIdx].x = x;
            fishtank[y][x] = nextIdx;
        }
        else
            fishtank[y][x] = 0;

        fishes[i].y = ny;
        fishes[i].x = nx;
        fishtank[ny][nx] = i;
    }

    //상어 이동
    int y = shark.y;
    int x = shark.x;
    int dir = shark.dir;

    for (int i = 1; i <= 3; ++i) {
        Fish tempFishes[17];
        for (int j = 0; j < 17; ++j)
            tempFishes[j] = fishes[j];

        int tempfishtank[4][4];
        for (int j = 0; j < 4; ++j)
            for (int k = 0; k < 4; ++k)
                tempfishtank[j][k] = fishtank[j][k];

        int ny = y + dy[dir] * i;
        int nx = x + dx[dir] * i;

        if (ny < 0 || ny >= 4 || nx < 0 || nx >= 4)
            continue;

        if (tempfishtank[ny][nx] == 0)
            continue;

        shark.y = ny;
        shark.x = nx;

        int score = tempfishtank[ny][nx];
        tempfishtank[ny][nx] = 0;

        shark.dir = tempFishes[score].dir;
        tempFishes[score].dir = 0;

        solve(tempFishes, tempfishtank, shark, sum + score);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            int a, b;
            cin >> a >> b;
            b -= 1;

            if (i == 0 && j == 0) {
                shark = { a,b,i,j };
                continue;
            }

            fishes[a] = { a,b,i,j };
            fishtank[i][j] = a;

        }
    }

    solve(fishes, fishtank, shark, shark.idx);
    cout << ret;


    return 0;
}




/////////////////////////////////////////////////
#include <iostream> 
#include <queue> 
#include <algorithm> 
using namespace std;
const int MAX = 4;
typedef struct {
    int y, x;
}
Dir;
Dir moveDir[9] = { {0, 0}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1} };
typedef struct {
    int idx, dir;
    int y, x;
}Fish;

int result;
Fish shark;
Fish fishes[MAX * MAX + 1];
int fishTank[MAX][MAX];

void func(Fish fishes[MAX * MAX + 1], int fishTank[MAX][MAX], Fish shark, int total) {
    result = max(result, total);
    // fish 
    for (int i = 1; i <= MAX * MAX; i++) {
        int y = fishes[i].y;
        int x = fishes[i].x;
        int dir = fishes[i].dir;

        if (dir == 0) {
            continue;
        }

        int nextY = y + moveDir[dir].y;
        int nextX = x + moveDir[dir].x;
        int dirChangeCnt = 0;
        for (dirChangeCnt = 0; dirChangeCnt < 8; dirChangeCnt++) {
            nextY = y + moveDir[dir].y;
            nextX = x + moveDir[dir].x;
            if (nextY < 0 || nextY >= MAX || nextX < 0 || nextX >= MAX) {
                fishes[i].dir = (dir == 8) ? 1 : dir + 1;
                dir = fishes[i].dir;
                continue;
            }
            if (nextY == shark.y && nextX == shark.x) {
                fishes[i].dir = (dir == 8) ? 1 : dir + 1;
                dir = fishes[i].dir; continue;
            }
            break;
        }
        if (dirChangeCnt == 8) {
            continue;
        }
        int nextIdx = fishTank[nextY][nextX];
        if (nextIdx) {
            fishes[nextIdx].y = y;
            fishes[nextIdx].x = x;
            fishTank[y][x] = nextIdx;
        }
        else {
            fishTank[y][x] = 0;
        }
        fishes[i].y = nextY;
        fishes[i].x = nextX;
        fishTank[nextY][nextX] = i;
    }
    // shark 
    int y = shark.y;
    int x = shark.x;
    int dir = shark.dir;
    for (int i = 1; i <= 3; i++) {
        Fish tempFishes[MAX * MAX + 1];
        for (int idx = 0; idx < MAX * MAX + 1; idx++) {
            tempFishes[idx] = fishes[idx];
        }
        int tempFishTank[MAX][MAX];
        for (int j = 0; j < MAX; j++) {
            for (int k = 0; k < MAX; k++) {
                tempFishTank[j][k] = fishTank[j][k];
            }
        }
        int nextY = y + moveDir[dir].y * i;
        int nextX = x + moveDir[dir].x * i;
        if (nextY < 0 || nextY >= MAX || nextX < 0 || nextX >= MAX) {
            continue;
        }
        if (tempFishTank[nextY][nextX] == 0) {
            continue;
        }
        shark.y = nextY;
        shark.x = nextX;
        int score = tempFishTank[nextY][nextX];
        tempFishTank[nextY][nextX] = 0;
        shark.dir = tempFishes[score].dir;
        tempFishes[score].dir = 0;
        func(tempFishes, tempFishTank, shark, total + score);
    }
}

int main(void) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    for (int y = 0; y < MAX; y++) {
        for (int x = 0; x < MAX; x++) {
            int idx, dir;
            cin >> idx >> dir;
            if (y == 0 && x == 0) {
                shark = { idx, dir, y, x };
                continue;
            }
            fishes[idx] = { idx, dir, y, x };
            fishTank[y][x] = idx;
        }
    }
    func(fishes, fishTank, shark, shark.idx);
    cout << result << "\n";
    return 0;
}
