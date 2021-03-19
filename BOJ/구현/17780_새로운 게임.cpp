/*
삽질에 삽질을 거듭하여 해결하지 못했다.
벡터 페어로 저장하는것이 익숙하여 그렇게 했더니 값에 접근할때 first,second로 접근하니
그게 좌표인지 방향인지 의미하는게 헷갈렸고 값을 직접 저장할떄도 코드가 길어졌다.
다음부턴 구조체를 활용해서 한결 보기 좋게 코드를 구현하면 값에 접근도 쉬위지고 알아보기도 편할것 같다.

이동하는 것 까진 좋은데 빨간칸인 경우 이동한 후 뒤집어야하고 파란색이면 방향만 바꿔서 한칸 이동해야한다.
문제이해는 됐는데 값을 변경하는 과정에서 제대로 안되거나 체스말 쌓이는 게 잘 안됐던 것 같다.

특별한 알고리즘을 필요로 하는 것도 아닌데 쉽게 해결하지 못하는걸보니 구현 부분도 많은 연습이 필요하다고 느꼈다.
*/

#include<iostream>
#include<vector>
using namespace std;

struct horse
{
	int x, y, d;
	bool is_bottom;
} h[10];

int N, K;
int dx[] = { 0, 0, 0, -1, 1 };
int dy[] = { 0, 1, -1, 0, 0 };
int turn[] = { 0, 2, 1, 4, 3 };
int color[13][13];
vector<int> info[13][13];

int move(int i)
{
	int tx = h[i].x + dx[h[i].d];
	int ty = h[i].y + dy[h[i].d];

	// 2. 경계를 넘거나 파란 칸
	if (tx <= 0 || ty <= 0 || tx > N || ty > N || color[tx][ty] == 2)
	{
		// 방향 전환
		h[i].d = turn[h[i].d];

		tx = h[i].x + dx[h[i].d];
		ty = h[i].y + dy[h[i].d];

		// 반대 방향도 파랑
		if (tx <= 0 || ty <= 0 || tx > N || ty > N || color[tx][ty] == 2)
			return 0;
	}

	vector<int>& cur = info[h[i].x][h[i].y];
	vector<int>& next = info[tx][ty];
	// 3. 하얀 칸
	if (color[tx][ty] == 0)
	{
		if (!next.empty()) h[cur.front()].is_bottom = false;
		next.insert(next.end(), cur.begin(), cur.end());
	}
	// 4. 빨간 칸
	else if (color[tx][ty] == 1)
	{
		next.insert(next.end(), cur.rbegin(), cur.rend());
		h[next.back()].is_bottom = false;
		h[next.front()].is_bottom = true;
	}
	h[next.front()].x = h[next.back()].x = tx;
	h[next.front()].y = h[next.back()].y = ty;
	cur.clear();
	return next.size();
}

int simulation()
{
	register int round, i, tx, ty, stack_cnt;

	// 라운드 반복
	for (round = 1; round <= 1000; ++round)
	{
		// 1. 자기 차레에 가장 아래에 있다면 이동
		for (i = 0; i < K; ++i)
		{
			if (h[i].is_bottom)
			{
				stack_cnt = move(i);

				// 5. 말이 4 이상 쌓이면 종료
				if (stack_cnt >= 4)
					return round;
			}
		}
	}
	return -1;
}

int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> N >> K;
	register int i, j;
	for (i = 1; i <= N; ++i)
		for (j = 1; j <= N; ++j)
			cin >> color[i][j];

	for (i = 0; i < K; ++i)
	{
		horse& ho = h[i];
		cin >> ho.x >> ho.y >> ho.d;
		ho.is_bottom = true;
		info[ho.x][ho.y].push_back(i);
	}
	cout << simulation();
	return 0;
}



///////////////////////////////////////////////////////////////
//몇시간을 들여 짠 코드. 마지막 예제를 통과하지 못한다.
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

int N, K;
int board[12][12];
int dy[4] = { 0,0,-1,1 };
int dx[4] = { 1,-1,0,0 };
vector<pair<pair<int, int>, pair<bool, int>>> chess; //체스말 정보 저장
vector<int> state[12][12];  //체스말 몇개인지 저장

