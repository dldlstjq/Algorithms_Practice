/*
백트래킹을 이용한 문제이다.
처음에는 DFS로만 풀었다가 틀려서 다시 확인해보니 백트래킹을 써야했다.
visited의 경우 A는 이미 방문했으니 더 이상 방문하지 못한다가 아니라 다른 경로로 가겠다. A는 방문하지 않았으니 다시 가도 된다는 식으로 코드를 구현해야한다.
DFS는 모든 노드를 한번씩 다 방문하지만 백트래킹은 비효율적인 경로는 가지 않고 다시 되돌아오는 것에서 차이가 있다.
*/

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;
#define MAX 21
int R, C;
int dy[] = { -1,0,1,0 };
int dx[] = { 0,1,0,-1 };
char graph[MAX][MAX];
bool visited[26];
int ans = 0;

//dfs 돌면서 방문 안한 알파벳 있으면 카운트
void dfs(int y, int x, int cnt) {
    for (int i = 0; i < 4; i++) {
        int ny = y + dy[i];
        int nx = x + dx[i];
        //백트래킹
        if (0 <= ny && ny < R && 0 <= nx && nx < C) {
            if (!visited[graph[ny][nx] - 'A']) {
                visited[graph[ny][nx] - 'A'] = true;
                dfs(ny, nx, cnt + 1);
                visited[graph[ny][nx] - 'A'] = false;
            }
            else {
                if (cnt > ans)
                    ans = cnt;
                continue;
            }
        }
    }

}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int cnt = 0;
    cin >> R >> C;

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            cin >> graph[i][j];
        }
    }

    memset(visited, false, sizeof(visited));
    visited[graph[0][0] - 'A'] = true;
    dfs(0, 0, 1);

    cout << ans;
    return 0;
}