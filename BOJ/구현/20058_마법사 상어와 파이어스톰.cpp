/*
문제를 잘못 이해해서 시간이 많이 걸렸다.

격자를 회전하는 경우 모든 칸에 대해 회전을 하면 되는데
예제에 색깔이 있는 부분만 회전을 해야 하는 줄 알고 그 부분을 구현하는 것이 힘들었다.
분할정복을 써서 들어가는데 어디서 어떻게 조건을 걸어야 색깔 있는 부분만 회전할 수 있는지
몰라서 해결하지 못했다.

다른 사람 풀이를 보니 애초에 모든 2^L x 2^L 격자에 대해 회전을 하면 됐다.
문제를 제대로 안보고 대충 해석한게 가장 큰 실수인 것 같다.

모든 격자에 대해 회전을 해야 하는 걸 알고나니 회전은 그렇게 오래 걸리지 않았다.
격자의 행이 가장 오른쪽 열로 이동하는 것이어서 비교적 쉽게 구현했다.

얼음이 줄어드는 조건도 다소 난해했는데 인접한 얼음이 3개 미만이면 해당 얼음을 1 감소시키면 된다.
다만 여기서도 모든 얼음이 동시에 감소하기 때문에 좌표하나를 검사해서 순서대로 1씩 감소하면
제대로 된 답이 나오지 않았다.

얼음 감소까지 하고 전체 얼음 갯수는 간단히 구하고 얼음 덩어리는 dfs를 돌려 구했다.

문제를 천천히 잘 읽어서 뭘 구현해야 하는지 빨리 파악하는게 제일 중요한것 같다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 64 + 1;
int N, Q, L;
int A[MAX][MAX];
int copy_A[MAX][MAX];

int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };

bool visited[MAX][MAX];
int cnt;

void copy() {
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            copy_A[i][j] = A[i][j];
}


//회전
void rotate(int len, int y, int x) {
    copy();
    //각 행은 맨 오른쪽 열로 이동한다.
    //한 행이 끝나면 열을 1씩 감소시킨다.
    int c = x + len - 1;
    for (int i = y; i < y + len; ++i) {
        int r = y;
        for (int j = x; j < x + len; ++j) {
            A[r++][c] = copy_A[i][j];
        }
        c--;
    }
}

bool check_adjacent(int y, int x) {
    //얼음이 있는 칸 3개 또는 그 이상과 인접해있지 않은 칸은 얼음 양 1 줄어든다.
    int ice_cnt = 0;
    for (int d = 0; d < 4; ++d) {
        int ny = y + dy[d];
        int nx = x + dx[d];

        if (0 <= ny && ny < N && 0 <= nx && nx < N) {
            if (A[ny][nx] != 0)
                ice_cnt++;
        }
    }

    if (ice_cnt < 3)
        return false;
    else
        return true;
}

//얼음 감소. 동시에 감소하기 때문에 하나씩 검사해서 감소를 시켜버리면 
//인접한 얼음에도 영향을 미친다. 따라서 인접 얼음이 3개미만인 것들을 모아 한번에 처리해야 한다.
void ice_decrease() {
    vector<pair<int, int>> v;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            //얼음이 없는 칸은 패스
            if (A[i][j] == 0)
                continue;
            //인접한 얼음 3개미만인 좌표 따로 저장
            if (!check_adjacent(i, j)) {
                v.push_back({ i,j });
                //A[i][j] -= 1;
            }


        }
    }

    //한꺼번에 감소
    for (int i = 0; i < v.size(); ++i) {
        A[v[i].first][v[i].second] -= 1;
    }

}

void ice_biggest(int y, int x) {
    visited[y][x] = true;
    cnt++;
    for (int i = 0; i < 4; ++i) {
        int ny = y + dy[i];
        int nx = x + dx[i];
        if (0 <= ny && ny < N && 0 <= nx && nx < N) {
            if (A[ny][nx] != 0 && !visited[ny][nx])
                ice_biggest(ny, nx);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> Q;
    N = 1 << N;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> A[i][j];
        }
    }

    for (int i = 0; i < Q; ++i) {
        cin >> L;
        L = 1 << L;
        for (int i = 0; i < N; i += L)
            for (int j = 0; j < N; j += L)
                rotate(L, i, j);

        //얼음 감소
        ice_decrease();

    }

    //남아있는 얼음 합
    int sum = 0;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            sum += A[i][j];

    //가장 큰 덩어리
    int ret = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cnt = 0;
            if (A[i][j] != 0 && !visited[i][j]) {
                ice_biggest(i, j);
                ret = max(ret, cnt);
            }
        }
    }

    cout << sum << "\n" << ret;
    return 0;
}