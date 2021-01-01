/*
첫 풀이는 (0,0)부터 시작해 양 옆과 위 아래를 비교해
색깔이 같으면 바꿔주는 식으로 풀었다.

하지만 (0,0)에 흰색이 오는지 검은색이 오는지에 따라 바꿔야 할
횟수가 달라지므로 둘 다 계산한 값 중 최소를 구해야 했다.

하나만 계산을 했기 때문에 오답이 나왔다.
종만북에서 처럼 흰색이 먼저오는 경우와 검은색이 먼저 오는 경우를
미리 선언해 놓고 거기서 하나씩 비교해 나가면 짧은 코드로 쉽게 답을 구할 수 있었다.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 987654321;
const int MAX = 50;

int m, n;
string board[MAX];

//(0,0)이 W인 보드
string white[8] = {
    {"WBWBWBWB"},
    {"BWBWBWBW"},
    {"WBWBWBWB"},
    {"BWBWBWBW"},
    {"WBWBWBWB"},
    {"BWBWBWBW"},
    {"WBWBWBWB"},
    {"BWBWBWBW"},
};

//(0,0)이 B인 보드
string black[8] = {
    {"BWBWBWBW"},
    {"WBWBWBWB"},
    {"BWBWBWBW"},
    {"WBWBWBWB"},
    {"BWBWBWBW"},
    {"WBWBWBWB"},
    {"BWBWBWBW"},
    {"WBWBWBWB"},
};


//해당 인덱스 위치가 8*8체스판 범위에 들어오는지 확인
bool range(int y, int x) {
    if (y + 8 > n || x + 8 > m)
        return false;
    return true;
}

//(0,0)에 흰색이 먼저 올 때 최소
int white_first(int y, int x) {
    int cnt = 0;
    for (int i = y; i < y + 8; ++i)
        for (int j = x; j < x + 8; ++j)
            //board의 범위는 8~50 사인데
            //white와 black의 가로, 세로는 8이므로 
            //i와 j에 y와 x를 빼서 인덱스를 맞춰준다. 
            if (board[i][j] != white[i - y][j - x])
                cnt++;
    return cnt;
}

//(0,0)에 검은색이 먼저 올 때 최소
int black_first(int y, int x) {
    int cnt = 0;
    for (int i = y; i < y + 8; ++i)
        for (int j = x; j < x + 8; ++j)
            if (board[i][j] != black[i - y][j - x])
                cnt++;
    return cnt;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 0; i < n; ++i)
        cin >> board[i];

    int ret = INF;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (range(i, j))
                //흰색, 검은색이 먼저 오는것중 최소가 정답
                ret = min(ret, min(white_first(i, j), black_first(i, j)));
        }
    }

    cout << ret;
    return 0;
}