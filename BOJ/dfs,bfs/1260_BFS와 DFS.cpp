/*
첫번째는 인접행렬 사용.
*/
#include <iostream>
#include <queue>

using namespace std;

#define MAX 1001
int map[MAX][MAX];
int visited[MAX];
int n, m, v;

void dfs(int start) {
    cout << start << " ";
    visited[start] = true;
    for (int i = 1; i <= n; i++) {
        if (map[start][i] && !visited[i])
            dfs(i);
    }
}

void bfs(int start) {
    queue <int> q;
    q.push(start);
    visited[start] = true;
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        cout << x << " ";
        for (int i = 1; i <= n; i++) {
            if (map[x][i] && !visited[i]) {
                q.push(i);
                visited[i] = true;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> v;

    int v1, v2;

    for (int i = 1; i <= m; i++) {
        cin >> v1 >> v2;
        map[v1][v2] = 1;
        map[v2][v1] = 1;
    }

    dfs(v);
    cout << "\n";

    for (int i = 0; i < MAX; i++)
        visited[i] = false;

    bfs(v);
    cout << "\n";


    return 0;
}


//////////////////////////
/*
두번쨰는 인접리스트 사용
출력순서에 맞게 될려면 데이터 삽입 후 정렬 해줘야함.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

#define MAX 1001
vector<int> graph[MAX];
int visited[MAX];
int n, m, v;

void dfs(int start) {
    cout << start << " ";
    visited[start] = true;
    for (int i = 0; i < graph[start].size(); i++) {
        int next = graph[start][i];
        if (!visited[next]) {
            dfs(next);
        }
    }

}

void bfs(int start) {
    queue <int> q;
    q.push(start);
    visited[start] = true;
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        cout << x << " ";
        for (int i = 0; i < graph[x].size(); i++) {
            int next = graph[x][i];
            if (!visited[next]) {
                q.push(next);
                visited[next] = true;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> v;

    int v1, v2;

    for (int i = 1; i <= m; i++) {
        cin >> v1 >> v2;
        graph[v1].push_back(v2);
        graph[v2].push_back(v1);

    }

    //연결이 오름차순으로 되도록 정렬해줌
    for (int i = 1; i <= n; i++)
        sort(graph[i].begin(), graph[i].end());


    dfs(v);
    cout << "\n";

    for (int i = 0; i < MAX; i++)
        visited[i] = false;

    bfs(v);
    cout << "\n";

    return 0;
}