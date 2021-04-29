/*
14502_연구소 문제랑 비슷하다.
1부터 100까지 모든 높이에 대해 수행하여 높이보다 작은 부분을 제외한 남은 컴포넌트 갯수를 구하면 된다.
dfs를 사용하면 쉽게 풀린다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX = 101;

int n;
int area[MAX][MAX];
int tmp[MAX][MAX];
int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };
bool visited[MAX][MAX];

void dfs(int y, int x) {
    visited[y][x] = true;
    for (int dir = 0; dir < 4; ++dir) {
        int ny = y + dy[dir];
        int nx = x + dx[dir];
        //범위 내
        if (0 <= ny && ny < n && 0 <= nx && nx < n) {
            if (!visited[ny][nx] && tmp[ny][nx] != -1)
                dfs(ny, nx);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> area[i][j];

    //아무지역도 물에 안잠기면 안전한 지역은 그래프 전체임
    int ret = 1;

    //최소 높이부터 시작해서 최대 높이까지 물에 잠기지 않는 쵀대 부분을 구한다.
    for (int i = 1; i < MAX; ++i) {
        int cnt = 0;
        memset(visited, false, sizeof(visited));

        //복사
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                tmp[i][j] = area[i][j];

        //높이가 낮은 부분은 -1로 처리
        for (int j = 0; j < n; ++j)
            for (int k = 0; k < n; ++k) {
                if (tmp[j][k] <= i) {
                    tmp[j][k] = -1;
                }
            }
        //dfs 갯수만큼 컴포넌트 구한다.
        for (int j = 0; j < n; ++j)
            for (int k = 0; k < n; ++k) {
                if (!visited[j][k] && tmp[j][k] != -1) {
                    dfs(j, k);
                    cnt++;
                }
            }
        ret = max(ret, cnt);
    }

    cout << ret;

    return 0;
}