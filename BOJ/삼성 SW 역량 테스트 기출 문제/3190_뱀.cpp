/*
머리와 꼬리가 있다는 것을 보고 덱을 사용하면 되겠다고 생각했다.
덱은 front, back 둘 다 삽입과 삭제가 가능해서 좋을 것 같았다.

뱀이 이동할때 좌표설정을 해주는 것과 뱀의 몸통을 표시하는 것에서 조금 헤맸지만
머리와 꼬리가 같을때만 예외처리해줘서 잘 넘어갔다.

문제는 방향 전환이 다 끝난 후에도 게임이 끝나지 않았으면 해당 방향으로 계속 이동해야 했다.
일단 L번 뱀이 이동하고 그 이후에는 무한루프를 돌려서 move(-1)을 하면 ret과 -1이 같을 수 없기 때문에
게임이 끝날때 까지 뱀이 이동할 수 있다.


다른 사람의 풀이를 보니 방향을 변환하는 것도 모듈러 연산을 이용해 더 짧게 구현할 수 있었다.
또한 초기 뱀을 저장할 때 머리만 (0,0)을 덱에 넣고 진행해도 됐었다.
그러면 머리와 꼬리가 같은 경우를 나누지 않고 사과를 먹었는지 안먹었는지만 고려하기 때문에 더 짧은 코드가 나왔다.
*/

// 2021.07.30 확실히 첫 풀이보다 더 간단하게 풀 수 있었다. 머리 하나로 시작해서 사과가 있으면 이동한 좌표를 삽입하고
// 사과가 없으면 꼬리를 하나씩 없애는 것으로 구현했다. 머리를 이동하기전에 꼬리부터 없애고 머리를 이동해야 사과 여부를 확인할 수 있다.
// 초와 방향은 벡터에 저장하고 하나씩 꺼냈는데 시간이 똑같을 때 까지 이동하도록 구현하는 것이 더 좋은 것 같다.
#include <iostream> 
#include <vector> 
#include <algorithm>
#include <deque>
using namespace std;

struct snake {
    int y, x;
};

const int MAX = 100 + 2;
int N, K, L;
int board[MAX][MAX];

int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };
vector<pair<int, char>> v;

int cnt;

void move_snake() {
    deque<snake> dq;
    dq.push_back({ 0,0 });
    board[0][0] = -1;
    int idx = 0;    //방향 바꾸는 벡터 인덱스
    int dir = 1;    // 뱀 방향
    while (1) {
        snake head = dq.front();

        // 특정 초에 방향 바꾼다.
        // idx<L을 안해주면 v[idx].first에서 idx가 벡터크기를 벗어날때 에러가 난다.
        if (idx < L && cnt == v[idx].first) {
            if (v[idx].second == 'L')
                dir = (dir + 3) % 4;
            else
                dir = (dir + 1) % 4;
            idx++;
        }
        cnt++;

        head.y += dy[dir];
        head.x += dx[dir];

        // 벽에 부딪히면 끝
        if (!(head.y >= 0 && head.y < N && head.x >= 0 && head.x < N)) {
            cout << cnt;
            return;
        }
        // 몸과 부딪히면 끝
        if (board[head.y][head.x] == -1) {
            cout << cnt;
            return;
        }

        // 움직인 머리에 사과가 없으면 꼬리 감소
        if (board[head.y][head.x] == 0) {
            board[dq.back().y][dq.back().x] = 0;
            dq.pop_back();
        }

        // 머리는 움직임
        // 머리부터 움직이면 움직인 머리에 사과가 있는지 없는지 여부를 확인할 수 없다.
        dq.push_front({ head.y, head.x });
        board[head.y][head.x] = -1;
    }

}

int main(int argc, char** argv) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> K;
    for (int i = 0; i < K; ++i) {
        int y, x;
        cin >> y >> x;
        board[y - 1][x - 1] = 1;    //사과
    }

    cin >> L;
    for (int i = 0; i < L; ++i) {
        int sec;
        char ch;
        cin >> sec >> ch;
        v.push_back({ sec,ch });
    }

    move_snake();

    return 0;
}



/////////////////////////
// 첫 풀이
#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
using namespace std;

const int MAX = 100 + 1;
int N, K, L;
int board[MAX][MAX];

deque<pair<int, int>> snake;    //뱀 몸통. 머리와 꼬리를 위해 덱 사용
int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };
int ret;    //전체 초
int dir;  //뱀이 향하는 방향
bool fin;   //게임 끝났는지 여부

 //보드 벗어나거나 몸통이랑 부딪히면 종료
bool finished(int y, int x) {
    if (y < 0 || y >= N || x < 0 || x >= N) {
        return true;
    }
    if (board[y][x] == 2)
        return true;
    return false;
}

