/*
뱡향이 3가지 방향밖에 없어서 비교적 쉽게 풀 수 있었다.
나는 좌표가 맨 마지막에 오면 종료하고 for문을 이용해 3가지 방향을 계산했는데
다른 풀이도 있었다.
*/

#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX = 1000 + 1;
int n, m;
int maze[MAX][MAX];
int cache[MAX][MAX];

int dy[3] = { 0,1,1 };
int dx[3] = { 1,1,0 };

//내 풀이
int solve(int y, int x) {
    //맨 마지막 좌표로 오면 해당 좌표의 사탕 리턴
    if (y == n - 1 && x == m - 1) {
        return maze[y][x];
    }

    int& ret = cache[y][x];
    if (ret != -1)return ret;
    for (int i = 0; i < 3; ++i) {
        int ny = y + dy[i];
        int nx = x + dx[i];
        //범위 내에 있고 현재위치의 사탕과 다음 위치 사탕을 계속 이어나가서 최대를 구한다,
        if (0 <= ny && ny < n && 0 <= nx && nx < m) {
            ret = max(ret, maze[y][x] + solve(ny, nx));
        }
    }
    return ret;
}

//다른 풀이. (1,1)부터 시작한다.
int maxCandy(int y, int x)
{
    if (y < 0 || y>N || x < 0 || x>M)
        return 0; //범위 초과

    int& result = cache[y][x];
    if (result != -1)
        return result;
    result = maze[y][x];
    //(y+1, x)로 갔을 경우, (y, x+1)로 갔을 경우 그리고 (y+1, x+1)로 갔을 경우 중 최대 값 반환
    return result += max(maxCandy(y + 1, x), max(maxCandy(y, x + 1), maxCandy(y + 1, x + 1)));
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    memset(cache, -1, sizeof(cache));

    cin >> n >> m;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> maze[i][j];

    cout << solve(0, 0);
    return 0;
}