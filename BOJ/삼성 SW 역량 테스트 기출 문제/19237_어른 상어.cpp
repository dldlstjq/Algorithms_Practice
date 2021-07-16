/*
원래 풀기로 했던 1시간 30분을 넘겨 두시간 가까이 됐는데 해결하기는 했다.
처음에 방향 우선순위 저장부분에서 어떤 자료구조를 써야 할지 오래 걸렸다.

상어의 수인 M개 배열 안에 4개의 배열이 필요하고 그 배열 안에 4방향을 저장해야 했다.
따라서 방향 우선순위를 저장하는 구조체를 만들고 2중 벡터를 선언해 해결했다.

상어의 번호를 저장하는 board와 번호와 냄새를 저장하는 shark 두 배열을 동시에 이용했다.

1. 모든 상어는 동시에 움직인다.
-> 먼저 이동시킨 후 겹치는 경우를 처리해도 되는데 헷갈려서 다음 이동할 좌표를 따로 저장해서 한꺼번에 처리했다.
-> 빈칸을 먼저 가야하지만 빈칸이 없는 경우 자기 냄새가 있는 곳으로 가야한다.
하지만 자기냄새가 있는 곳도 우선순위가 있기 때문에 이걸 고려해줘야 한다.

2. 겹칠 경우 번호가 작은 상어가 살아남는다.
-> next_loc에 이동할 좌표를 저장하여 상어가 없으면 집어넣고 있으면 번호비교해서 값을 변경했다.

3. 냄새가 사라진다.
-> 현재 위치에 board와 shark 둘 다 상어 번호가 있으면 감소하지 않고 shark에만 있는 경우 냄새를 감소시킨다.
냄새가 0이 되면 다 초기화 해준다.

방향 우선순위를 저장하는 것, 상어가 움직일 때 우선순위를 고려하는 것, 동시에 있을 때 어떤 상어가 살아남는지를 
다 고려해야해서 조금 까다로웠던 것 같다. 그래도 청소년상어보다는 나름 풀만한 것 같다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAX = 20 + 2;
int N, M, k;
int board[MAX][MAX];

struct adult_shark {
    int num;
    int scent;
};
adult_shark shark[MAX][MAX];

//상어 방향 저장
int shark_dir[MAX * MAX + 1];
//상어 잡아 먹혔는지 여부
bool is_shark[MAX * MAX + 1];

int dy[5] = { 0,-1,1,0,0 };
int dx[5] = { 0,0,0,-1,1 };

//방향 우선순위 저장
struct dir_priority {
    int dir[4];
};
vector<vector<dir_priority>> v;

vector<pair<int, int>> next_loc;    //상어가 이동할 다음 좌표

bool is_in(int y, int x) {
    return 0 <= y && y < N && 0 <= x && x < N;
}

void move() {
    next_loc.clear();
    next_loc.resize(M + 1);

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            //어떤 상어도 없으면 통과
            if (board[i][j] == 0)
                continue;

            //상어는 동시에 이동한다. 
            int shark_num = shark[i][j].num;
            int now_dir = shark_dir[shark_num];

            bool empty = false;
            int self_scent = 0;
            for (int a = 0; a < 4; ++a) {
                //우선순위에 따른 방향
                int go = v[shark_num][now_dir].dir[a];
                int ny = i + dy[go];
                int nx = j + dx[go];
                //범위 아웃
                if (!is_in(ny, nx))
                    continue;

                //자기 냄새와 같을 경우
                if (shark[ny][nx].num == shark_num) {
                    //우선순위가 높은 방향을 저장
                    //한 번 저장 됐기 때문에 다른 방향에 자기 냄새가 있더라도 그 방향은 저장 안함
                    if (self_scent == 0)
                        self_scent = go;
                }

                //아무 냄새가 없다
                if (shark[ny][nx].num == 0) {
                    empty = true;
                    next_loc[shark_num].first = ny;
                    next_loc[shark_num].second = nx;

                    shark_dir[shark_num] = go;

                    //이전 위치는 0
                    board[i][j] = 0;
                    break;
                }

            }

            //빈 칸이 없으면 자기 냄새가 있는 쪽으로 이동
            if (!empty) {
                if (self_scent != 0) {
                    int ny = i + dy[self_scent];
                    int nx = j + dx[self_scent];
                    next_loc[shark_num].first = ny;
                    next_loc[shark_num].second = nx;

                    shark_dir[shark_num] = self_scent;

                    //이전 위치는 0
                    board[i][j] = 0;
                }


            }

        }
    }

    //냄새 퍼트림
    for (int i = 1; i <= M; ++i) {
        int y = next_loc[i].first;
        int x = next_loc[i].second;

        //상어가 잡아먹혔으면 패스
        if (!is_shark[i])
            continue;

        //냄새가 없거나 자기 냄새이면 이동
        if (board[y][x] == 0 || shark[y][x].num == i) {
            board[y][x] = i;    //새로운 방향에 상어번호 표시
            shark[y][x].num = i;    //해당 위치에 상어 냄새와 번호
            shark[y][x].scent = k;
        }

        else {
            //기존에 상어보다 새로 들어오는게 작으면 잡아먹음
            if (board[y][x] > i) {
                is_shark[board[y][x]] = false;  //원래 있던 상어 잡아먹힘
                board[y][x] = i;
                shark[y][x].num = i;
                shark[y][x].scent = k;

            }
            //원래 있던게 작으면 패스
            else {
                is_shark[i] = false;
                continue;
            }

        }

    }
}

void decrease() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            //상어는 없고 냄새만 있으면 1 감소
            if (board[i][j] == 0 && shark[i][j].num != 0) {
                shark[i][j].scent--;
                //냄새가 0이 되면 사라짐
                if (shark[i][j].scent == 0) {
                    shark[i][j].num = 0;
                    shark[i][j].scent = 0;
                }
            }

        }
    }
}

//1번 상어만 남았는지 확인
bool only_one() {
    //0인 부분은 통과하고 1이 아닌 다른 상어가 있으면 실패
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (board[i][j] == 0)
                continue;
            else if (board[i][j] != 0 && board[i][j] != 1)
                return false;
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M >> k;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> board[i][j];
            if (board[i][j] != 0) {
                shark[i][j].num = board[i][j];
                shark[i][j].scent = k;
            }

        }

    }


    //상어 초기 방향
    for (int i = 1; i <= M; ++i) {
        int d;
        cin >> d;
        shark_dir[i] = d;
    }

    //상어 방향 우선순위
    v.resize(M + 1);
    for (int i = 1; i <= M; ++i)
        v[i].resize(5);


    for (int i = 1; i <= M; ++i) {
        //상어가 모두 남아 있다
        is_shark[i] = true;
        //방향 저장
        for (int j = 1; j <= 4; ++j) {
            for (int l = 0; l < 4; ++l) {
                int d;
                cin >> d;
                v[i][j].dir[l] = d;

            }
        }
    }

    int time = 1;
    bool flag = false;
    while (time <= 1000) {
        //상어 이동
        move();
        //냄새 감소
        decrease();

        //1번 상어만 남으면 종료
        if (only_one()) {
            flag = true;
            break;
        }
        time++;
    }

    if (flag)
        cout << time;
    else
        cout << -1;
    return 0;
}