//뱀 이동
void move(int sec) {
    while (ret != sec) {
        //머리부터 이동 시작
        int head_y = snake.front().first;
        int head_x = snake.front().second;

        //뱀의 머리 이동
        head_y += dy[dir];
        head_x += dx[dir];
        ret++;

        //게임 끝인지 확인
        if (finished(head_y, head_x)) {
            fin = true;
            return;
        }

        //사과먹은 경우
        if (board[head_y][head_x] == 1) {
            //머리와 꼬리가 같은 경우
            if (snake.front().first == snake.back().first &&
                snake.front().second == snake.back().second) {
                snake.pop_front();
                board[head_y][head_x] = 2;
                snake.push_front({ head_y,head_x });
            }
            //다르면 새로운 머리만 삽입
            else {
                board[head_y][head_x] = 2;
                snake.push_front({ head_y, head_x });
            }


        }
        else {
            //머리와 꼬리가 같은 경우
            if (snake.front().first == snake.back().first &&
                snake.front().second == snake.back().second) {
                snake.pop_front();
                board[head_y][head_x] = 2;
                snake.push_front({ head_y,head_x });

                board[snake.back().first][snake.back().second] = 0;
                snake.pop_back();
                snake.push_back({ head_y,head_x });
            }

            else {
                //뱀 머리 좌표 갱신
                board[head_y][head_x] = 2;
                snake.push_front({ head_y, head_x });

                //꼬리만 삭제한다.
                board[snake.back().first][snake.back().second] = 0;
                snake.pop_back();
            }
        }

    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> K;
    for (int i = 0; i < K; ++i) {
        int r, c;
        cin >> r >> c;
        r -= 1; c -= 1;
        board[r][c] = 1;
    }

    //첫 머리, 꼬리 삽입
    snake.push_front({ 0,0 });
    snake.push_back({ 0,0 });
    board[0][0] = 2;
    dir = 1;  //뱀의 첫 방향

    cin >> L;

    for (int i = 0; i < L; ++i) {
        int sec;
        char d;
        cin >> sec >> d;

        //sec초까지 계속 이동
        move(sec);

        //벽 또는 자기자신과 부딪혔다. 게임 끝
        if (fin) {
            cout << ret;
            return 0;
        }

        //방향 전환
        if (d == 'L' && dir == 0)
            dir = 3;

        else if (d == 'D' && dir == 0)
            dir = 1;

        else if (d == 'L' && dir == 1)
            dir = 0;

        else if (d == 'D' && dir == 1)
            dir = 2;

        else if (d == 'L' && dir == 2)
            dir = 1;

        else if (d == 'D' && dir == 2)
            dir = 3;

        else if (d == 'L' && dir == 3)
            dir = 2;

        else if (d == 'D' && dir == 3)
            dir = 0;
    }

    //방향 변환 모두 끝난 후에 계속 이동
    while (1) {
        //sec=-1로 하면 ret과 같을 일이 없다.
        move(-1);
        //벽 또는 자기자신과 부딪혔다. 게임 끝
        if (fin)
            break;
    }

    cout << ret;

    return 0;
}



////////////////////////////////////////
//다른사람 풀이
#include <iostream>  
#include <queue>
using namespace std;
#define N_MAX 100 + 1

enum {
    UP, RIGHT, DOWN, LEFT
};
int board[N_MAX][N_MAX] = { 0 };
int dx[4] = { -1, 0 , 1, 0 };
int dy[4] = { 0, 1, 0, -1 };
deque<pair<int, int>> snake;
int now_direction = RIGHT;
int N, time = 0;

void change_direction(char _way) {
    switch (_way) {
    case 'L':
        now_direction = (now_direction + 3) % 4;
        break;
    case 'D':
        now_direction = (now_direction + 1) % 4;
        break;
    }
}

bool is_can_move() {
    pair<int, int> before_top = snake.front();
    int now_x = before_top.first + dx[now_direction];
    int now_y = before_top.second + dy[now_direction];
    // 더 이상 못 움직이면 0 리턴 
    if (now_x < 1 || now_x > N || now_y < 1 || now_y > N) return false;
    if (board[now_x][now_y] == -1) return false;

    snake.push_front({ now_x, now_y });
    // 사과 없으면
    if (board[now_x][now_y] != 1) {
        board[snake.back().first][snake.back().second] = 0;
        snake.pop_back();
    }
    board[now_x][now_y] = -1;
    return true;
}

int main() {
    snake.push_back({ 1,1 }); board[1][1] = -1;
    int K; scanf("%d %d", &N, &K);
    for (int K_idx = 0; K_idx < K; K_idx++) {
        int row, col; scanf("%d %d", &row, &col);
        board[row][col] = 1;
    }
    // 이동하는 조건에 맞춰서 이동
    int L; scanf("%d", &L);
    for (int L_idx = 0; L_idx < L; L_idx++) {
        int X, C; scanf("%d %c", &X, &C);
        while (time != X) {
            if (is_can_move() == false) {
                printf("%d", time + 1);
                return 0;
            }
            time++;
        }
        change_direction(C);
    }
    // 이동 조건이 다 끝났으면 현재 방향 상태로 이동 
    while (1) {
        if (is_can_move() == false) {
            printf("%d", time + 1);
            return 0;
        }
        time++;
    }
    return 0;
}
