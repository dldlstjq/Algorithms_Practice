//ret=0을 쓰면 visited를 안 써도 돼서 메모리를 덜 쓴다.
//ret=-1이면 방문 안한곳, 1이면 경로가 있다, 0이면 경로가 없다.

#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX = 500 + 1;
int n, m;
char maze[MAX][MAX];
int cache[MAX][MAX];
bool visited[MAX][MAX];

//범위 안에 있는지 체크
bool is_in(int y, int x) {
    return 0 <= y && y < n && 0 <= x && x < m;
}

int solve(int y, int x) {
    //좌표가 이미 방문한 곳이고 범위 안에 있으면 무한루프를 돈다.
    //0 반환
    if (visited[y][x] == true && is_in(y, x))
        return 0;

    //범위 벗어나면 ok
    if (!is_in(y, x))
        return 1;

    //메모이제이션
    int& ret = cache[y][x];
    if (ret != -1)return ret;

    ret = 0;  //이 부분을 쓰면 visited를 쓸 필요가 없다.

    //해당 알파벳에 따라 좌표를 이동한다.
    //무한루프를 방지하기 위해 방문표시를 해주고 끝난 다음 다시 방문해제 해주어야 경로를 셀 수 있다.
    //해제 하지 않으면 위의 if문에서 visited==true에 걸려 0을 반환하기 때문에 정답이 제대로 안나온다.
    if (maze[y][x] == 'D') {
        visited[y][x] = true;
        ret = max(ret, solve(y + 1, x));
        visited[y][x] = false;
    }

    else if (maze[y][x] == 'U') {
        visited[y][x] = true;
        ret = max(ret, solve(y - 1, x));
        visited[y][x] = false;
    }

    else if (maze[y][x] == 'R') {
        visited[y][x] = true;
        ret = max(ret, solve(y, x + 1));
        visited[y][x] = false;
    }

    else if (maze[y][x] == 'L') {
        visited[y][x] = true;
        ret = max(ret, solve(y, x - 1));
        visited[y][x] = false;
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> maze[i][j];

    //cache 초기화
    memset(cache, -1, sizeof(cache));

    //각 좌표마다 탈출 가능한 칸을 더한다.
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j)
            ans += solve(i, j);
    }
    cout << ans;
    return 0;
}