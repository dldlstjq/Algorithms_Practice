/*
해결 못함
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX = 100 + 1;
const int INF = 987654321;
string board[MAX];
int check[MAX][MAX];    //미친 아두이노 중복 체크
typedef struct {
    int y;
    int x;
    bool crash;
}crazy;
crazy info;
int R, C;
vector<crazy> v;
string direction;
bool finish = false;

int dy[9] = { 1,1,1,0,0,0,-1,-1,-1 };
int dx[9] = { -1,0,1,-1,0,1,-1,0,1 };

bool is_in(int y, int x) {
    return 0 <= y && y < R && 0 <= x && x < C;
}

void move_crazy(int y, int x) {
    memset(check, -1, sizeof(check));
    for (int i = 0; i < v.size(); ++i) {

        //폭파된 아두이노는 통과
        if (v[i].crash)
            continue;

        int cy = v[i].y;
        int cx = v[i].x;
        board[cy][cx] = '.';

        int distance = INF;
        int idx = 0;
        //9방향 중 종수 아두이노와 가까운 방향 조사
        for (int k = 0; k < 9; ++k) {
            int next_cy = cy + dy[k];
            int next_cx = cx + dx[k];

            if (is_in(next_cy, next_cx)) {
                if (distance > abs(y - next_cy) + abs(x - next_cx)) {
                    distance = abs(y - next_cy) + abs(x - next_cx);
                    idx = k;
                }
            }
        }

        //이동하려는 칸에 일반 아두이노가 있으면 종료
        if (board[cy + dy[idx]][cx + dx[idx]] == 'I') {
            finish = true;
            break;
        }

        //이동자리에 아두이노가 없으면 자신의 인덱스 저장
        else if (check[cy + dy[idx]][cx + dx[idx]] == -1) {
            check[cy + dy[idx]][cx + dx[idx]] = i;  //체크에 현재 인덱스 저장
            //보드와 좌표 갱신
            v[i].y += dy[idx];
            v[i].x += dx[idx];
        }

        //이동자리에 이미 인덱스가 있으면, 즉 같은 미친 아두이노면 폭파변수 true
        else if (check[cy + dy[idx]][cx + dx[idx]] != -1) {
            v[i].crash = true;
            v[check[cy + dy[idx]][cx + dx[idx]]].crash = true;
        }
    }

    //폭파변수가 true인 좌표는 R을 없앤다.
    for (int j = 0; j < v.size(); ++j) {
        if (v[j].crash)
            board[v[j].y][v[j].x] = '.';
    }
    for (int j = 0; j < v.size(); ++j) {
        if (!v[j].crash)
            board[v[j].y][v[j].x] = 'R';
    }

}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> R >> C;
    int y = 0, x = 0;

    for (int i = 0; i < R; ++i) {
        cin >> board[i];
        for (int j = 0; j < C; ++j) {
            //종수 아두이노 저장
            if (board[i][j] == 'I') {
                y = i, x = j;
                break;
            }
            //미친 아두이노 좌표 저장
            if (board[i][j] == 'R') {
                info.y = i;
                info.x = j;
                info.crash = false;
                v.push_back(info);
            }
        }
    }

    cin >> direction;
    int cnt = 0;

    for (int i = 0; i < direction.length(); ++i) {
        int num = direction[i] - '0';

        //dir 인덱스 0부터 시작하기대문에 맞춰준다.
        board[y][x] = '.';
        y += dy[num - 1];
        x += dx[num - 1];
        cnt++;  //이동횟수 증가

        //이동하려는 칸에 미친 아두이노가 있으면 종료
        if (board[ny][nx] == 'R') {
            finish = true;
            break;
        }

        board[y][x] = 'I';
        move_crazy(y, x);
        //finish true면 빠져나온다.
        //미친 아두이노와 겹친다는 뜻이다.
        if (finish)
            break;
    }
    if (!finish)
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                cout << board[i][j];
            }
            cout << "\n";
        }
    else
        cout << "kraj " << cnt;
    return 0;
}