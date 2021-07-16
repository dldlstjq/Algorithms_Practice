/*
문제이해는 쉽게 됐는데 구현이 어려웠다.

토네이도의 경우 서남동북 순으로 움직이기 때문에 visited 배열을 선언해서 
한칸 움직일때마다 visited 표시해주고 다음 방향으로 이동할 수 있는지 확인한다.
이동할 수 있으면 해당 칸으로 방향을 바꿔 이동하고 그렇지 않으면 이동뱡향으로 계속 이동한다.

문제는 모래의 양을 구하는 것이었다. 1%, 2%, 7%, 10% 2개에 5% 1개, a까지 고려하면 전체 10개의 경우의 수가 나온다.
이 경우의수가 전체 4방향이므로 총 40가지 경우를 고려해야 하는데 이걸 전부 다 일일이 구현하는건 코드가 너무 복잡해지고
어려울 것 같았다.

상대적인 좌표를 딱 정하면 좋겠다 생각했는데 로직이 생각나지 않아 못풀었다.

퍼센트는 퍼센트대로 정의하고 각 방향에 맞게 2차원 배열을 해서 좌표를 설정하면 된다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 1000 + 1;
int N;
int A[MAX][MAX];
bool visited[MAX][MAX];

int dy[4] = { 0,1,0,-1 };
int dx[4] = { -1,0,1,0 };

const int blow_y[4][10] = {
   {-1,1,-2,-1,1,2,-1,1,0,0},
    {-1,-1,0,0,0,0,1,1,2,1},
    {-1,1,-2,-1,1,2,-1,1,0,0},
    {1,1,0,0,0,0,-1,-1,-2,-1}
};

const int blow_x[4][10] = {
   {1,1,0,0,0,0,-1,-1,-2,-1},
    {-1,1,-2,-1,1,2,-1,1,0,0},
    {-1,-1,0,0,0,0,1,1,2,1},
    {-1,1,-2,-1,1,2,-1,1,0,0}
};
const int percent[9] = { 1,1,2,7,7,2,10,10,5 };

int ret;

bool is_in(int y, int x) {
    return 0 <= y && y < N && 0 <= x && x < N;
}

int blow_sand(int y, int x, int d) {
    int sum = 0, init = A[y][x];
    for (int i = 0; i < 10; ++i) {
        int sand = 0;
        //마지막은 a로 이동하는 모래이다.
        if (i != 9) {
            sand = init * percent[i] / 100;
            A[y][x] -= sand;
        }
        else
            sand = A[y][x];

        //모래가 날린 부분이 범위 안이면 더해주고 아니면 sum에 저장
        int ny = y + blow_y[d % 4][i];
        int nx = x + blow_x[d % 4][i];

        if (!is_in(ny, nx)) {
            sum += sand;
            continue;
        }

        A[ny][nx] += sand;

    }
    //현재 좌표의 모래는 없어진다.
    A[y][x] = 0;
    return sum;
}

void solve(int y, int x) {
    //토네이도 이동
    int dir = 0;

    while (1) {
        y += dy[dir % 4];
        x += dx[dir % 4];

        if (y == 0 && x == -1)
            break;

        visited[y][x] = true;

        ret += blow_sand(y, x, dir);

        int ny = y + dy[(dir + 1) % 4];
        int nx = x + dx[(dir + 1) % 4];

        if (!visited[ny][nx])
            dir += 1;

    }


}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            cin >> A[i][j];

    int start_y = N / 2;
    int start_x = N / 2;

    visited[start_y][start_x] = true;
    solve(start_y, start_x);

    cout << ret;

    return 0;
}