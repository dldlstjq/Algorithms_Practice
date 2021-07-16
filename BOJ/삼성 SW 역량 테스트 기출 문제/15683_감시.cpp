/*
가장 많이 틀리고 못푸는 유형중에 한문제인것 같다.

dfs를 통해 계산을 하는데 계산하고 난 후 이전의 배열 값을 다시 저장해줘야 하는 유형의 문제인데
이 부분에서 많이 약한 것 같다.
우선 dfs 실행전 임시 배열에 원본배열을 복사하고 난 후 원본배열에 계산한다.
dfs가 끝나면 값이 바뀐 원본배열에 임시배열을 복사해주면 이전 값이 들어가서 제대로 된 계산이 나오는 것 같다.

아니면 함수 인자에 배열을 넣어서 진행하는 방법도 괜찮은 것 같다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAX = 8 + 1;
int N, M;
int map[MAX][MAX];

int ret = 987654321;

//북동남서 순서
int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };

vector<pair<int, int>> v; //cctv 좌표저장

//감시 영역 표시
void check(int y, int x, int dir) {

    //굳이 dir 값에 따라 조건 안나누고 while하나로 처리하면 될 것 같다.
    while (1) {
        y += dy[dir]; x += dx[dir];
        if (!(0 <= y && y < N && 0 <= x && x < M))
            break;

        if (map[y][x] == 6)
            break;
        else if (map[y][x] == 0)
            map[y][x] = -1;
    }


    /*if (dir == 0) {
        for (int i = y - 1; i >= 0; --i) {
            if (map[i][x] == 6)
                break;
            else if (map[i][x] == 0)
                map[i][x] = -1;
        }
    }

    if (dir == 1) {
        for (int i = x + 1; i < M; ++i) {
            if (map[y][i] == 6)
                break;
            else if (map[y][i] == 0)
                map[y][i] = -1;
        }
    }

    if (dir == 2) {
        for (int i = y + 1; i < N; ++i) {
            if (map[i][x] == 6)
                break;
            else if (map[i][x] == 0)
                map[i][x] = -1;
        }
    }

    if (dir == 3) {
        for (int i = x - 1; i >= 0; --i) {
            if (map[y][i] == 6)
                break;
            else if (map[y][i] == 0)
                map[y][i] = -1;
        }
    }*/
}


void solve(int idx) {
    //기저사례: 모든 cctv를 다 조사
    if (idx == v.size()) {
        //사각지대 조사
        int cnt = 0;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                if (map[i][j] == 0)
                    cnt++;
        ret = min(ret, cnt);
        return;
    }

    int y = v[idx].first;
    int x = v[idx].second;

    int tmp[MAX][MAX] = { 0 };
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            tmp[i][j] = map[i][j];

    if (map[y][x] == 1) {
        for (int d = 0; d < 4; ++d) {
            check(y, x, d);
            solve(idx + 1);
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < M; ++j)
                    map[i][j] = tmp[i][j];

        }
    }

    else if (map[y][x] == 2) {
        for (int d = 0; d < 2; ++d) {
            check(y, x, d);
            check(y, x, d + 2);
            solve(idx + 1);
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < M; ++j)
                    map[i][j] = tmp[i][j];

        }
    }

    else if (map[y][x] == 3) {
        for (int d = 0; d < 4; ++d) {
            check(y, x, d);
            check(y, x, (d + 1) % 4);
            solve(idx + 1);
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < M; ++j)
                    map[i][j] = tmp[i][j];

        }
    }

    else if (map[y][x] == 4) {
        for (int d = 0; d < 4; ++d) {
            check(y, x, d);
            check(y, x, (d + 1) % 4);
            check(y, x, (d + 2) % 4);
            solve(idx + 1);
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < M; ++j)
                    map[i][j] = tmp[i][j];

        }
    }
    else if (map[y][x] == 5) {
        for (int d = 0; d < 4; ++d) {
            check(y, x, d);
        }
        solve(idx + 1);
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                map[i][j] = tmp[i][j];

    }


}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j) {
            cin >> map[i][j];
            if (map[i][j] != 0 && map[i][j] != 6)
                v.push_back({ i,j });
        }


    solve(0);
    cout << ret;

    return 0;
}