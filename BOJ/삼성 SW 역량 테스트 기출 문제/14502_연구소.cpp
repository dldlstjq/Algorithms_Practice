/*
처음 풀었을 때는 어느 위치에 벽을 세워야 최소가 되나 생각한다고 못풀었지만
다시 보니 모든 빈칸에 벽을 세우면서 최대를 구하면 되는 것이 보였다.

기존 연구소를 나타내는 배열과 바이러스가 퍼진 상태를 나타내는 배열 두개가 필요했고
바이러스 좌표를 저장하는 큐 역시 두 개로 설정했다.

백트래킹을 해가며 벽을 세우고 바이러스가 퍼진 후 안전지역을 구하면 된다.
다시 풀었을 때는 풀이가 조금 복잡아 보였는데 한 번 풀었던 풀이는 비교적 깔끔했다.

그리고 시간초과가 날 줄 알았는데 다행히 나지 않았다.
*/

/*
2021.07.25
문제 접근을 잘못해서 풀지 못했다. 벽을 세울 때 벽이 서로 떨어져 있어도 상관없는데 붙어있어야 되는 줄 알고
dfs형식으로 접근했다 정확한 답이 안나왔다. 또 떨어져 있는 벽을 구현할때도 그냥 처음부터 다시 0인 걸 탐색하면 되는데
너무 어렵게 생각해서 해결하지 못했다. 이런 문제는 못해도 3~40분 안에는 해결해야 승산이 있어 보인다.
*/

//2021.04.06 다시 풀었을 때 풀이
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;

const int MAX = 8;
int N, M;
int lab[MAX][MAX];
int copy_lab[MAX][MAX];

int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };

queue<pair<int, int>> q;    //바이러스 좌표 저장
queue<pair<int, int>> tmp;    //바이러스 좌표 저장
int ret;

void copy() {
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            copy_lab[i][j] = lab[i][j];
}

//바이러스 퍼진다
void virus() {
    while (!q.empty()) {
        int y = q.front().first;
        int x = q.front().second;
        q.pop();

        for (int d = 0; d < 4; ++d) {
            int ny = y + dy[d];
            int nx = x + dx[d];

            if (!(0 <= ny && ny < N && 0 <= nx && nx < M))
                continue;

            if (copy_lab[ny][nx] == 0) {
                copy_lab[ny][nx] = 2;
                q.push({ ny,nx });
            }
        }
    }
}

//안전 지역 확인
int check_safe() {
    int cnt = 0;
    for (int k = 0; k < N; ++k)
        for (int l = 0; l < M; ++l)
            if (copy_lab[k][l] == 0)
                cnt++;
    return cnt;
}


void solve(int y, int x, int wall) {
    if (wall == 0) {
        //바이러스 퍼지고 난 후 빈 칸 개수 구한다.
        copy();    //copy_board에 바이러스를 퍼트린다.
        q = tmp;   //q에 tmp 복사. 
        virus();
        ret = max(ret, check_safe());
        return;
    }

    //벽이 0이 될때가지 세워본다.
    for (int i = y; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (lab[i][j] == 0) {
                lab[i][j] = 1;
                solve(i, j, wall - 1);
                lab[i][j] = 0;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M;
    //바이러스 좌표는 큐에 저장
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> lab[i][j];
            if (lab[i][j] == 2) {
                q.push({ i,j });
            }
        }
    }

    //tmp에 q 복사
    tmp = q;

    //벽을 하나씩 세워본다.
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (lab[i][j] == 0) {
                lab[i][j] = 1;
                solve(i, j, 2);
                lab[i][j] = 0;
            }
        }
    }

    cout << ret;

    return 0;
}


///////////////////////////////////////////
//나름 깔끔한 풀이. main에서 배열을 복사했고 
//바이러스 퍼진 것을 구현할 때 큐에 바이러스를 넣었다.
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

const int MAX = 8;
int n, m;
int adj[MAX][MAX];
int tmp[MAX][MAX];
int ret;

int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };

void bfs() {
    //바이러스가 퍼진 상태를 저장한다.
    int virus[MAX][MAX];
    //복사
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            virus[i][j] = tmp[i][j];

    //바이러스인 좌표를 큐에 넣는다.
    queue<pair<int, int>> q;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (tmp[i][j] == 2)
                q.push({ i,j });


    while (!q.empty()) {
        int cur_y = q.front().first;
        int cur_x = q.front().second;

        q.pop();

        for (int i = 0; i < 4; ++i) {
            int ny = cur_y + dy[i];
            int nx = cur_x + dx[i];
            //범위안
            if (0 <= ny && ny < n && 0 <= nx && nx < m) {
                //빈칸은 바이러스가 퍼진다.
                if (virus[ny][nx] == 0) {
                    virus[ny][nx] = 2;
                    q.push({ ny,nx });
                }


            }
        }
    }
    int empty = 0;
    //빈칸 세기
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (virus[i][j] == 0)
                empty++;
    ret = max(ret, empty);
}

void makewall(int cnt) {
    //벽을 세개 만들었으므로
    if (cnt == 3) {
        bfs();
        return;
    }
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (tmp[i][j] == 0) {
                tmp[i][j] = 1;  //마찬가지로 해당칸에 새우고
                makewall(cnt + 1);
                tmp[i][j] = 0;  //다시 허문다
            }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);


    cin >> n >> m;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> adj[i][j];

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            //빈칸인 부분 전부에 벽을 세워서 최대값을 찾아야한다.
            if (adj[i][j] == 0) {
                //tmp에 adj를 복사한다.
                for (int k = 0; k < n; ++k)
                    for (int l = 0; l < m; ++l)
                        tmp[k][l] = adj[k][l];

                tmp[i][j] = 1;  //해당 칸에 벽을 세운다.
                makewall(1);     //벽을 세운 상태이므로 cnt=1
                tmp[i][j] = 0;  //다시 허문다.
            }
        }
    }

    cout << ret;
    return 0;
}