/*
bfs나 dfs를 쓰면서 빨간구슬이 나오면 그만일 줄 알았는데 파란색 구슬이 나오면 안됐다.
구슬을 이동할 수 없을때까지 이동시키는데 두개의 구슬의 좌표를 어떻게 표현해야 할지,
이동시킬때 마다 파란색과 빨간색 구슬을 옮겨줘야 하면 코드가 복잡해졌다.

구슬이 겹칠때 어떻게 해야하는지, 파란색 구슬이 나오면 어떻게 해야하는지 몰라서 풀지 못했다.
그리고 visited배열을 4차원이 아니라 2차원 2개로 구현하면 제대로 된 답이 안나온다.
빨간구슬의 위치가 이전에 방문했다 하더라도 파란구슬이 새로 방문하면 그걸 체크해야한다.
그 반대도 마찬가지이기 때문에 4차원으로 설정 안하면 답이 안나온다.

반례

6 7
#######
#..BR##
#.#####
#.#O###
#....##
#######
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

const int MAX = 10 + 1;
int N, M;
char board[MAX][MAX];

typedef struct {
    int depth;
    int ry, rx, by, bx;
}balls;
queue<balls> q;

int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };

//2차원 배열 두개로 선언하면 제대로 된 답이 안나온다.
bool visited[MAX][MAX][MAX][MAX];

int ry, rx, by, bx, hx, hy; //현재 빨간구슬, 파란구슬, 구멍 좌표
int ret;

void move(int& y, int& x, int d) {
    while (1) {
        y += dy[d]; x += dx[d];
        //벽을 만나거나 구멍을 만나면 종료
        if (board[y][x] == '#') {
            y -= dy[d];
            x -= dx[d];
            break;
        }
        else if (board[y][x] == 'O')
            break;
    }
}

void solve() {

    while (!q.empty()) {
        balls cur = q.front();
        q.pop();

        //횟수가 10회 넘어가면 -1
        if (cur.depth > 10)
            break;

        //빨간 구슬이 구멍에 나오면 종료
        if (cur.ry == hy && cur.rx == hx) {
            ret = cur.depth;
            break;
        }

        //구슬 이동. 움직일 수 없을때까지 이동
        for (int i = 0; i < 4; ++i) {
            int rx = cur.rx, ry = cur.ry;
            int bx = cur.bx, by = cur.by;
            move(ry, rx, i);
            move(by, bx, i);

            //파란구슬이 나오면 안됨. 다른 방향으로 이동
            if (by == hy && bx == hx)
                continue;

            if (ry == by && rx == bx) {
                if (i == 0)
                    cur.ry < cur.by ? by++ : ry++;

                else if (i == 1)
                    cur.rx < cur.bx ? rx-- : bx--;

                else if (i == 2)
                    cur.ry < cur.by ? ry-- : by--;

                else if (i == 3)
                    cur.rx < cur.bx ? bx++ : rx++;

            }

            //방문 안한 좌표는 방문
            if (!visited[ry][rx][by][bx]) {
                balls next = { cur.depth + 1,ry,rx,by,bx };
                q.push(next);
                visited[ry][rx][by][bx] = true;
            }
        }


    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);


    cin >> N >> M;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> board[i][j];
            if (board[i][j] == 'R') {
                ry = i;
                rx = j;
            }
            else if (board[i][j] == 'B') {
                by = i;
                bx = j;
            }
            else if (board[i][j] == 'O') {
                hy = i;
                hx = j;
            }
        }
    }

    q.push({ 0,ry,rx,by,bx });
    visited[ry][rx][by][bx] = true;
    solve();

    //답이 없거나 10회 넘어가면 -1
    if (ret == 0 || ret > 10)
        cout << -1;
    else
        cout << ret;

    return 0;
}