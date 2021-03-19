/*
문제자체는 쉽게 이해했는데 구현에서 시간이 많이 걸렸다.
상어 한 마리당 저장해야할 변수가 속도, 이동방향, 크기였기 때문에
나무 재테크 문제처럼 2차원 배열에 pair를 사용해서 상어를 저장했다.

변수 저장까지는 좋았는데 상어의 이동이 문제였다.
한 방향으로 이동하다 벽에 닿으면 다시 방향을 바꿔서 돌아와야 했고
겹치게 되면 크기가 큰 것만 살아남는다.
이동한 후의 좌표를 저장하기 위해 별도로 벡터하나를 더 선언하고 거기다 저장해서
shark에 새로 복사하는 방식으로 접근했다.

또한 방향 바꾸는 방식도 범위를 벗어난 경우 다시 돌아와야 했는데 그냥 끝에 닿을 경우에
방향을 바꾸도록 구현하니 정확한 답이 안나왔다.

다른 사람 풀이를 참고하여 상어의 이동은 큐를 이용하여 별도의 벡터가 필요없었다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int R, C, M;
int r, c, s, d, z;

vector<pair<int, pair<int, int>>> shark[110][110];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> R >> C >> M;

    for (int i = 0; i < M; ++i) {
        cin >> r >> c >> s >> d >> z;
        //속력, 이동방향, 크기 순으로 저장
        shark[r][c].push_back({ s, {d,z} });
    }

    int ret = 0;
    int cur = 0;
    //열의 갯수만큼 진행
    for (int i = 0; i < C; ++i) {
        cur++;
        //한 열에 먼저 있는 상어를 잡는다.
        for (int j = 1; j <= R; ++j) {
            //상어가 있으면 잡는다.
            if (shark[j][cur].size()) {
                int size = shark[j][cur][0].second.second;
                ret += size;
                //잡은 상어는 사라진다.
                shark[j][cur].clear();
                break;
            }
        }

        queue<pair<pair<int, int>, pair<int, pair<int, int>>>> q;
        for (int k = 1; k <= R; ++k)
            for (int l = 1; l <= C; ++l)
                //이동안한 상어를 이동시킨다.
                //큐에 상어정보를 저장한다.
                if (shark[k][l].size()) {
                    q.push({ { k,l }, { shark[k][l][0] } });
                    shark[k][l].clear();
                }

        //상어가 움직인다.
        while (!q.empty()) {
            //현재 상어의 위치
            int y = q.front().first.first;
            int x = q.front().first.second;
            //속력, 방향, 크기
            int speed = q.front().second.first;
            int dir = q.front().second.second.first;
            int size = q.front().second.second.second;

            q.pop();
            for (int sp = 0; sp < speed; ++sp) {
                //방향따라 좌표를 설정해주고 범위 밖으로 나간경우 방향과 좌표를 맞게 바꿔준다.
                if (dir == 1) {
                    y = y - 1;
                    //끝에 도착하면 방향을 바꿔준다.
                    if (y == 0) {
                        dir = 2;
                        y = y + 2;
                    }

                }
                else if (dir == 2) {
                    y = y + 1;
                    if (y == R + 1) {
                        dir = 1;
                        y = y - 2;
                    }

                }
                else if (dir == 3) {
                    x = x + 1;
                    if (x == C + 1) {
                        dir = 4;
                        x = x - 2;
                    }

                }
                else if (dir == 4) {
                    x = x - 1;
                    if (x == 0) {
                        dir = 3;
                        x = x + 2;
                    }

                }
            }
            //해당 칸에 상어가 있으면 큰 크기의 상어가 잡아먹는다.
            if (shark[y][x].size()) {
                if (shark[y][x][0].second.second < size) {
                    shark[y][x].clear();
                    shark[y][x].push_back({ speed, {dir,size} });
                }

            }
            //없으면 그대로 추가
            else
                shark[y][x].push_back({ speed, {dir,size} });
        }

    }
    cout << ret;
    return 0;
}