/*
다익스트라 알고리즘을 사용하여 최단경로를 구한다.
우선순위 큐를 이용하는데 자세한 알고리즘은 코드를 보는 것이 빠르다.
데이터 입력 시 0부터 시작하기 위해 입력값을 1씩 빼준다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

const int MAX_V = 20000 + 1;
const int INF = 987654321;

//정점의 개수
int V, E;
//그래프의 인접리스트. (연결된 정점 번호, 간선 가중치) 쌍을 담는다.
vector<pair<int, int>> adj[MAX_V];
vector<int> dijkstra(int src) {
    vector<int> dist(V, INF);
    dist[src] = 0;
    priority_queue<pair<int, int>> pq;
    pq.push({ 0,src });

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

    cin >> V >> E;
    int start;
    cin >> start;
    for (int i = 0; i < E; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u - 1].push_back({ v - 1,w });
    }

    vector<int> ans = dijkstra(start - 1);
    for (int i = 0; i < V; ++i)
        if (ans[i] == INF)
            cout << "INF" << "\n";
        else
            cout << ans[i] << "\n";
    return 0;
}



/////////////////////////////////////////
/*
정점의 수가 적거나 간선의 수가 매우 많은 경우 우선순위 큐 사용하지 않고
다른 방법이 있다. 이 문제에서는 시간초과가 나지만 위의 방법으로 안될 때 사용하면 될 것 같다.
*/

vector<int> dijkstra2(int src) {
    vector<int> dist(V, INF);
    //각 정점을 방문했는지 여부를 저장한다.
    vector<bool> visited(V, false);
    dist[src] = 0; visited[src] = false;
    while (true) {
        //아직 방문하지 않은 정점 중 가장 가까운 정점을 찾는다.
        int closest = INF, here;
        for (int i = 0; i < V; ++i)
            if (dist[i] < closest && !visited[i]) {
                here = i;
                closest = dist[i];
            }
        if (closest == INF)break;
        //가장 가까운 정점을 방문한다.
        visited[here] = true;
        for (int i = 0; i < adj[here].size(); ++i) {
            int there = adj[here][i].first;
            if (visited[there])continue;
            int nextDist = dist[here] + adj[here][i].second;
            dist[there] = min(dist[there], nextDist);
        }
    }
    return dist;
}