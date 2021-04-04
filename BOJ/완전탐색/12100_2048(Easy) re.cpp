/*
구슬 탈출 2랑 비슷하게 생각했는데 딱히 풀이가 떠오르지 않았다.
bfs, dfs 둘 다 써야하고 블록이 합쳐지는 것, 한번 합쳐지면 다시 합쳐지지 않는다를 구현하는게 쉽지 않았다.
구조체를 생각해서 하기도 했는데 복잡해지는 것 같아 안됐다.

2021.04.04
solve 함수 내에서 배열을 복사할때 copyboard를 전역으로 선언하면 제대로 된 값이 안나온다.
아마 전역으로 선언하면 이전 데이터 값이 계속 저장되어서 그런것 같다.
그리고 블록을 계산하는 move도 로직을 비슷하게 짰는데 시간초과가 났다.
어느 부분에서 시간초과가 났는지는 모르겠다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int N;
const int MAX = 20 + 1;
int board[MAX][MAX];

int ret;

int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };

void move(int d) {
    queue<int> q;
    switch (d) {
        //위쪽
    case 0:
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                //0이 아닌 부분은 큐에 넣고 보드를 0으로 만든다.
                if (board[j][i])
                    q.push(board[j][i]);
                board[j][i] = 0;
            }

            int idx = 0;
            //보드가 비었다면 빈 곳에 숫자를 넣어주고
            //숫자가 같으면 더하고 인덱스를 조정한다.
            //이미 숫자가 존재하면 그 다음 좌표에 숫자를 넣는다.
            while (!q.empty()) {
                int num = q.front();
                q.pop();

                if (board[idx][i] == 0)
                    board[idx][i] = num;
                else if (board[idx][i] == num) {
                    board[idx][i] *= 2;
                    idx++;
                }
                else {
                    idx++;
                    board[idx][i] = num;
                }
            }
        }
        break;
        //아래쪽
    case 2:
        for (int i = 0; i < N; ++i) {
            for (int j = N - 1; j >= 0; --j) {
                //0이 아닌 부분은 큐에 넣고 보드를 0으로 만든다.
                if (board[j][i])
                    q.push(board[j][i]);
                board[j][i] = 0;
            }

            int idx = N - 1;
            //보드가 비었다면 빈 곳에 숫자를 넣어주고
            //숫자가 같으면 더하고 인덱스를 조정한다.
            //이미 숫자가 존재하면 그 다음 좌표에 숫자를 넣는다.
            while (!q.empty()) {
                int num = q.front();
                q.pop();

                if (board[idx][i] == 0)
                    board[idx][i] = num;
                else if (board[idx][i] == num) {
                    board[idx][i] *= 2;
                    idx--;
                }
                else {
                    idx--;
                    board[idx][i] = num;
                }
            }
        }
        break;
        //오른쪽
    case 1:
        for (int i = 0; i < N; ++i) {
            for (int j = N - 1; j >= 0; --j) {
                //0이 아닌 부분은 큐에 넣고 보드를 0으로 만든다.
                if (board[i][j])
                    q.push(board[i][j]);
                board[i][j] = 0;
            }

            int idx = N - 1;
            //보드가 비었다면 빈 곳에 숫자를 넣어주고
            //숫자가 같으면 더하고 인덱스를 조정한다.
            //이미 숫자가 존재하면 그 다음 좌표에 숫자를 넣는다.
            while (!q.empty()) {
                int num = q.front();
                q.pop();

                if (board[i][idx] == 0)
                    board[i][idx] = num;
                else if (board[i][idx] == num) {
                    board[i][idx] *= 2;
                    idx--;
                }
                else {
                    idx--;
                    board[i][idx] = num;
                }
            }
        }
        break;
        //왼쪽
    case 3:
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                //0이 아닌 부분은 큐에 넣고 보드를 0으로 만든다.
                if (board[i][j])
                    q.push(board[i][j]);
                board[i][j] = 0;
            }

            int idx = 0;
            //보드가 비었다면 빈 곳에 숫자를 넣어주고
            //숫자가 같으면 더하고 인덱스를 조정한다.
            //이미 숫자가 존재하면 그 다음 좌표에 숫자를 넣는다.
            while (!q.empty()) {
                int num = q.front();
                q.pop();

                if (board[i][idx] == 0)
                    board[i][idx] = num;
                else if (board[i][idx] == num) {
                    board[i][idx] *= 2;
                    idx++;
                }
                else {
                    idx++;
                    board[i][idx] = num;
                }
            }
        }
        break;
    }


}

//같은 값을 갖는 두 블록이 충돌하면 두 블록은 하나로 합쳐지게 된다. 
//한 번의 이동에서 이미 합쳐진 블록은 또 다른 블록과 다시 합쳐질 수 없다.
void solve(int cnt) {

    if (cnt == 5) {
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                ret = max(ret, board[i][j]);
        return;
    }

    int copyboard[MAX][MAX];
    //현재 보드 상태 저장
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            copyboard[i][j] = board[i][j];

    for (int d = 0; d < 4; ++d) {
        move(d);
        solve(cnt + 1);
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                board[i][j] = copyboard[i][j];
    }

}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            cin >> board[i][j];

    solve(0);
    cout << ret;
    return 0;
}