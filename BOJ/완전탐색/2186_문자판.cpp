/*
처음엔 단순히 DFS를 활용하면 답이 나올 줄 알았다.
하지만 그러면 DFS문제이지 왜 완전탐색일까 싶었는데 아니나 다를까 시간초과가 떴다.
DFS와 DP를 합쳐서 구현해야하는 문제이다.
자세한건 블로그를 참조해서 이해할 수 있었다. 다시 풀어봐야 할 문제 중 하나

DP[a][b][c] = d의 의미는 "(a, b)에 존재하는 알파벳을 찾고자하는 문자열의 'c'번 인덱스로 설정했을 때,
나올 수 있는 정답의 갯수 갯수는 d개입니다.

*/

// 2021.07.01 정답을 맞은 코드랑 거의 비슷한데 틀렸다가 뜬다. 거의 똑같은데 왜 안되는지 이유를 모르겠다.
// dfs+dp 문제이고 dp를 이용할때 3차원으로 써야 답이 나온다. 인덱스를 빼먹지 말자.
#include <iostream>
#include <cstring>
using namespace std;

const int MAX = 100 + 1;
int N, M, K;
char board[MAX][MAX];
int cache[MAX][MAX][80];

int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };
string word;

int solve(int y, int x, int idx) {
    if (idx == word.length()) {
        return 1;
    }

    int& ret = cache[y][x][idx];
    if (ret != -1)return ret;

    ret = 0;
    for (int k = 1; k <= K; ++k) {
        for (int d = 0; d < 4; ++d) {
            int ny = y + dy[d] * k;
            int nx = x + dx[d] * k;

            if (0 <= ny && ny < N && 0 <= nx && nx < M) {
                if (board[ny][nx] == word[idx])
                    ret += solve(ny, nx, idx + 1);
            }
        }
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M >> K;

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            cin >> board[i][j];

    cin >> word;

    memset(cache, -1, sizeof(cache));

    int cnt = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (board[i][j] == word[0]) {
                cnt += solve(i, j, 1);
            }

        }
    }

    cout << cnt;

    return 0;
}


////////////////////////////////
#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
#include <utility>

using namespace std;
#define MAX 101
int n, m, k;
char graph[MAX][MAX];
int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };
int num;    //경로 개수
string str; //찾을 단어
int dp[MAX][MAX][80];   //메모이제이션

int dfs(int y, int x, int idx) {
    //이미 단어 경로가 있음
    if (dp[y][x][idx] != -1)
        return dp[y][x][idx];
    //idx는 찾을 단어의 인덱스를 나타냄. 0<=idx<=str.length()-1
    //단어를 다 찾은 경우 idx의 크기가 str.length()와 같음
    if (idx >= str.length())
        return 1;

    dp[y][x][idx] = 0;
    for (int i = 1; i <= k; i++) {
        for (int j = 0; j < 4; j++) {
            int ny = y + dy[j] * i;
            int nx = x + dx[j] * i;
            if (0 <= ny && ny < n && 0 <= nx && nx < m) {
                if (graph[ny][nx] == str[idx]) {
                    dp[y][x][idx] = dp[y][x][idx] + dfs(ny, nx, idx + 1);
                }
            }
        }
    }
    return dp[y][x][idx];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> k;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> graph[i][j];

    cin >> str;

    memset(dp, -1, sizeof(dp));
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (graph[i][j] == str[0])
                ans = ans + dfs(i, j, 1);
        }
    }
    cout << ans;
    return 0;
}