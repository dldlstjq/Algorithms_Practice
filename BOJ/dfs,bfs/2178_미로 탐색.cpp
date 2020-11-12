/*
bfs 사용해서 지나야 하는 칸 수를 visited에 저장. 제일 마지막 n,m위치의 수가 최소 칸 수
*/
#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
#include <queue>


using namespace std;

#define MAX 101
int graph[MAX][MAX];
int visited[MAX][MAX];
//4방향 검사
int dx[4] = { 0,1,0,-1 };
int dy[4] = { -1,0,1,0 };
int n, m;
queue <pair<int, int>> q;

void bfs(int y, int x) {
    q.push(make_pair(y, x));
    visited[y][x] = 1;

    while (!q.empty()) {
        int nowY = q.front().first;
        int nowX = q.front().second;
        q.pop();
        for (int i = 0; i < 4; i++) {
            int nextX = nowX + dx[i];
            int nextY = nowY + dy[i];
            //nextX, nextY가 범위 안에 들어오고
            if (0 < nextX && nextX <= m && 0 < nextY && nextY <= n) {
                //방문하지 않은 곳인고 길이 있으면 큐에 넣음
                if (!visited[nextY][nextX] && graph[nextY][nextX] == 1) {
                    q.push(make_pair(nextY, nextX));
                    visited[nextY][nextX] = visited[nowY][nowX] + 1;
                }
            }
        }

    }

}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string str;
    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        cin >> str;
        for (int j = 0; j < m; j++)
            graph[i][j] = str[j] - '0';
    }

    bfs(0, 0);
    cout << visited[n - 1][m - 1];

    return 0;
}