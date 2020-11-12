/*
전형적인 dfs 문제.
처음엔 방향 설정하는 걸 못잡아서 못풀었는데 이제는 어느정도 할 줄 암.
방문 안했으면서 1인 곳을 dfs 돌면서 크기 측정.
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX 25
string graph[MAX];
int visited[MAX][MAX];
int cnt;
int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { -1, 0, 1, 0 };
int n;

void dfs(int x, int y) {
    cnt++;
    visited[x][y] = true;
    for (int i = 0; i < 4; i++) {
        int nextX = x + dx[i];
        int nextY = y + dy[i];
        if (0 <= nextX && nextX < n && 0 <= nextY && nextY < n)
            if (graph[nextX][nextY] == '1' && !visited[nextX][nextY])
                dfs(nextX, nextY);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int a;
    cin >> n;
    vector<int> residance; //단지 내 집 수 저장용 벡터

    for (int i = 0; i < n; i++) {
        cin >> graph[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            if (!visited[i][j] && graph[i][j] == '1') {
                cnt = 0;
                dfs(i, j);
                residance.push_back(cnt);
            }

    }
    sort(residance.begin(), residance.end());
    cout << residance.size() << "\n";
    for (int i = 0; i < residance.size(); i++)
        cout << residance[i] << "\n";


    return 0;
}