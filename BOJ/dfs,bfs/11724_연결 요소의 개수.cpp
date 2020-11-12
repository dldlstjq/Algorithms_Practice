/*
무방향 그래프이기 때문에 양쪽 정점 연결해주고 dfs, bfs 둘 중 하나 이용해 연결 요소 찾으면 됨
연결된 그래프가 몇개 인지 구하는 것으로 이해함
*/
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define MAX 1001
int map[MAX][MAX];
int visited[MAX];
int n, m, v;
int cntComponent;

void dfs(int start) {
    visited[start] = true;
    for (int i = 1; i <= n; i++) {
        if (map[start][i] && !visited[i]) {
            dfs(i);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;

    int v1, v2;

    for (int i = 1; i <= m; i++) {
        cin >> v1 >> v2;
        map[v1][v2] = 1;
        map[v2][v1] = 1;
    }

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfs(i);
            cntComponent++;
        }
    }
    cout << cntComponent;

    return 0;
}