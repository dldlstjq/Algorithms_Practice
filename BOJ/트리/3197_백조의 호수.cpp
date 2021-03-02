/*
14868 문명 이랑 비슷한 문제라고 해서 그나마 쉽게 해결할 줄 알았는데 아니었다.
문명문제에서는 특정 좌표가 주어져서 거기에만 번호를 붙여 유니온 파인드를 해결하면 됐지만
여기서는 2차원 배열의 좌표를 1차원 배열 parent 인덱스에 표현해야 했기 때문에 거기서 적용하는데 어려웠지 않나 생각한다.
2차원 배열의 좌표를 1차원 배열의 인덱스로 전환하는 방법은 행의 수x현재 열의 좌표+현재 행의 좌표로 구하면 됐다.
매치 시킨 다음 백조의 좌표를 배열에 저장해둔다. 그리고 얼음인 부분을 녹이면서 같은 집합에 속하는지 판단하면 해결할 수 있었다.

같은 집합인지 찾는 find만 필요하고 합치는 merge는 사용하지 않아도 됐다.
유니온 파인드 문제가 직접적으로 쓰라하지 않고 문제를 풀면서 유형을 익혀야 하기 때문에
어렵게 느껴진다고 생각한다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

//호수가 최대 1500x1500이어서 전체 칸 갯수는 2250000개이다.
int parent[2250000];

char map[1501][1501];
int r, c;

int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };

queue<pair<int, int>> q;
vector<int> swan;

//u가 속한 트리의 루트의 번호를 반환한다.
int find(int u) {
	if (u == parent[u])return u;
	//u의 부모를 찾을 때 parent[u]에 부모를 저장해둬 다시 찾을 때도 재귀를 하지 않게 한다.
	return parent[u] = find(parent[u]);
}

bool isSafe(int y, int x) {
	return 0 <= y && y < r && 0 <= x && x < c;
}

void melt(int i, int j) {
	//얼음을 물로 바꿔주고 큐에 넣는다.
	map[i][j] = '.';
	q.push({ i,j });
	int x = find(c * i + j), y;
	for (int k = 0; k < 4; ++k) {
		int ni = i + dy[k], nj = j + dx[k];
		//범위에 들어오고 물인 경우 같은 집합에 속하는 확인한다.
		//다른 집합이면 y를 x 집합에 넣는다.
		if (isSafe(ni, nj) && map[ni][nj] == '.') {
			y = find(c * ni + nj);
			if (x != y)
				parent[y] = x;
		}
	}
}

int solve() {
	int ans = 0;
	while (!q.empty()) {
		//두 마리가 같은 집합이면 그대로 종료
		if (find(swan[0]) == find(swan[1]))
			return ans;
		int len = q.size();
		for (int i = 0; i < len; ++i) {
			int y = q.front().first, x = q.front().second;
			q.pop();
			for (int j = 0; j < 4; ++j) {
				int ni = y + dy[j], nj = x + dx[j];
				//범위안에 있고 얼음이면 녹인다.
				if (isSafe(ni, nj) && map[ni][nj] == 'X')
					melt(ni, nj);
			}
		}
		++ans;
	}
	return -1;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	for (int i = 0; i < 2250000; ++i)
		parent[i] = i;

	cin >> r >> c;

	for (int i = 0; i < r; ++i) {
		cin >> map[i];
		for (int j = 0; j < c; ++j) {
			if (map[i][j] != 'X') {
				if (map[i][j] == 'L') {
					//각 칸을 0부터 오름차순으로 표현할 때 해당하는 수
					swan.push_back(c * i + j);
				}
				melt(i, j);
			}
		}
	}

	cout << solve();
	return 0;
}


///////////////////////////////////////////////////////
//bfs 두번을 이용한 다른 풀이
#include<iostream>
#include<cstring>
#include<vector>
#include<queue>

#define endl "\n"
#define MAX 1500
using namespace std;

int R, C;
bool Find;
char MAP[MAX][MAX];
bool Visit[MAX][MAX];

int dx[] = { 0, 0, 1, -1 };
int dy[] = { 1, -1, 0, 0 };

queue<pair<int, int>> Swan_Q, Swan_NQ, Q, NQ;
pair<int, int> Swan_Pos;

void Input()
{
    Find = false;
    cin >> R >> C;
    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            cin >> MAP[i][j];
            if (MAP[i][j] != 'X') Q.push(make_pair(i, j));
            if (MAP[i][j] == 'L')
            {
                Swan_Pos.first = i;
                Swan_Pos.second = j;
            }
        }
    }
}

void Swan_BFS()
{
    while (Swan_Q.empty() == 0 && Find == false)
    {
        int x = Swan_Q.front().first;
        int y = Swan_Q.front().second;
        Swan_Q.pop();

        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && ny >= 0 && nx < R && ny < C)
            {
                if (Visit[nx][ny] == false)
                {
                    if (MAP[nx][ny] == '.')
                    {
                        Visit[nx][ny] = true;
                        Swan_Q.push(make_pair(nx, ny));
                    }
                    else if (MAP[nx][ny] == 'L')
                    {
                        Visit[nx][ny] = true;
                        Find = true;
                        break;
                    }
                    else if (MAP[nx][ny] == 'X')
                    {
                        Visit[nx][ny] = true;
                        Swan_NQ.push(make_pair(nx, ny));
                    }
                }
            }
        }
    }
}

void Water_BFS()
{
    while (Q.empty() == 0)
    {
        int x = Q.front().first;
        int y = Q.front().second;
        Q.pop();

        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && ny >= 0 && nx < R && ny < C)
            {
                if (MAP[nx][ny] == 'X')
                {
                    MAP[nx][ny] = '.';
                    NQ.push(make_pair(nx, ny));
                }
            }
        }
    }
}

void Solution()
{
    int Day = 0;
    Swan_Q.push(make_pair(Swan_Pos.first, Swan_Pos.second));
    Visit[Swan_Pos.first][Swan_Pos.second] = true;

    while (Find == false)
    {
        Swan_BFS();

        if (Find == false)
        {
            Water_BFS();
            Q = NQ;
            Swan_Q = Swan_NQ;

            while (NQ.empty() == 0) NQ.pop();
            while (Swan_NQ.empty() == 0) Swan_NQ.pop();
            Day++;
        }
    }
    cout << Day << endl;
}

void Solve()
{
    Input();
    Solution();
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    Solve();

    return 0;
}