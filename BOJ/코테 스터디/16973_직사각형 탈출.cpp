/*
처음 접근했을 때는 직사각형의 모든 좌표를 큐에 넣었다.
그러다 보니 방문여부를 확인하는 것이 오래걸렸고 시간초과가 났다.

두번째 시도한 방법은 가장 위쪽 좌표만 이동하여 확인하는 것이었다.
4방향으로 이동하여 직사각형의 테두리만 확인하여 갈 수 있는지 없는지 했다.
문제는 해당 좌표로부터 시작해서 직사각형의 크기를 고려해야 하는데 그냥 직사각형의 크기만 고려해서 틀렸다.

*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

const int MAX = 1000 + 2;
int N, M;
int H, W;
int board[MAX][MAX];
int start_r, start_c;
int fin_r, fin_c;

bool visited[MAX][MAX];

int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };

bool check(int y, int x, int dir) {
    //틀린부분. x~x+w 만큼 확인해야 하고, 다른 좌표를 확인할때
    //해당 좌표가 범위를 벗어나는지 확인해야한다.
    //위
    if (dir == 0) {
        for (int i = x; i < x + W; ++i) {
            if (board[y][i] == 1)
                return false;
        }
    }

    //오
    else if (dir == 1) {
        x = x + W - 1;
        if (x >= M)
            return false;

        for (int i = y; i < y + H; ++i) {
            if (board[i][x] == 1)
                return false;
        }
    }

    //아래
    else if (dir == 2) {
        y = y + H - 1;
        if (y >= N)
            return false;
        for (int i = x; i < x + W; ++i) {
            if (board[y][i] == 1)
                return false;
        }
    }

    //왼
    else if (dir == 3) {
        for (int i = y; i < y + H; ++i) {
            if (board[i][x] == 1)
                return false;
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            cin >> board[i][j];

    cin >> H >> W >> start_r >> start_c >> fin_r >> fin_c;
    start_r -= 1; start_c -= 1;
    fin_r -= 1; fin_c -= 1;

    queue<pair<pair<int, int>, int>> q;
    q.push({ { start_r,start_c }, 0 });
    visited[start_r][start_c] = true;
    int ret = 987654321;


    while (!q.empty()) {
        int y = q.front().first.first;
        int x = q.front().first.second;
        int cnt = q.front().second;
        q.pop();

        //가장 왼쪽 위칸이 fin이랑 같으면 종료
        if (y == fin_r && x == fin_c) {
            ret = min(ret, cnt);
            break;
        }

        //4방향 검사
        for (int i = 0; i < 4; ++i) {
            int ny = y + dy[i];
            int nx = x + dx[i];

            if (!(0 <= ny && ny < N && 0 <= nx && nx < M))
                continue;

            if (visited[ny][nx])
                continue;

            if (board[ny][nx] == 1)
                continue;

            //모든 직사각형 범위에 대해 검사한다.
            if (check(ny, nx, i)) {
                q.push({ {ny,nx}, cnt + 1 });
                visited[ny][nx] = true;
            }

        }
    }

    if (ret == 987654321)
        cout << -1;
    else
        cout << ret;

    return 0;
}



//////////////////////////////////////////////
//가장 위 좌표만 확인. 틀린 코드
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

const int MAX = 1000 + 2;
int N, M;
int H, W;
int board[MAX][MAX];
int start_r, start_c;
int fin_r, fin_c;

bool visited[MAX][MAX];

int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };

bool check(int y, int x, int dir) {
    //위
    if (dir == 0) {
        for (int i = x; i < W; ++i) {
            if (!(0 <= y && y < N && 0 <= i && i < M))
                return false;

            if (visited[y][i])
                return false;

            if (board[y][i] == 1)
                return false;
        }
    }

    //오
    else if (dir == 1) {
        x = x + W - 1;

        for (int i = y; i < H; ++i) {
            if (!(0 <= i && i < N && 0 <= x && x < M))
                return false;

            if (visited[i][x])
                return false;

            if (board[i][x] == 1)
                return false;
        }
    }

    //아래
    else if (dir == 2) {
        y = y + H - 1;
        for (int i = x; i < W; ++i) {
            if (!(0 <= y && y < N && 0 <= i && i < M))
                return false;

            if (visited[y][i])
                return false;

            if (board[y][i] == 1)
                return false;
        }
    }

    //왼
    else if (dir == 3) {
        for (int i = y; i < H; ++i) {
            if (!(0 <= i && i < N && 0 <= x && x < M))
                return false;

            if (visited[i][x])
                return false;

            if (board[i][x] == 1)
                return false;
        }
    }

    return true;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            cin >> board[i][j];

    cin >> H >> W >> start_r >> start_c >> fin_r >> fin_c;
    start_r -= 1; start_c -= 1;
    fin_r -= 1; fin_c -= 1;

    queue<pair<pair<int, int>, int>> q;
    q.push({ { start_r,start_c }, 0 });
    visited[start_r][start_c] = true;
    int ret = 987654321;


    while (!q.empty()) {
        int y = q.front().first.first;
        int x = q.front().first.second;
        int cnt = q.front().second;
        q.pop();

        //가장 왼쪽 위칸이 fin이랑 같으면 종료
        if (y == fin_r && x == fin_c) {
            ret = min(ret, cnt);
            break;
        }

        //4방향 검사
        for (int i = 0; i < 4; ++i) {
            int ny = y + dy[i];
            int nx = x + dx[i];

            //모든 직사각형 범위에 대해 검사한다.
            if (check(ny, nx, i)) {
                q.push({ {ny,nx}, cnt + 1 });
                visited[ny][nx] = true;
            }

        }
    }

    if (ret == 987654321)
        cout << -1;
    else
        cout << ret;

    return 0;
}