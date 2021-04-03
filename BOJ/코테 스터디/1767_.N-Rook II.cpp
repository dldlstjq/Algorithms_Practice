/*
53분 부터 시작.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <set>
using namespace std;

const int MAX = 100 + 1;
const int MOD = 1000001;
int N, M, K;
int board[MAX][MAX];
bool visited[MAX][MAX];

int ret;

bool check(int y, int x) {

}

void solve(int y, int x, int row, int col, int rook) {
    if (rook == K) {
        ret += ret % MOD;
        return;
    }

    for (int i = y; i < N; ++i) {
        if (row == 2)
            continue;
        for (int j = x + 1; j < M; ++j) {

        }
    }

}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M >> K;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            board[i][j] = 1;
            solve(i, j, 1);
            board[i][j] = 0;
        }
    }

    return 0;
}