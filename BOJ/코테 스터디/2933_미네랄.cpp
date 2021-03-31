/*
첫 접근 방법은 미네랄의 클러스터를 번호별로 구분했고 구분한 클러스터를 별도의 2차원 배열에 저장했다
미네랄을 지우면서 해당 클러스터의 미네랄 개수와 전체 미네랄 개수를 구분하려고 했는데 앞뒤가 잘 안맞았다.
밑으로 내리는 것도 미네랄의 좌표를 모두 알고 있어야해서 따로 저장을 해야 했다.

2~3시간 고민하다가 결국 해결하지 못했다.
다른 사람 풀이를 보니 클러스터별로 구분하지 않아도 됐고 미네랄이 하나만 파괴되기 때문에 그와 연결된 클러스터만 확인해서
밑에 붙어있으면 패스, 없으면 따로 저장해서 한칸씩 내리면 됐다.

클러스터가 하나가 아닐 수도 있다는 걸 생각하다보니 각 클러스터별로 어떻게 처리해야 하는지 생각이 안나서
코드가 많이 복잡해지고 못풀었던 것 같다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAX = 100 + 1;
int R, C;
char cave[MAX][MAX];    //동굴
int N;
bool visited[MAX][MAX];

int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };

vector<pair<int, int>> cluster;   //클러스터 번호, 미네랄 개수 페어로 저장ㄴ
bool flag;  //맨 밑에 미네랄이 있는지 여부


//클러스터 확인
void dfs(int y, int x) {
    //클러스터 중 미네랄이 하나라도 밑에 닿아있으면 ok
    visited[y][x] = true;
    if (y == R - 1) {
        flag = true;
        return;
    }
    for (int i = 0; i < 4; ++i) {
        int ny = y + dy[i];
        int nx = x + dx[i];
        if (0 <= ny && ny < R && 0 <= nx && nx < C) {
            if (cave[ny][nx] == 'x' && !visited[ny][nx]) {
                cluster.push_back({ ny,nx });
                dfs(ny, nx);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> R >> C;
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            cin >> cave[i][j];
        }
    }

    cin >> N;
    for (int i = 0; i < N; ++i) {
        int num;
        cin >> num;

        int y = R - num;
        int x = -1;
        //왼쪽
        if (i % 2 == 0) {
            for (int j = 0; j < C; ++j) {
                //막대기가 미네랄과 마주치면 미네랄 파괴
                if (cave[y][j] == 'x') {
                    x = j;
                    break;
                }
            }
        }
        //오른쪽
        else {
            for (int j = C - 1; j >= 0; --j) {
                //막대기가 미네랄과 마주치면 미네랄 파괴
                if (cave[y][j] == 'x') {
                    x = j;
                    break;
                }
            }
        }

        //미네랄 없으면 통과
        if (x == -1)
            continue;
        cave[y][x] = '.';

        for (int k = 0; k < 4; ++k) {
            int ny = y + dy[k];
            int nx = x + dx[k];

            //범위 벗어나거나 미네랄이 아니면 패스
            if (!(0 <= ny && ny < R && 0 <= nx && nx < C))
                continue;
            if (cave[ny][nx] == '.')
                continue;

            memset(visited, false, sizeof(visited));
            cluster.clear();
            flag = false;

            //클러스터 확인한다.
            cluster.push_back({ ny,nx });
            dfs(ny, nx);

            //하나라도 바닥에 닿아있으면 ok
            if (flag)
                continue;

            //밑에 떨어질때 까지 내린다
            while (1) {
                bool is_down = true;
                //기존 클러스터인 곳 전부 . 표시
                for (int j = 0; j < cluster.size(); ++j) {
                    cave[cluster[j].first][cluster[j].second] = '.';
                }

                //한 칸씩 내려본다.
                for (int j = 0; j < cluster.size(); ++j) {
                    int new_y = cluster[j].first + 1;
                    int new_x = cluster[j].second;

                    //한칸 내린곳이 범위 벗어나거나 미네랄이 있으면 break
                    if (new_y == R || cave[new_y][new_x] == 'x') {
                        is_down = false;
                        break;
                    }
                }

                for (int j = 0; j < cluster.size(); ++j) {
                    //바닥이 아니면 한 칸씩 내리기
                    if (is_down)
                        cluster[j].first++;
                    cave[cluster[j].first][cluster[j].second] = 'x';
                }
                if (!is_down)
                    break;
            }
        }

    }

    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            cout << cave[i][j];
        }
        cout << "\n";
    }
    return 0;
}