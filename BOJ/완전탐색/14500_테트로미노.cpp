/*
문제를 보자마자 DFS가 생각났다. 근데 여러가지 모양이 있기 때문에
visited를 막 사용하면 모든 모양을 체크할 수 없었다.
그래서 백트래킹 형식으로 제일 처음 시작할때 visited를 체크하고 다음 좌표로 이동할때도 체크해준다.
재귀가 다 끝났을 때 다시 해제해줘서 모든 칸을 다 확인할 수 있게 한다.

그리고 ㅗ 모양은 DFS로 해결할 수 없어 직접 합을 구해줘야 한다.
ㅗ모양을 구하는데 시간이 걸려서 다른 사람 풀이를 참고했다.
*/

#include <iostream>
#include <algorithm>

using namespace std;

const int MAX = 501;
int n, m;
int paper[MAX][MAX];
int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };
bool visited[MAX][MAX];

int ret;

//ㅗ모양 테트로미노. dfs로 판별할 수 없다. 직접 구해줌.
int special(int y, int x) {
    int sum = 0;

    //ㅗ (현재 좌표 ㅡ의 가운데)
    if (y >= 1 && x >= 1 && x < m - 1)
        sum = max(sum, paper[y][x - 1] + paper[y][x] + paper[y - 1][x] + paper[y][x + 1]);
    //ㅏ (현재 좌표 ㅣ의 가운데)
    if (y >= 1 && y < n - 1 && x < m - 1)
        sum = max(sum, paper[y - 1][x] + paper[y][x] + paper[y][x + 1] + paper[y + 1][x]);
    //ㅜ (현재 좌표 ㅡ의 가운데)
    if (x >= 1 && y < n - 1 && x < m - 1)
        sum = max(sum, paper[y][x - 1] + paper[y][x] + paper[y + 1][x] + paper[y][x + 1]);
    //ㅓ (현재 좌표 ㅣ의 가운데)
    if (y >= 1 && y < n - 1 && x >= 1)
        sum = max(sum, paper[y - 1][x] + paper[y][x] + paper[y][x - 1] + paper[y + 1][x]);

    return sum;
}

//dfs로 구할 수 있는 테트로미노 구한다.
void solve(int y, int x, int sum, int cnt) {
    if (cnt == 4) {
        ret = max(ret, sum);
        return;
    }
    for (int k = 0; k < 4; ++k) {
        int ny = y + dy[k];
        int nx = x + dx[k];
        if (0 <= ny && ny < n && 0 <= nx && nx < m) {
            if (!visited[ny][nx]) {
                //함수 들어가기 직전 visited true로 해주고
                //빠져나올 때 false 해줘야 한다.
                visited[ny][nx] = true;
                solve(ny, nx, sum + paper[ny][nx], cnt + 1);
                visited[ny][nx] = false;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> paper[i][j];

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            //ㅗ 제외한 모양의 합을 구해준다.
            //함수 시작전 visited를 true로 해주고 빠져나올 때 false로 해줘야 한다.
            visited[i][j] = true;
            solve(i, j, paper[i][j], 1);
            visited[i][j] = false;

            //ㅗ 모양 합과 비교한다.
            ret = max(ret, special(i, j));
        }
    cout << ret;
    return 0;
}