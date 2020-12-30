/*
처음에는 불난집이나 소방서에서 하나씩 다익스트라를 돌리면 될 줄 알았다.
하지만 책 풀이에서 이런 식으로 풀면 시간이 많이 걸린다고 했다.

양방향 bfs 했던 것을 생각해 각 소방서에서 동시에 다익스트라를 진행하면
될 것 같았고 문제를 풀 수 있었다.
이렇게 하면 한번의 다익스트라로 답을 구할 수 있다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

const int MAX_V = 1000 + 1;
const int INF = 987564321;

//정점의 개수
int V, E;
//그래프의 인접리스트. (연결된 정점 번호, 간선 가중치) 쌍을 담는다.
vector<pair<int, int>> adj[MAX_V];
vector<int> dijkstra(const vector<int>& station) {
    vector<int> dist(V, INF);

    //모든 소방서에서 동시에 다익스트라 수행
    priority_queue<pair<int, int>> pq;
    for (int i = 0; i < station.size(); ++i) {
        dist[station[i]] = 0;
        pq.push({ 0,station[i] });
    }

    //priority_queue는 기본적으로 가장 큰 원소가 위로 가도록 큐를 구성하기 때문에
    //거리의 부호를 바꿔서 거리가 작은 정점부터 꺼내지도록 한다.
    //그렇지 않으면  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; 로 선언해야 한다.
    while (!pq.empty()) {
        int cost = -pq.top().first;
        int here = pq.top().second;
        pq.pop();
        //만약 지금 꺼낸 것보다 더 짧은 경로를 알고 있다면 지금 꺼낸 것을 무시한다.
        if (dist[here] < cost)
            continue;
        for (int i = 0; i < adj[here].size(); ++i) {
            int there = adj[here][i].first;
            int nextDist = cost + adj[here][i].second;
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
        int n, m;
        cin >> V >> E >> n >> m;
        //초기화
        for (int i = 0; i < V; ++i)
            adj[i].clear();

        for (int i = 0; i < E; ++i) {
            int a, b, t;
            cin >> a >> b >> t;
            adj[a - 1].push_back({ b - 1, t });
            adj[b - 1].push_back({ a - 1, t });
        }

        vector<int> fire_house, station;
        for (int i = 0; i < n; ++i) {
            int tmp;
            cin >> tmp;
            fire_house.push_back(tmp - 1);
        }

        for (int i = 0; i < m; ++i) {
            int tmp;
            cin >> tmp;
            station.push_back(tmp - 1);
        }

        //다익스트라 수행
        vector<int> ans = dijkstra(station);

        //불난집까지 최소 거리를 더한다.
        int ret = 0;
        for (int i = 0; i < fire_house.size(); ++i) 
            ret += ans[fire_house[i]];
        
        cout << ret << "\n";
    }
    return 0;
}