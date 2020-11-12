/*
bfs 사용하는건 알았는데 두 군데서 동시에 토마토 있는 경우를 해결못함.
토마토가 익은 곳을 입력받을 때 큐에 바로 넣어줘야 두 군데 있는 경우를 고려할 수 있음.
여기서는 방문여부는 graph에다 표시하고 날짜를 visited에 표시함
*/
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