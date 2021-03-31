/*
구슬 탈출 2랑 거의 비슷한 문제였다.
다시 봐도 아리송한게 있었는데 구슬이 이동한 후 좌표를 저장할때 구조체를 사용하는것, 큐를 이용해서 하나씩 검사하는게 핵심인것 같다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int MAX = 10 + 1;
int N, M;
char board[MAX][MAX];
bool visited[MAX][MAX][MAX][MAX];

int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };

int ry, rx, by, bx, hy, hx;
int ret = 987654321;

struct gooseul {
    int ry, rx, by, bx;
    int cnt;
};
queue<gooseul> q;

void move_gooseul(int& y, int& x, int dir) {
    while (1) {
        y += dy[dir];
        x += dx[dir];
        //벽을 만나거나 구멍을 만나면 종료
        if (board[y][x] == '#') {
            y -= dy[dir];
            x -= dx[dir];
            break;
        }
        else if (board[y][x] == 'O')
            break;
    }
}

void solve() {

    while (!q.empty()) {
        gooseul cur = q.front();
        q.pop();

        //빨간색 구슬이 나오면 종료
        if (cur.ry == hy && cur.rx == hx) {
            ret = min(ret, cur.cnt);
            break;
        }

        for (int d = 0; d < 4; ++d) {
            int ry = cur.ry, rx = cur.rx;
            int by = cur.by, bx = cur.bx;
            move_gooseul(ry, rx, d);
            move_gooseul(by, bx, d);

            //파란색 구슬이 나오면 안됨
            if (by == hy && bx == hx)
                continue;

            //두 구슬이 겹치는 경우
            //cur의 위치에 따라 조정한다.
            else if (ry == by && rx == bx) {
                if (d == 0)
                    cur.ry < cur.by ? by++ : ry++;
                else if (d == 1)
                    cur.rx < cur.bx ? rx-- : bx--;
                else if (d == 2)
                    cur.ry < cur.by ? ry-- : by--;
                else if (d == 3)
                    cur.rx < cur.bx ? bx++ : rx++;
            }

            //방문 안한 좌표는 방문
            if (!visited[ry][rx][by][bx]) {
                q.push({ ry,rx,by,bx,cur.cnt + 1 });
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
                ry = i; rx = j;
            }
            else if (board[i][j] == 'B') {
                by = i; bx = j;
            }
            else if (board[i][j] == 'O') {
                hy = i; hx = j;
            }
        }
    }

    visited[ry][rx][by][bx] = true;
    q.push({ ry, rx, by, bx, 0 });
    solve();

    if (ret == 987654321)
        cout << -1;
    else
        cout << ret;

    return 0;
}