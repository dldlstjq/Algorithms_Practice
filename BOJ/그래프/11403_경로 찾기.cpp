/*
dfs로도 풀 수 있지만 플로이드 알고리즘으로도 풀 수 있다.
다른 정점을 거쳐 자기자신 혹은 다른 정점을 갈 수 있기 때문에 
플로이드 알고리즘을 적용한 후 값이 INF면 경로가 없고
INF가 아니면 경로가 있다는 것을 나타낸다.

처음엔 어떻게 적용해야 하나 싶었는데 다른 곳을 거쳐가면서 
가중치가 변경되어 새로운 경로가 생기는 것을 알 수 있었다.
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
                adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> V;

    for (int i = 0; i < V; ++i)
        for (int j = 0; j < V; ++j) {
            cin >> adj[i][j];
            if (adj[i][j] == 0)
                adj[i][j] = INF;
        }

    floyd();

    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (adj[i][j] == INF)
                cout << 0 << " ";
            else
                cout << 1 << " ";
        }
        cout << "\n";
    }

    return 0;
}