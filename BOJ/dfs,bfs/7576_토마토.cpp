/*
bfs 사용하는건 알았는데 두 군데서 동시에 토마토 있는 경우를 해결못함.
토마토가 익은 곳을 입력받을 때 큐에 바로 넣어줘야 두 군데 있는 경우를 고려할 수 있음.
여기서는 방문여부는 graph에다 표시하고 날짜를 visited에 표시함
*/

//2021.05.31 
// 2차원 배열을 3개를 선언했다. 방문여부와 날짜를 합친 하나만 있어도 되기 때문에 메모리를 아낄 수 있다.
#include <iostream> 
#include <algorithm>
#include <queue>
using namespace std;

const int MAX = 1000 + 2;
int M, N;
int box[MAX][MAX];  // 토마토 정보
int day[MAX][MAX];  // 날짜 저장 배열
bool visited[MAX][MAX];

int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };

queue<pair<int, int>> q;

void bfs() {
    while (!q.empty()) {
        int y = q.front().first;
        int x = q.front().second;
        q.pop();

        for (int d = 0; d < 4; ++d) {
            int ny = y + dy[d];
            int nx = x + dx[d];

            // 범위 밖
            if (ny < 0 || ny >= N || nx < 0 || nx >= M)
                continue;
            // 이미 방문했거나 빈 곳
            if (visited[ny][nx] || box[ny][nx] == -1)
                continue;

            visited[ny][nx] = true;
            q.push({ ny,nx });
            day[ny][nx] = day[y][x] + 1;
        }
    }
}

int main(int argc, char** argv) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> M >> N;

    int tomato = 0;    //익은 토마토 개수
    int empty = 0;     // 빈 곳 개수
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j) {
            cin >> box[i][j];
            if (box[i][j] == 1) {
                visited[i][j] = true;
                q.push({ i,j });
                tomato++;
            }
            else if (box[i][j] == -1) {
                visited[i][j] = true;
                empty++;
            }
        }

    // 전체 크기는 N*M. 비어있는 곳을 뺀 곳이 토마토가 존재할 수 있다. 
    // 그 개수가 익은 토마토 개수와 같으면 모든 토마토 익어있다.
    if (N * M - empty == tomato) {
        cout << 0;
        return 0;
    }

    bfs();

    bool flag = true;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            // 방문하지 않았고 익지 않은 토마토가 있다.
            if (!visited[i][j] && box[i][j] == 0) {
                flag = false;
                break;
            }

        }
        if (!flag)
            break;
    }

    //하나라도 익지 않았다.
    if (!flag)
        cout << -1;

    // 제일 큰 날짜가 최소 일수
    else {
        int ret = 0;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                ret = max(ret, day[i][j]);

        cout << ret;
    }

    return 0;
}


////////////////////////////////////////////

#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

#define MAX 1000
int graph[MAX][MAX];
int visited[MAX][MAX];
int dx[4] = { 0,1,0,-1 };
int dy[4] = { -1,0,1,0 };
int m, n;
queue <pair<int, int>> q;

void bfs(int y, int x) {
    visited[y][x] = 0;  //처음 날짜는 0

    while (!q.empty()) {
        int nowY = q.front().first;
        int nowX = q.front().second;
        q.pop();
        for (int i = 0; i < 4; i++) {
            int nextX = nowX + dx[i];
            int nextY = nowY + dy[i];
            //nextX, nextY가 범위 안에 들어오고
            if (0 <= nextX && nextX < m && 0 <= nextY && nextY < n) {
                //방문하지 않은 곳인고 안 익은 토마토 있으면 계산
                if (!visited[nextY][nextX] && !graph[nextY][nextX]) {
                    q.push(make_pair(nextY, nextX));
                    graph[nextY][nextX] = 1;
                    visited[nextY][nextX] = visited[nowY][nowX] + 1;

                }
            }
        }

    }

}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> m >> n;

    //토마토가 익은 곳은 큐에 넣음
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> graph[i][j];
            if (graph[i][j] == 1)
                q.push(make_pair(i, j));
        }
    }
    int y = q.front().first;
    int x = q.front().second;

    bfs(y, x);


    int max = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            //안 익은 토마토가 남아 있으면 -1
            if (graph[i][j] == 0) {
                cout << -1;
                return 0;
            }
            //다 익은 날짜가 max
            else if (max < visited[i][j]) {
                max = visited[i][j];
            }
        }

    }
    cout << max;

    return 0;
}