/*
어려워서 다른 사람 코드 참고해서 품.
섬인 부분은 bfs로 탐색해서 같은 섬 번호 붙임.
같은 번호인 섬을 모두 큐에 넣어서 다른 섬에 닿을때까지 반복
자세한건 코드보는게 빠름
*/
#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring> //memset


using namespace std;

#define MAX 100
int graph[MAX][MAX];
int visited[MAX][MAX];
//4방향 검사
int dx[4] = { 0,1,0,-1 };
int dy[4] = { -1,0,1,0 };
int n;
int cnt = 1;
queue <pair<int, int>> q;

void bfs(int y, int x) {
    q.push(make_pair(y, x));
    visited[y][x] = 1;
    while (!q.empty()) {
        int nowY = q.front().first;
        int nowX = q.front().second;
        //현재 위치 대륙 번호 붙임
        graph[nowY][nowX] = cnt;
        q.pop();
        for (int i = 0; i < 4; i++) {
            int nextX = nowX + dx[i];
            int nextY = nowY + dy[i];
            //nextX, nextY가 범위 안에 들어오고
            if (0 <= nextX && nextX < n && 0 <= nextY && nextY < n) {
                //방문하지 않은 곳인고 대륙인 경우
                if (!visited[nextY][nextX] && graph[nextY][nextX] == 1) {
                    //같은 대륙이면 같은 번호 붙임
                    graph[nextY][nextX] = cnt;
                    q.push(make_pair(nextY, nextX));
                    visited[nextY][nextX] = 1;
                }
            }
        }

    }

}

int make_bridge(int num) {
    // 같은 대륙에 있는 모든 땅을 큐에 넣음
    queue <pair<int, int>> bridge;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (graph[i][j] == num)
                bridge.push(make_pair(i, j));
        }
    }

    int result = 0;
    while (!bridge.empty()) {
        int size = bridge.size();
        //bridge 사이즈 만큼 반복
        for (int i = 0; i < size; i++) {
            int nowY = bridge.front().first;
            int nowX = bridge.front().second;
            bridge.pop();
            for (int i = 0; i < 4; i++) {
                int nextX = nowX + dx[i];
                int nextY = nowY + dy[i];
                //nextX, nextY가 그래프 범위 안에 들어오고
                if (0 <= nextX && nextX < n && 0 <= nextY && nextY < n) {
                    //방문하지 않은 곳이고 바다라면 큐에 넣음
                    if (!visited[nextY][nextX] && !graph[nextY][nextX]) {
                        bridge.push(make_pair(nextY, nextX));
                        visited[nextY][nextX] = 1;
                    }
                    //이동하려는 칸이 육지이고 다른 섬에 도착하면 종료
                    else if (graph[nextY][nextX] && graph[nextY][nextX] != num)
                        return result;
                }
            }
        }
        result++;

    }

}

int MIN(int a, int b) {
    return a < b ? a : b;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cin >> graph[i][j];
    }

    //섬에 번호 붙임
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!visited[i][j] && graph[i][j]) {
                bfs(i, j);
                cnt++;
            }
        }
    }

    int result = 999999;
    //최단 거리 다리 구함. 새로 시작할때마다 visited 초기화
    for (int i = 1; i < cnt; i++) {
        memset(visited, false, sizeof(visited));
        result = MIN(result, make_bridge(i));

    }
    cout << result;

    return 0;
}