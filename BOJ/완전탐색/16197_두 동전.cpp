/*
예외조건 설정에 너무 애를 먹었다.
첫 접근은 solve의 인자를 똑같이 주고 10번이 넘어가면 -1을 출력하고 종료하는 것을 했다.
그 다음 좌표를 움직일 때가 문제였는데 둘 다 범위를 나갔을 경우, 둘 중 하나만 나갔을 경우를
어디서 구현해야하는지, visited를 어떻게 설정해야 한번 간 곳은 다시 안가게 할 수 있는지 등이 너무 헷갈렸다.

다른사람들의 풀이를 보니 4차원 visited를 사용해 방문여부를 체크했고
함수인자를 적절하게 사용하여 해결했다.

그렇게 어려워 보이진 않았는데 구현이 까다로웠다.
재귀함수쪽은 진짜 연습이 많이 필요한 것 같다.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX = 21;
int n, m;
char board[MAX][MAX];
int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };


bool is_in(int y, int x) {
    return 0 <= y && y < n && 0 <= x && x < m;
}

int solve(int y1, int x1, int y2, int x2, int cnt) {
    bool out1 = false;
    bool out2 = false;

    //10번보다 많은 경우
    if (cnt > 10)
        return -1;

    //범위 밖으로 나가는 경우
    if (!is_in(y1, x1))
        out1 = true;
    if (!is_in(y2, x2))
        out2 = true;

    //둘다 범위 나가면 -1 리턴
    if (out1 && out2)
        return -1;
    //둘 중 하나만 아웃이면 cnt 리턴
    if (out1 || out2)
        return cnt;

    int ans = -1;

    for (int i = 0; i < 4; ++i) {
        int ny1 = y1 + dy[i];
        int nx1 = x1 + dx[i];
        int ny2 = y2 + dy[i];
        int nx2 = x2 + dx[i];

        //가는 방향이 벽이라면 원위치
        if (is_in(ny1, nx1) && board[ny1][nx1] == '#') {
            ny1 = y1;
            nx1 = x1;
        }
        if (is_in(ny2, nx2) && board[ny2][nx2] == '#') {
            ny2 = y2;
            nx2 = x2;
        }
        //next가 -1이라면 해당 방향으로는 답이 없다.
        int next = solve(ny1, nx1, ny2, nx2, cnt + 1);
        if (next == -1)
            continue;
        //맨 처음 발견한 횟수 혹은 기존 ans보다 next가 더 작으면 ans 갱신
        if (ans == -1 || ans > next)
            ans = next;

    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;

    int y1, x1, y2, x2;
    int flag = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            cin >> board[i][j];
            if (flag == 0 && board[i][j] == 'o') {
                y1 = i, x1 = j;
                flag++;
            }
            else if (flag == 1 && board[i][j] == 'o') {
                y2 = i, x2 = j;
            }
        }

    cout << solve(y1, x1, y2, x2, 0);

    return 0;
}



///////////////////////////////////////////////////////////
//solve 인자에 방향을 넣어서 구현해도 괜찮은 것 같다.
bool is_in(int y, int x) {
    return 0 <= y && y < n && 0 <= x && x < m;
}

int ans;

void solve(int y1, int x1, int y2, int x2, int cnt, int dir) {
    // 기존의 횟수보다 더 많이 버튼을 눌렸다면 더 이상 해볼 필요가 없다. (최소값이 아니므로)
    if (ans < cnt)
        return;
    //10번보다 많은 경우 더이상 진행할 필요가 없다.
    if (cnt > 10) {
        //기존 횟수와 비교해서 값을 갱신하고 종료.
        ans = min(ans, cnt);
        return;
    }

    int ny1 = y1 + dy[i];
    int nx1 = x1 + dx[i];
    int ny2 = y2 + dy[i];
    int nx2 = x2 + dx[i];

    //둘 다 범위 벗어날 경우 종료
    if (!is_in(ny1, nx1) && !is_in(ny2, nx2))
        return;

    //둘 중 하나만 떨어질 경우
    else if(is_in(ny1, nx1) && !is_in(ny2, nx2)) {
        ans = min(ans, cnt);
        return;
    }
    else if (!is_in(ny1, nx1) && is_in(ny2, nx2)) {
        ans = min(ans, cnt);
        return;
    }

    //가는 방향이 벽이라면 원위치
    if (board[ny1][nx1] == '#') {
        ny1 = y1;
        nx1 = x1;
    }
    if (board[ny2][nx2] == '#') {
        ny2 = y2;
        nx2 = x2;
    }
    
    //다음 진행방향으로
    for (int i = 0; i < 4; ++i) 
        solve(ny1, nx1, ny2, nx2, cnt + 1, i);
    
}

int main() {
    //....

    for (int i = 0; i < 4; ++i) 
        solve(y1, x1, y2, x2, 1, i);
   
	if (ans > 10)
		ans = -1;
    cout << ans;
}