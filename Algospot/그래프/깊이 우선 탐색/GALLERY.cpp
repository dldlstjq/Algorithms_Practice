/*
지배집합과 루트없는 트리라는 개념을 사용해야 한다.
dfs를 사용하면 코드가 간단해지는데 생각보다 간단해서
조금만 생각하면 풀 수 있을 것 같기도 하다.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_V = 1000 + 1;
int V;
vector<int> adj[MAX_V];
vector<bool> visited;
const int UNWATCHED = 0;
const int WATHCED = 1;
const int INSTALLED = 2;
//지금까지 설치한 카메라의 총 수
int installed;
//here로부터 깊이 우선 탐색을 하고, here의 정보를 반환한다.
int dfs(int here) {
    visited[here] = true;
    int children[3] = { 0,0,0 };
    for (int i = 0; i < adj[here].size(); ++i) {
        int there = adj[here][i];
        if (!visited[there])
            ++children[dfs(there)];
    }
    //자손 노드 중 감시되지 않은 노드가 있을 경우 카메라를 설치한다.
    if (children[UNWATCHED]) {
        ++installed;
        return INSTALLED;
    }
    //자손 노드 중 카메라가 설치된 노드가 있을 경우 설치할 필요가 없다.
    if (children[INSTALLED])
        return WATHCED;
    return UNWATCHED;
}

//그래프를 감시하는 데 필요한 카메라의 최소 수를 반환한다.
int installCamera() {
    installed = 0;
    visited = vector<bool>(V, false);
    for (int u = 0; u < V; ++u)
        if (!visited[u] && dfs(u) == UNWATCHED)
            ++installed;
    return installed;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int c;
    cin >> c;
    while (c--) {
        int h;
        cin >> V >> h;
        for (int i = 0; i < h; ++i) {
            int a, b;
            cin >> a >> b;
            adj[a].push_back(b);
            adj[b].push_back(a);

        }
        cout << installCamera() << "\n";
        for (int i = 0; i < V; ++i)
            adj[i].clear();
    }

    return 0;
}

