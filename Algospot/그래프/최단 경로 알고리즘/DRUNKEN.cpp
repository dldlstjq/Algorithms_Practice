/*
플로이드 알고리즘에 정점의 가중치를 더하는 것 까진 이해했다.
하지만 처음과 끝을 제외한 정점을 지나칠 때 하나의 가중치만 더해야 하는데
두 개 이상의 정점을 지날 때 두 개 가중치를 모두 더하게 되서 그걸 해결하지 못했다.

별도의 배열 W를 하나 더 선언해 거기다가 정답을 따로 저장했다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

const int INF = 1000000000;
const int MAX_V = 500 + 2;

//정점의 개수, 간선 개수
int V, E;

//그래프의 인접 행렬 표현.
//adj[u][v]=u에서 v로 가는 간선의 가중치. 간선이 없으면 아주 큰 값을 넣는다.
int adj[MAX_V][MAX_V];

//각 정점에서 음주 운전 단속을 할 때 걸리는 시간
int delay[MAX_V];
int W[MAX_V][MAX_V];

//플로이드의 모든 쌍 최단 거리 알고리즘
void floyd() {
    //모든 정점들을 예상 시간 별로 정렬한다.
    vector<pair<int, int>> order;
    for (int i = 0; i < V; ++i)
        order.push_back(make_pair(delay[i], i));
    sort(order.begin(), order.end());
    //정점을 하나도 거치지 않고 얻을 수 있는 최단 경로
    for (int i = 0; i < V; ++i)
        for (int j = 0; j < V; ++j)
            if (i == j)
                W[i][j] = 0;
            else
                W[i][j] = adj[i][j];
    int ret = INF;

    for (int k = 0; k < V; ++k) {
        //k번째로 예상 시간이 적게 걸리는 정점 w까지를 지나서 얻을 수 있는 최단 거리
        int w = order[k].second;
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                adj[i][j] = min(adj[i][j], adj[i][w] + adj[w][j]);
                W[i][j] = min(adj[i][w] + adj[w][j] + delay[w], W[i][j]);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> V >> E;
    for (int i = 0; i < V; ++i)
        cin >> delay[i];

    //초기화
    for (int i = 0; i < V; ++i)
        for (int j = 0; j < V; ++j)
            adj[i][j] = INF;


    for (int i = 0; i < E; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a - 1][b - 1] = c;
        adj[b - 1][a - 1] = c;
    }
    floyd();

    int t;
    cin >> t;
    while (t--) {
        int s, k;
        cin >> s >> k;
        cout << W[s - 1][k - 1] << "\n";
    }


    return 0;
}