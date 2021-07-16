/*
거의 다 해결해는데 인덱스 설정을 해결하지 못했다.

문제에 맞게 구현은 잘했는데 파이어볼을 이동할때 처음과 끝이 연결되어 있어
범위를 벗어나면 다시 범위 안으로 잡아줘야 했다.

처음에는 방향x속력만큼 계산해서 %N을 했는데 음수가 나올 수 있기 때문에 런타임 에러를 받았다.
이걸 해결하기 위해 이리저리 머리 굴렸는데 마땅한 식이 생각 안났다.

다른 사람 풀이를 보니 속도만큼 반복문 돌면서
-1이면 N-1로, N이면 0으로 좌표를 설정하면 끝이었다.

너무 어렵게 생각해서 풀지 못한 것 같다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;

const int MAX = 50 + 4;
int N, M, K;

struct fireball {
    int kg; //질량
    int velocity;   //속력
    int dir;    //방향
};

vector<fireball> board[MAX][MAX];
vector<fireball> copy_board[MAX][MAX];

int dy[8] = { -1,-1,0,1,1,1,0,-1 };
int dx[8] = { 0,1,1,1,0,-1,-1,-1 };

void copy() {
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            board[i][j] = copy_board[i][j];
}

//파이어볼 이동
void move() {
    int y = 0, x = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            //파이어볼이 없으면 다음 칸 진행
            if (board[i][j].empty())
                continue;

            //현재 파이어볼의 좌표와 질량, 속력, 방향을 이동한 좌표에 저장
            for (int k = 0; k < board[i][j].size(); ++k) {
                y = i; x = j;
                int m = board[i][j][k].kg;
                int v = board[i][j][k].velocity;
                int d = board[i][j][k].dir;

                //첫행과 끝행, 첫열과 끝열이 연결되어 있다
                for (int l = 0; l < v; ++l) {
                    y += dy[d];
                    if (y == N)
                        y = 0;
                    else if (y == -1)
                        y = N - 1;

                    x += dx[d];
                    if (x == N)
                        x = 0;
                    else if (x == -1)
                        x = N - 1;
                }
                copy_board[y][x].push_back({ m,v,d });
            }
            board[i][j].clear();

        }
    }
}

//2개 이상 파이어볼 처리
void add_fireball() {
    //floor()쓰면 내림
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            //파이어볼이 없으면 다음 칸 진행
            if (board[i][j].empty())
                continue;

            //1개일 때 다음칸 진행
            if (board[i][j].size() < 2)
                continue;

            //2개 이상인 경우
            int m_sum = 0;
            int v_sum = 0;
            int odd_cnt = 0, even_cnt = 0;
            int fire_size = board[i][j].size();
            for (int k = 0; k < board[i][j].size(); ++k) {
                m_sum += board[i][j][k].kg;   //질량을 다 합한다.
                v_sum += board[i][j][k].velocity;
                odd_cnt += (board[i][j][k].dir % 2 != 0) ? 1 : 0;
                even_cnt += (board[i][j][k].dir % 2 == 0) ? 1 : 0;
            }
            board[i][j].clear();
            //질량이 0이면 소멸
            if (floor(m_sum / 5) == 0) {
                continue;
            }

            //질량은 합쳐진 파이어볼 질량 합/5의 내림값
            m_sum = floor(m_sum / 5);
            //속력은 합쳐진 파이어볼 속력 합/파이어볼 개수 내림 값
            v_sum = floor(v_sum / fire_size);
            //d1은 짝수, d2는 홀수
            int d1 = 0, d2 = 1;
            for (int k = 0; k < 4; ++k) {
                //합쳐지는 파이어볼 방향이 모두 홀수이거나 짝수이면 0,2,4,6
                if (even_cnt == fire_size || odd_cnt == fire_size) {
                    board[i][j].push_back({ m_sum,v_sum,d1 });
                    d1 += 2;
                }

                else {
                    board[i][j].push_back({ m_sum,v_sum,d2 });
                    d2 += 2;
                }

            }


        }
    }
}

int get_sum() {
    int ret = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (board[i][j].empty())
                continue;

            for (int k = 0; k < board[i][j].size(); ++k) {
                ret += board[i][j][k].kg;
            }
        }
    }
    return ret;
}

void init() {
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            copy_board[i][j].clear();
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M >> K;

    for (int i = 0; i < M; ++i) {
        int r, c, m, s, d;
        cin >> r >> c >> m >> s >> d;
        r -= 1; c -= 1;
        board[r][c].push_back({ m,s,d });
    }

    for (int i = 0; i < K; ++i) {
        move(); //모든 파이어볼 이동
        copy(); //copy_board에 있는걸 원래 board로 이동

        init();  //copy_board 초기화. 초기화 안하면 move때 이동한 값들이 그대로 남아있다.
        add_fireball();  //2개 이상 파이어볼 처리
    }

    cout << get_sum();


    return 0;
}