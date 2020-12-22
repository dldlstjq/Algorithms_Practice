/*
dfs나 bfs로도 풀 수 있지만 플로이드 알고리즘으로도 풀 수 있다.
다른 정점을 거쳐 자기자신 혹은 다른 정점을 갈 수 있기 때문에 
처음엔 블로그를 참고했지만 종만북에 친절히 가중치 없는 그래프에서
각 정점 간 도달 가능성 여부 계산 방법이 나왔다.

최소치 연산을 OR, 덧셈을 AND로 바꾸면 간단하게 구할 수 있다.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1000000000;
const int MAX_V = 100 + 2;

//정점의 개수, 간선 개수
int V, E;
//그래프의 인접 행렬 표현.
//adj[u][v]=u에서 v로 가는 간선의 가중치. 간선이 없으면 아주 큰 값을 넣는다.
int adj[MAX_V][MAX_V];
//플로이드의 모든 쌍 최단 거리 알고리즘
void floyd() {
    for (int k = 0; k < V; ++k)
        for (int i = 0; i < V; ++i)
            for (int j = 0; j < V; ++j)
                adj[i][j] = adj[i][j] || (adj[i][k] && adj[k][j]);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> V;

    for (int i = 0; i < V; ++i)
        for (int j = 0; j < V; ++j) {
            cin >> adj[i][j];
        }

    floyd();

    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            cout << adj[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}