/*
기존의 다익스트라 코드를 조금 수정해야 한다.
더하는 것이 아니라 곱하기 때문에 초기값을 1로 줘야하고
큐에 삽입할때 -1을 넣어줘야 한다.

결정적으로 그래프를 저장하는 adj를 초기화 안해줘서 몇 번이고 런타임 오류가 났다.
이런 실수를 안 하기 위해서 데이터 입력 시 무조건 초기화하는 버릇을 들여야겠다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <functional>
#include <float.h>

using namespace std;

const int MAX_V = 10000 + 1;
const double INF = DBL_MAX;

//정점의 개수
int V, E;
//그래프의 인접리스트. (연결된 정점 번호, 간선 가중치) 쌍을 담는다.
vector<pair<int, double>> adj[MAX_V];
vector<double> dijkstra(int src) {
    vector<double> dist(V, INF);
    dist[src] = 1.0;
    priority_queue<pair<double, int>> pq;
    pq.push({ -1.0,src });

    //priority_queue는 기본적으로 가장 큰 원소가 위로 가도록 큐를 구성하기 때문에
    //거리의 부호를 바꿔서 거리가 작은 정점부터 꺼내지도록 한다.
    //그렇지 않으면  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; 로 선언해야 한다.
    while (!pq.empty()) {
        double cost = -pq.top().first;
        int here = pq.top().second;
        pq.pop();
        //만약 지금 꺼낸 것보다 더 짧은 경로를 알고 있다면 지금 꺼낸 것을 무시한다.
        if (dist[here] < cost)
            continue;
        for (int i = 0; i < adj[here].size(); ++i) {
            int there = adj[here][i].first;
            double nextDist = cost * adj[here][i].second;
            //더 짧은 경로를 발견하면, dist[]를 갱신하고 우선순위 큐에 넣는다.
            if (dist[there] > nextDist) {
                dist[there] = nextDist;
                pq.push({ -nextDist,there });
            }

        }
    }
    return dist;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int c;
    cin >> c;
    while (c--) {
        cin >> V >> E;
        //초기화
        for (int i = 0; i < V; ++i)
            adj[i].clear();

        for (int i = 0; i < E; ++i) {
            int a, b;
            long double c;
            cin >> a >> b >> c;
            adj[a].push_back({ b, c });
            adj[b].push_back({ a, c });
        }

        vector<double> ans = dijkstra(0);
        cout << fixed;
        cout.precision(10);
        cout << ans[V - 1] << "\n";

    }


    return 0;
}