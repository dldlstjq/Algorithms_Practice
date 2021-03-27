/*
백트래킹을 이용해야 풀리는 문제이다.
빈칸이 있는 곳은 전부 출발하여 모든 곳을 방문할 수 있으면 최소 거리를
아니면 다시 돌아와야 한다.

모든 테스트케이스를 통과했는데 시간초과가 나와서 입력을 바꿔보니
정답을 맞았다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAX = 30 + 1;
const int INF = 987654321;
int N, M;  //보드 크기
char board[MAX][MAX];
bool visited[MAX][MAX];


int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };

int ret;    //결과값 저장
int total;  //빈칸 개수

bool is_in(int y, int x) {
    //범위 벗어나거나 장애물이거나 방문 한 곳이면 false
    if (!(0 <= y && y < N && 0 <= x && x < M))
        return false;
    if (board[y][x] == '*')
        return false;
    if (visited[y][x])
        return false;
    return true;
}


void solve(int y, int x, int move, int cnt) {
    //ret이 기존 것 이상 나오면 종료
    if (move > ret)
        return;

    //모든 빈칸 방문한 경우 이동횟수 최소 반환
    if (cnt == total) {
        ret = min(ret, move);
        return;
    }

    for (int dir = 0; dir < 4; ++dir) {
        int cur = 0;
        int ny = y;
        int nx = x;
        //한 방향으로 계속 이동
        while (1) {
            ny += dy[dir];
            nx += dx[dir];

            //범위 벗어날경우, 장애물, 방문한 곳이면 break
            if (!is_in(ny, nx)) {
                ny -= dy[dir];
                nx -= dx[dir];
                break;
            }
            cur++;  //빈칸 체크. 모든 빈칸 방문했는지 확인 용도
            visited[ny][nx] = true;
        }

        //이동한 좌표가 현재 좌표랑 같으면 다른 방향 탐색
        if (ny == y && nx == x)
            continue;

        //이동좌표, 이동횟수, 빈칸 카운트 넘겨줌
        solve(ny, nx, move + 1, cnt + cur);

        //현재 좌표로 되돌아오면서 visited 초기화
        while (ny != y || nx != x) {
            visited[ny][nx] = false;
            ny -= dy[dir];
            nx -= dx[dir];
        }
    }

}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t = 1;
    while (cin >> N >> M) {
        memset(visited, false, sizeof(visited));
        total = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                cin >> board[i][j];
                //빈칸 갯수 저장
                if (board[i][j] == '.')
                    total++;
            }
        }

        ret = INF;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                //빈칸인 곳 백트래킹
                if (board[i][j] == '.') {
                    visited[i][j] = true;
                    solve(i, j, 0, 1);
                    visited[i][j] = false;
                }
            }
        }

        if (ret == INF)
            cout << "Case " << t++ << ": " << -1 << "\n";
        else
            cout << "Case " << t++ << ": " << ret << "\n";
    }

    return 0;
}