/*
처음엔 BFS를 활용해서 풀려고 했었는데 최소값을 찾는데서 어려움을 겪었다.
정확한 정답이 있는 것이 아니라 최소를 찾아야 했기 때문에 큐에 모든 원소를 확인하면 시간초과가 날 것 같았다.

구글링 해보니 priority_queue라는 자료구조가 있었다. 
힙과 똑같은 개념인데 min_heap은 최솟값이 top에 있고 max_heap은 최대값이 top에 있다.
이를 이용하면 최소값만 빼내서 미로 끝까지 계산해서 답을 구할 수 있다.
또 하나의 자료구조를 배웠다.
*/


/*
2021.06.08 일반 큐를 이용하여 bfs를 실행하면 제대로 된 값이 안나온다.
벽이 있는 부분이랑 없는 부분이 섞이게 되는데 최소값이 가장 먼저 나와야 제대로 된 답이 나온다.
일반 큐는 벽을 부술 때가 먼저 나오면 그게 가장 먼저 계산된다. 그러면 출구 좌표가 true가 되어 
더 작은 값을 계산할 수가 없게 된다. 자세한건 예제2번 직접 해볼것
*/
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>

using namespace std;
#define MAX 102
int maze[MAX][MAX];
string str[MAX];
bool visited[MAX][MAX];
int dy[] = { -1,0,1,0 };
int dx[] = { 0,1,0,-1 };
int n, m;

//우선순위 큐를 이용한 bfs
int bfs() {
    priority_queue<pair<int, pair<int, int>>, vector< pair<int, pair<int, int>>>, greater< pair<int, pair<int, int>>>> pq;
    pq.push(make_pair(0, make_pair(0, 0)));
    visited[0][0] = true;

    while (!pq.empty()) {
        int y = pq.top().second.first;
        int x = pq.top().second.second;
        int ans = pq.top().first;
        pq.pop();

        if (y == n - 1 && x == m - 1) {
            return ans;
        }


        for (int i = 0; i < 4; i++) {
            int ny = y + dy[i];
            int nx = x + dx[i];
            if (0 <= ny && ny < n && 0 <= nx && nx < m) {
                if (!visited[ny][nx]) {
                    if (maze[ny][nx] == 1) {
                        pq.push(make_pair(ans + 1, make_pair(ny, nx)));
                    }
                    else
                        pq.push(make_pair(ans, make_pair(ny, nx)));
                    visited[ny][nx] = true;
                }
            }
        }

    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> m >> n;

    for (int i = 0; i < n; i++) {
        cin >> str[i];
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            maze[i][j] = str[i][j] - '0';


    cout << bfs();

    return 0;
}