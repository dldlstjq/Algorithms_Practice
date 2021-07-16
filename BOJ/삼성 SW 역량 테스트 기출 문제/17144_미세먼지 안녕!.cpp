/*
문제 이해는 쉽게 됐다. 미세먼지가 퍼지고 줄어드는 양이 이해가 안됐었는데
동시에 퍼진다고 해서 먼지가 증가하는 부분과 퍼져서 감소하는 부분은 따로 처리했다.

공기가 퍼지는 부분은 dfs를 생각했으나 막히기 전까지 한 방향으로만 가야 하기 때문에 쓸 수 없었다.
이 부분은 다른 사람 코드를 보고 알았는데 4방향의 인덱스를 따로 저장해서 사용하면 됐다.
    0     1     2      3
{(-1,0) (0,1) (1,0) (0,-1)}

up[4]={1,0,3,2}로 두면 dir[up[0]]= dir[1]이 되어 (0,1)방향으로 움직이게 된다.

이런식으로 하면 공기 방향을 쉽게 정할 수 있다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int r, c, T;

//방향순서= 북[0] 동[1] 남[2] 서[3] 
int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };

//공기청정기의 방향. 위에건 동 북 서 남 순서로
//아래는 동 남 서 북 방향
int up[4] = { 1,0,3,2 };
int down[4] = { 1,2,3,0 };

int house[50][50];    //현재 상태 저장

vector<pair<int, int>> air;    //공기 청정기 위치

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> r >> c >> T;

    for (int i = 0; i < r; ++i)
        for (int j = 0; j < c; ++j) {
            cin >> house[i][j];
            if (house[i][j] == -1)
                air.push_back({ i,j });
        }

    //t초 동안 발생
    for (int t = 0; t < T; ++t) {
        queue<pair<int, int>> q;
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                //미세먼지가 있는 곳
                if (house[i][j] != -1 && house[i][j] != 0)
                    q.push({ i,j });
            }
        }
        int copy[50][50] = { 0 };

        while (!q.empty()) {
            int y = q.front().first;
            int x = q.front().second;
            q.pop();

            int cnt = 0;
            //미세먼지가 퍼지는 방향 갯수를 cnt에 저장
            for (int j = 0; j < 4; ++j) {
                int ny = y + dy[j];
                int nx = x + dx[j];
                if (0 <= ny && ny < r && 0 <= nx && nx < c) {
                    if (house[ny][nx] != -1) {
                        cnt++;
                        //미세먼지가 동시에 퍼지기 때문에 미세먼지가 있는 곳에 퍼진 것을 더하면 정확한 값이 안나온다.
                        //퍼진 양은 따로 저장해뒀다가 나중에 한꺼번에 처리.
                        copy[ny][nx] += house[y][x] / 5;
                    }

                }
            }
            //원래 있던 미세먼지 양이 줄어든다.
            house[y][x] -= (house[y][x] / 5) * cnt;
        }

        //미세먼지가 퍼진 곳을 더해서 값을 갱신한다.
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                if (house[i][j] != -1)
                    house[i][j] += copy[i][j];
            }
        }


        //공기청정기 윗부분. 시작위치에서 행을 한 칸 옮겨 공기방향 시작 좌표를 만든다. 
        int y = air[0].first;
        int x = air[0].second + 1;

        for (int i = 0; i < r; ++i)
            for (int j = 0; j < c; ++j)
                copy[i][j] = house[i][j];

        house[y][x] = 0;  //바람이 제일 처음 닿는 곳은 0
        for (int i = 0; i < 4; ++i) {
            while (1) {
                int ny = y + dy[up[i]];
                int nx = x + dx[up[i]];

                //원래 공기청정기 위치에 오면 스탑
                if (ny == air[0].first && nx == air[0].second)
                    break;
                //범위 벗어나도 스탑
                if (!(0 <= ny && ny < r && 0 <= nx && nx < c))
                    break;
                house[ny][nx] = copy[y][x];
                y = ny;
                x = nx;

            }
        }

        //공기청정기 아래. 시작위치에서 행을 한 칸씩 옮겨 공기방향 시작 좌표를 만든다. 
        y = air[1].first;
        x = air[1].second + 1;

        for (int i = 0; i < r; ++i)
            for (int j = 0; j < c; ++j)
                copy[i][j] = house[i][j];

        house[y][x] = 0;  //바람이 제일 처음 닿는 곳은 0
        for (int i = 0; i < 4; ++i) {
            while (1) {
                int ny = y + dy[down[i]];
                int nx = x + dx[down[i]];

                //원래 공기청정기 위치에 오면 스탑
                if (ny == air[1].first && nx == air[1].second)
                    break;
                //범위 벗어나도 스탑
                if (!(0 <= ny && ny < r && 0 <= nx && nx < c))
                    break;
                //한칸씩 옮겨준다.
                house[ny][nx] = copy[y][x];
                //좌표 갱신
                y = ny;
                x = nx;

            }
        }
    }

    //미세먼지 양
    int ret = 0;
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (house[i][j] != -1)
                ret += house[i][j];
        }
    }
    cout << ret;

    return 0;
}