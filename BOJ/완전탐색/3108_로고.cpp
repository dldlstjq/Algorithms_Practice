/*
BFS, DFS를 이용해야 할것 같긴 했는데 정확하게 어떤 식으로 이용해야 하는지 몰랐다.
좌표 범위가 -500 ~ 500 이다. 하지만, 우리가 컴퓨터로 배열을 만든다면, 범위는 0부터 가능하다. 
따라서, 입력받는 좌표 값들에 +500 씩을 해서 받아준다.
그리고 사각형이 겹치는 부분이 있기 때문에 입력받는 좌표 값에 500을 더하고 x2를 해야 원하는 그림을 입력으로 받아낼 수 있단다.
그저 감탄밖에 안나온다.
따라서 최대 크기는 2001로 설정해야 한다.
그리고 마지막에 연필을 들어올리지 않고도 사각형을 그릴 수 있기 때문에 1을 빼줘야 정확한 답이 나온다.
자세한건 코드 참고
*/
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;
#define MAX 2001
int graph[MAX][MAX];
bool visited[MAX][MAX];
int dx[] = { 0, 0, 1, -1 };
int dy[] = { 1, -1, 0, 0 };

int n;

void dfs(int y, int x) {
    graph[y][x] = 2;    //방문표시
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (0 <= nx && nx < MAX && 0 <= ny && ny < MAX) {
            //graph[y][x]==1이면 방문 안한 직사각형
            if (graph[ny][nx] == 1) {
                dfs(ny, nx);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;

    for (int i = 0; i < n; i++) {
        int x1, x2, y1, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        //범위가 -500~500이기 때문에 500 더하고 겹치는 부분 때문에 *2 해줌
        x1 = (x1 + 500) * 2;
        x2 = (x2 + 500) * 2;
        y1 = (y1 + 500) * 2;
        y2 = (y2 + 500) * 2;

        //직사각형 표시
        for (int i = x1; i <= x2; i++) {
            graph[y1][i] = 1;
            graph[y2][i] = 1;
        }

        for (int i = y1; i <= y2; i++) {
            graph[i][x1] = 1;
            graph[i][x2] = 1;
        }
    }

    memset(visited, false, sizeof(visited));

    //직사각형인 부분 dfs
    int pu_cnt = 0;
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            if (graph[i][j] == 1) {
                dfs(i, j);
                pu_cnt++;
            }
        }

    }

    /*거북이가 처음에 있는 위치인 (0, 0) 에서가 아닌, 우리의 입력방식대로 바꾼 (1000, 1000) 에도 사각형이
   존재한다면, 연필을 들어올리지 않고 바로 사각형을 그릴 수가 있다. 즉, MAP[1000][1000] = 2 라면, 연필을 들어올린 횟수를
   1회 빼줘야 한다는 점을 생각해 줘야 한다 !*/

    if (graph[1000][1000] == 2)
        pu_cnt--;

    cout << pu_cnt;
    return 0;
}