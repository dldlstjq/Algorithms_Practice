/*
처음엔 dp 문제인줄 알고 dfs+dp로 접근했다.
테스트케이스는 맞았는데 시간초과가 났다.
아무래도 N이 커질수록 깊이가 깊어져서 시간초과가 나는 것 같았다.

최단거리를 구하기 때문에 BFS로 접근해서 최소비용을 갱신하는 방향으로 가면 더 쉽게 풀렸다.
주의할 점은 첫 시작할때는 방향이 무조건 직선이기 때문에 그 부분을 고려해 줘야 된다.
*/

#include <string>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

struct car {
    int y, x, cost, dir;
};

const int MAX = 25 + 1;

int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };

int N;

bool is_in(int y, int x) {
    return 0 <= y && y < N && 0 <= x && x < N;
}

int solution(vector<vector<int>> board) {
    int answer = 0;
    answer = 987654321;

    N = board.size();

    vector<vector<int>> road = board;
    road[0][0] = 0;
    queue<car> q;
    car Car = { 0,0,0,-1 }; //시작할때 방향을 -1로 줌. 
    q.push(Car);

    while (!q.empty()) {
        car now = q.front();
        q.pop();

        //도착지에 도착하면 answer 갱신
        if (now.y == N - 1 && now.x == N - 1) {
            answer = min(answer, now.cost);
            continue;
        }

        for (int i = 0; i < 4; ++i) {
            int ny = now.y + dy[i];
            int nx = now.x + dx[i];

            if (!is_in(ny, nx) || board[ny][nx] == 1)
                continue;

            int new_cost = now.cost;
            //방향이 같거나 현재 방향이 -1이면 직선도로
            if (i == now.dir || now.dir == -1) {
                new_cost += 100;
            }
            //아니면 코너
            else {
                new_cost += 600;
            }
            //해당 좌표가 값이 없거나 new_cost보다 크면 갱신
            if (road[ny][nx] == 0 || road[ny][nx] >= new_cost) {
                road[ny][nx] = new_cost;
                q.push({ ny,nx,new_cost,i });
            }
        }
    }

    return answer;
}


////////////////////////////
//첫 DFS+DP 풀이. 시간초과
#include <string>
#include <vector>
#include <iostream>
#include <cstring>
using namespace std;

const int MAX = 25 + 1;
const int INF = 987564321;

int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };
int cache[MAX][MAX][4];

int N;
vector<vector<int>> road;
int visited[MAX][MAX];

bool is_in(int y, int x) {
    return 0 <= y && y < N && 0 <= x && x < N;
}

int solve(int y, int x, int dir) {
    //목적지에 도착
    if (y == N - 1 && x == N - 1)
        return 0;

    int& ret = cache[y][x][dir];
    if (ret != INF)
        return ret;

    visited[y][x] = true;

    for (int i = 0; i < 4; ++i) {
        int ny = y + dy[i];
        int nx = x + dx[i];
        //범위 밖, 벽, 이미 지나온 곳이면 갈 수 없다.
        if (!is_in(ny, nx) || road[ny][nx] == 1 || visited[ny][nx])
            continue;
        if (i == dir) {
            //방향이 같으면 100원
            ret = min(ret, solve(ny, nx, i) + 100);
        }
        else {
            //방향이 달라진다는 건 코너. 코너를 바꿀 때 500+ 직선이 이어지기 때문에 100
            ret = min(ret, solve(ny, nx, i) + 600);
        }
    }
    visited[y][x] = false;    //백트래킹. 다시 false로 만들어 줘야함.

    return ret;
}

int solution(vector<vector<int>> board) {
    int answer = 0;

    N = board.size();

    for (int i = 0; i < MAX; ++i)
        for (int j = 0; j < MAX; ++j)
            for (int k = 0; k < 4; ++k)
                cache[i][j][k] = INF;

    memset(visited, false, sizeof(visited));    //방문여부 초기화

    road = board; //road에 board 복사

    //0,0에서 시작하면 오른쪽, 아래 둘 중에 하나
    visited[0][0] = true;
    answer = solve(0, 0, 1);    //오른쪽 먼저 갈때 최소값 구한다.
    memset(visited, false, sizeof(visited));    //방문여부 초기화. 그래야 밑으로 갈 때 비용을 따로 구할 수 있다.
    visited[0][0] = true;
    answer = min(answer, solve(0, 0, 2));


    return answer;
}