bool is_in(int y, int x) {
    return (0 <= y && y < N && 0 <= x && x < N);
}

int turn(int dir) {
    if (dir == 0)return 1;
    else if (dir == 1)return 0;
    else if (dir == 2)return 3;
    else if (dir == 3)return 2;
}

int move(int idx) {
    int y = chess[idx].first.first;
    int x = chess[idx].first.second;
    bool bottom = chess[idx].second.first;
    int dir = chess[idx].second.second;

    int ny = y + dy[dir];
    int nx = x + dx[dir];

    //범위 벗어났거나 파란칸
    if (!is_in(ny, nx) || board[ny][nx] == 2) {
        //방향 전환
        dir = turn(dir);
        chess[idx].second.second = dir;
        ny = y + dy[dir];
        nx = x + dx[dir];
        //방향을 바꿨는데도 범위 벗어나거나 파란칸이면 종료
        //바뀐 값이 없다.
        if (!is_in(ny, nx) || board[ny][nx] == 2) {
            return 0;
        }

    }

    //하얀 칸
    if (is_in(ny, nx) && board[ny][nx] == 0) {
        //이동하려는 칸에 말이 있으면 맨 밑이 아니다.
        if (!state[ny][nx].empty()) {
            chess[idx].second.first = false;
        }
        //(y,x)칸에 있는 말을 모두 다음 칸으로 옮긴다.
        for (int j = 0; j < state[y][x].size(); ++j) {
            state[ny][nx].push_back(state[y][x][j]);
            //chess[state[y][x][j]].first.first = ny;  //좌표도 같이 업데이트
            //chess[state[y][x][j]].first.second = nx;
        }
    }

    //빨간 칸
    else if (is_in(ny, nx) && board[ny][nx] == 1) {
        //이동하려는 칸에 말이 있으면 맨 밑이 아니다.
        if (!state[ny][nx].empty()) {
            chess[idx].second.first = false;
        }
        //(y,x)칸에 있는 말을 모두 다음 칸으로 옮긴다.
        for (int j = 0; j < state[y][x].size(); ++j) {
            state[ny][nx].push_back(state[y][x][j]);
            //chess[state[y][x][j]].first.first = ny;  //좌표도 같이 업데이트
            //chess[state[y][x][j]].first.second = nx;
        }
        //현재 위치의 말을 뒤집는다.
        //맨 밑과 맨 위의 is_bottom을 바꿔준다.
        //단, 말이 하나밖에 없는 경우에는 안해줘도 된다.
        if (state[ny][nx].size() >= 2) {
            reverse(state[ny][nx].begin(), state[ny][nx].end());
            chess[state[ny][nx].front()].second.first = true;
            chess[state[ny][nx].back()].second.first = false;
        }

    }
    //이동한 체스판의 좌표에 있는 말의 맨 밑과 맨 위 좌표만 이동한 좌표로 바꿔준다.
    //가운데 있는건 맨 밑이 될 수 없기 때문에 더 이상 상관없다.
    chess[state[ny][nx].front()].first.first = ny;
    chess[state[ny][nx].front()].first.second = nx;
    chess[state[ny][nx].back()].first.first = ny;
    chess[state[ny][nx].back()].first.second = nx;
    state[y][x].clear();
    return state[ny][nx].size();
}

int solve() {
    int cnt = 0;
    for (int t = 1; t <= 1000; ++t) {
        for (int i = 0; i < K; ++i) {
            bool is_bottom = chess[i].second.first;
            if (is_bottom) {
                cnt = move(i);
                //말이 4개이상 쌓이면 종료
                if (cnt >= 4)
                    return t;
            }
        }
    }
    return -1;
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> K;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            cin >> board[i][j];

    for (int i = 0; i < K; ++i) {
        int y, x, dir;
        cin >> y >> x >> dir;
        //체스말 좌표, 맨 밑인지 여부와 방향 페어로 저장
        chess.push_back({ {y - 1,x - 1},{true,dir - 1} });
        state[y - 1][x - 1].push_back(i);   //체스판 상태
    }

    cout << solve();

    return 0;
}