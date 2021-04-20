/*
어려운 문제. 이런 유형을 많이 못푸는데 다시 한번 볼 필요가 있다.
*/

/*다른 사람 풀이랑 비슷하게 했는데 시간초과가 난다.*/
#include<iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
const int MAX = 15;
const int INF = 987654321;
int N, W, H;
int board[MAX][MAX];

int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };

int ret;

bool is_in(int y, int x) {
    return 0 <= y && y < H && 0 <= x && x < W;
}

void bomb(int r, int c) {
    //board[r][c] = 0;
    queue<pair<int, int>> q;
    q.push({ r,c });

    while (!q.empty()) {
        int y = q.front().first;
        int x = q.front().second;
        int num = board[y][x];
        q.pop();

        board[y][x] = 0;

        if (num == 1)
            continue;

        for (int j = 1; j <= num - 1; ++j) {
            for (int i = 0; i < 4; ++i) {
                int ny = y + dy[i] * j;
                int nx = x + dx[i] * j;

                if (is_in(ny, nx) && board[ny][nx] != 0)
                    q.push({ ny,nx });
            }
        }
    }
}

void down() {

    for (int i = 0; i < W; i++) {
        for (int j = H - 1; j >= 1; j--) {
            for (int k = j - 1; k >= 0; k--) {
                if (board[j][i] != 0) break;
                if (board[k][i] != 0) {
                    board[j][i] = board[k][i];
                    board[k][i] = 0;
                    break;
                }
            }
        }
    }
}

void solve(int n) {
    if (n == N) {
        int cnt = 0;
        for (int i = 0; i < H; ++i)
            for (int j = 0; j < W; ++j)
                if (board[i][j] != 0)
                    cnt++;

        ret = min(ret, cnt);
        return;
    }

    int copy_board[MAX][MAX];
    for (int i = 0; i < H; ++i)
        for (int j = 0; j < W; ++j)
            copy_board[i][j] = board[i][j];


    for (int i = 0; i < W; ++i) {
        int height = 0, y = i;
        while (is_in(height, y) && board[height][y] == 0)
            height++;

        bomb(height, y);
        down();
        solve(n + 1);

        for (int j = 0; j < H; ++j)
            for (int k = 0; k < W; ++k)
                board[j][k] = copy_board[j][k];
    }
}
int main(int argc, char** argv)
{
    int test_case;
    int T;

    cin >> T;
    /*
       여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
    */
    for (test_case = 1; test_case <= T; ++test_case)
    {
        ret = INF;
        cin >> N >> W >> H;
        for (int i = 0; i < H; ++i)
            for (int j = 0; j < W; ++j)
                cin >> board[i][j];

        solve(0);

        cout << "#" << test_case << " " << ret << "\n";

    }
    return 0;//정상종료시 반드시 0을 리턴해야합니다.
}

////////////////////
#include <iostream>
#include <math.h>
#include <vector>
#include <queue>
#define INF 987654321
using namespace std;

struct node {
    int x, y, range;

    node() { }
    node(int _x, int _y, int _range) : x(_x), y(_y), range(_range) { }
};

int testcase;
int n, r, c, ans;

int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };

vector<vector<int>> map;

void printMap(vector<vector<int>> v) {
    cout << "\n";
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cout << v[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

vector<vector<int>> bombBlock(vector<vector<int>> v, int col) {
    // 구슬이 명중하는 노드 찾기
    int row = -1;
    for (int i = r - 1; i >= 0; i--) {
        if (v[i][col] == 0) {
            row = i;
            break;
        }
    }

    if (row == r - 1) return v;
    else if (row == -1) row = 0;
    else row += 1;

    queue<node> q;
    q.push(node(row, col, v[row][col]));
    v[row][col] = 0;

    while (!q.empty()) {
        int x = q.front().x;
        int y = q.front().y;
        int range = q.front().range;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nx = x;
            int ny = y;
            for (int j = 1; j < range; j++) {
                nx += dx[i];
                ny += dy[i];

                if (nx < 0 || ny < 0 || nx >= r || ny >= c) continue;

                if (v[nx][ny] >= 1) {
                    q.push(node(nx, ny, v[nx][ny]));
                    v[nx][ny] = 0;
                }
            }
        }
    }

    return v;
}

vector<vector<int>> downBlock(vector<vector<int>> v) {
    for (int i = r - 1; i >= 0; i--) {
        for (int j = 0; j < c; j++) {
            if (v[i][j] != 0) {
                int row = i;
                int col = j;

                while (1) {
                    if (v[row + 1][col] != 0 || row + 1 >= r) break;

                    v[row + 1][col] = v[row][col];
                    v[row][col] = 0;
                    row++;
                }
            }
        }
    }

    return v;
}

int getBlock(vector<vector<int>> v) {
    int res = 0;

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (v[i][j] != 0) res++;
        }
    }

    return res;
}

