/*
단지번호붙이기랑 비슷한 문제.
상하좌우 및 대각선까지 포함해야해서 총 8방향 돌면서 섬인지 바다인지 검사.
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX 50
int graph[MAX][MAX];
int visited[MAX][MAX];
//8방향 검사
int dx[8] = { -1, -1, -1, 0, 1, 1 ,1, 0 };
int dy[8] = { -1, 0, 1, 1, 1, 0, -1,-1 };
int w, h;

//8방향 돌면서 섬인지 아닌지 검사. 
//그래프 범위안에 들어오면서 방문안했고 섬이면 DFS 실행
void dfs(int y, int x) {
    visited[y][x] = true;
    for (int i = 0; i < 8; i++) {
        int nextX = x + dx[i];
        int nextY = y + dy[i];
        if (0 <= nextX && nextX < w && 0 <= nextY && nextY < h)
            if (graph[nextY][nextX] == 1 && !visited[nextY][nextX])
                dfs(nextY, nextX);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    while (1) {
        cin >> w >> h;
        if (w == 0 && h == 0)
            break;

        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++)
                cin >> graph[i][j];
        }

        int cnt = 0;
        //방문하지 않았고 그래프가 1인 곳은 섬임. dfs 수행후 섬 갯수 증가
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++)
                if (!visited[i][j] && graph[i][j] == 1) {
                    dfs(i, j);
                    cnt++;
                }

        }
        cout << cnt << "\n";

        //그래프, 방문여부 초기화
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                graph[i][j] = 0;
                visited[i][j] = 0;
            }
        }
    }

    return 0;
}