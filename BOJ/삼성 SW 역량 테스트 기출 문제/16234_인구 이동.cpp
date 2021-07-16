/*
처음에 문제 이해에 시간이 걸렸다. 직접 손으로 풀어보고 나서야 뭘 구해야 할지 알았다.
bfs 또는 dfs를 사용하여 L과 R 사이에 들어오는 차이면 나라 수와 인구수를 더해주고 나눠준다.
그리고 카운트를 해줘서 몇 번의 인구이동이 되는지 구하면 된다.

문제이해에 어려움을 겪었고 인구이동 종료조건을 설정하는데 애를 먹었다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

int N, R, L;
int board[101][101];

int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };

bool visited[101][101];
vector<pair<int, int>> uni; //연합이 되는 나라의 좌표 저장
int people, num;    //인구 수, 연합 나라 수

bool cond(int y, int x, int ny, int nx) {
    return L <= abs(board[y][x] - board[ny][nx]) && abs(board[y][x] - board[ny][nx]) <= R;
}

void bfs(int y, int x) {
    queue<pair<int, int>> q;    //bfs 사용할 큐
    q.push({ y,x });
    uni.push_back({ y,x });

    //bfs 진행
    while (!q.empty()) {
        int now_y = q.front().first;
        int now_x = q.front().second;
        q.pop();

        for (int i = 0; i < 4; ++i) {
            int ny = now_y + dy[i];
            int nx = now_x + dx[i];
            //범위안에 들어오고 인구 차이가 L이상 R 이하일 경우
            if (0 <= ny && ny < N && 0 <= nx && nx < N) {
                if (!visited[ny][nx] && cond(now_y, now_x, ny, nx)) {
                    q.push({ ny,nx });  //큐에 넣고
                    num++;  //나라 수 증가
                    people += board[ny][nx];    //인구 수 증가
                    uni.push_back({ ny,nx });   //연합에 넣는다.
                    visited[ny][nx] = true;
                }
            }
        }
    }
}


//DFS 풀이
void DFS(int y, int x)
{
    for (int i = 0; i < 4; i++)
        int nextY = y + moveDir[i].y;
        int nextX = x + moveDir[i].x;
        int diff = abs(graph[y][x] - graph[nextY][nextX]);
        if (0 <= nextY && nextY < N && 0 <= nextX && nextX < N)
            if (L <= diff && diff <= R && !visited[nextY][nextX])
            {
                //조건 충족할 경우에만
                visited[nextY][nextX] = true;
                v.push_back({ nextY, nextX });
                people += graph[nextY][nextX];
                num++;
                DFS(nextY, nextX);
            }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> L >> R;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            cin >> board[i][j];

    int ret = 0;

    while (1) {
        memset(visited, false, sizeof(visited));

        bool found = false;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (visited[i][j])
                    continue;

                visited[i][j] = true;
                people = board[i][j];
                num = 1;    //나라 수는 1

                uni.clear();
                bfs(i, j);

                //국경이 하나라도 열리면
                if (num >= 2) {
                    found = true;
                    for (int i = 0; i < uni.size(); ++i)
                        board[uni[i].first][uni[i].second] = people / num;
                }
            }
        }
        //케이스 증가
        if (found)
            ret++;
        else
            break;

    }
    cout << ret;
    return 0;
}