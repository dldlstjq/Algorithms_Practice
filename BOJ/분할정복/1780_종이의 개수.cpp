/*
재귀함수를 써야 된다는 것은 알았는데 어떻게 써야 할 지 몰랐다.
다른 블로그를 보고 풀 수 있었는데 재귀함수에 익숙해 지려면 시간이 좀 걸릴것 같다.
아무래도 재귀함수는 디버깅 해서 값을 확인하는 게 어렵다는 것이 재귀함수를 더 어렵게 만드는 것 같다.

n을 3으로 나누면서 하나씩 들어가면 문제를 풀 수 있다.
*/
#include <iostream>

using namespace std;
#define MAX 2187
int graph[MAX][MAX];
// cnt[0] : -1로만 채워진 종이의 개수, cnt[1] : 0으로만 채워진 종이의 개수, cnt[2] : 1로만 채워진 종이의 개수
int cnt[3];

bool same(int x, int y, int n) {
    for (int i = x; i < x + n; i++) {
        for (int j = y; j < y + n; j++) {
            if (graph[x][y] != graph[i][j])
                return false;
        }
    }

    return true;
}

void solve(int x, int y, int n) {
    // 같은 숫자로 이루어진 종이면
    if (same(x, y, n)) {
        cnt[graph[x][y] + 1] += 1;
        return;
    }
    int m = n / 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            solve(x + i * m, y + j * m, m);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> graph[i][j];

    solve(0, 0, n);
    for (int i = 0; i < 3; i++)
        cout << cnt[i] << "\n";

    return 0;
}