void dfs(vector<vector<int>> v, int cnt) {
    // n개의 구술을 쐈다면
    if (cnt == n) {
        ans = min(ans, getBlock(v));
        return;
    }

    for (int i = 0; i < c; i++) {
        vector<vector<int>> tmp = bombBlock(v, i);
        tmp = downBlock(tmp);
        dfs(tmp, cnt + 1);
    }
}

int main(int argc, const char* argv[]) {
    // cin,cout 속도향상
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> testcase;
    for (int tc = 1; tc <= testcase; tc++) {
        cin >> n >> c >> r;

        map.clear();
        map.assign(r + 1, vector<int>(c + 1, 0));

        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                cin >> map[i][j];
            }
        }

        ans = INF;
        dfs(map, 0);

        cout << "#" << tc << " " << ans << "\n";
    }

    return 0;
}

///////////////////////////////////////

//[SWEA] 5656 - 벽돌 깨기
#include<iostream>
#include<algorithm>
#define INF 1000
using namespace std;

int N, W, H;
int map[15][12] = { 0 };
int dr[] = { 0,1,0,-1 };//동남북서
int dc[] = { 1,0,-1,0 };
int minCount = INF;

void copy(int(*a)[12], int(*b)[12]) {
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            b[i][j] = a[i][j];
        }
    }
}//복사
bool check_range(int x, int y) {
    if (x >= 0 && y >= 0 && x < H && y < W)
        return true;
    else
        return false;

}//범위검사

void reset() {
    int ans = 0;
    for (int i = 0; i < W; i++) {
        for (int j = H - 1; j >= 1; j--) {
            for (int k = j - 1; k >= 0; k--) {
                if (map[j][i] != 0) break;
                if (map[k][i] != 0) {
                    map[j][i] = map[k][i];
                    map[k][i] = 0;
                    break;
                }
            }
        }
    }
}//벽돌제거 후 아래로 정렬

void boom(int row, int col) {
    if (!map[row][col]) return;
    int k = map[row][col];
    map[row][col] = 0;
    for (int i = 0; i < k; i++) {
        for (int z = 0; z < 4; z++) {
            int nr = row + dr[z] * i;
            int nc = col + dc[z] * i;
            if (check_range(nr, nc) && map[nr][nc] != 0) {
                boom(nr, nc);
            }
        }
    }
}//벽돌제거

void solve(int n) {
    int copy_map[15][12] = { 0 };
    copy(map, copy_map);
    if (n == N) {
        int cnt = 0;
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                if (map[i][j] != 0) cnt++;
            }
        }
        if (minCount > cnt)minCount = cnt;
        return;
    }
    for (int i = 0; i < W; i++) {
        int x = 0, y = i;
        while (check_range(x, y) && map[x][y] == 0)
            x++;
        boom(x, y);
        reset();
        solve(n + 1);
        copy(copy_map, map);
    }
}//0~(W-1) 사이에 구슬을 N번 투하하는 모든 경우

int main(int argc, char** argv)
{
    int test_case;
    int T;
    cin >> T;
    for (test_case = 1; test_case <= T; ++test_case)
    {
        minCount = INF;
        cin >> N >> W >> H;
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                cin >> map[i][j];
            }
        }
        solve(0);
        cout << "#" << test_case << ' ' << minCount << '\n';
    }
    return 0;
}