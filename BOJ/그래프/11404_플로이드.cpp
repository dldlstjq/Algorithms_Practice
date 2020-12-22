/*
플로이드 알고리즘을 사용해서 푸는 문제.
처음에 memset으로 adj를 초기화 했는데 초기화가 안됐다.
직접 for문을 돌려서 INF로 초기화 했고
98%에서 틀려 질문을 찾아보니 반례가 존재했다.
값이 INF인 경우 길이 없어 0을 출력해야했는데 INF값을 그대로 출력해서 틀렸다.
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
    for (int i = 0; i < V; ++i)adj[i][i] = 0;
    for (int k = 0; k < V; ++k)
        for (int i = 0; i < V; ++i)
            for (int j = 0; j < V; ++j)
                adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> V;
    cin >> E;

    //초기화. 처음에는 전부 INF.
    for (int i = 0; i < V; ++i)
        for (int j = 0; j < V; ++j)
            adj[i][j] = INF;


    for (int i = 0; i < E; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a - 1][b - 1] = min(adj[a - 1][b - 1], c);
    }
    floyd();

    //2 1 1 2 1 입력인 경우
    //2->1로 가는 길이 없어서 0이 나와야 하는데 INF가 들어있어 INF가 출력된다.
    //그 부분을 수정
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (adj[i][j] == INF || adj[i][j] == 0)
                cout << 0 << " ";
            else
                cout << adj[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}