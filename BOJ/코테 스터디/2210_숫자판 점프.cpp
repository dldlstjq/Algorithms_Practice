/*
dfs를 이용해서 모든 경우를 확인하면 된다.
문제는 중복된 값은 제외해야하는데 set이 중복을 허용하지 않는다는 게 생각나서 비교적 쉽게 해결했다.
그게 아니면 일일이 확인해야하는 번거로움이 있을거 같다.
*/

#include <iostream>
#include <set>
using namespace std;

char board[5][5];

set<string> s;

int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };

void solve(int y, int x, string tmp) {
    //길이가 6이면 set에 삽입.
    //set은 중복을 허용하지 않는다.
    if (tmp.length() == 6) {
        s.insert(tmp);
        return;
    }

    for (int d = 0; d < 4; ++d) {
        int ny = y + dy[d];
        int nx = x + dx[d];
        if (0 <= ny && ny < 5 && 0 <= nx && nx < 5) {
            solve(ny, nx, tmp + board[ny][nx]);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j)
            cin >> board[i][j];
    }

    //문자를 하나씩 붙여서 확인한다
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            string str = "";
            str += board[i][j];
            solve(i, j, str);
        }

    }

    cout << s.size();
    return 0;
}