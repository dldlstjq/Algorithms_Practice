/*
이 문제에서 그래프를 생각하는게 쉽지 않다.
풀이를 봐도 딱 와닿지 않아 다음에 볼때 제대로 봐야겠다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <functional>
#include <float.h>

using namespace std;

const int INF = 987654321;

//정점의 개수
int V;
//그래프의 인접리스트. (연결된 정점 번호, 간선 가중치) 쌍을 담는다.
vector<pair<int, int>> adj[410];
const int START = 401;

vector<int> dijkstra(int src) {
    vector<int> dist(400, INF);
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

//(A국 선수의 예상시간-B국 선수의 예상시간)의 정점 번호를 반환한다.
int vertex(int delta) {
    return delta + 200;
}

//a[]=A국 선수의 종목별 예상시간
//b[]=B국 선수의 종목별 예상시간
int solve(const vector<int>& a, const vector<int>& b) {
    //그래프를 만든다.
    V = 402;
    for (int i = 0; i < V; ++i)
        adj[i].clear();
    for (int i = 0; i < a.size(); ++i) {
        int delta = a[i] - b[i];
        adj[START].push_back({ vertex(delta),a[i] });
    }
    //현재 차이
    for (int delta = -200; delta <= 200; ++delta) {
        //i번 종목을 뒤에 붙인다면?
        for (int i = 0; i < a.size(); ++i) {
            int next = delta + a[i] - b[i];
            //시간 차이의 절대 값이 200을 넘는 정점은 만들 필요가 없다.
            if (abs(next) > 200)continue;
            adj[vertex(delta)].push_back({ vertex(next),a[i] });
        }
    }
    vector<int> shortest = dijkstra(START);
    int ret = shortest[vertex(0)];
    if (ret == INF)return -1;
    return ret;

}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int c;
    cin >> c;
    while (c--) {
        int m;
        cin >> m;
        vector<int> a(m, 0), b(m, 0);
        for (int i = 0; i < m; ++i)
            cin >> a[i] >> b[i];

        int ans = solve(a, b);
        if (ans == -1)
            cout << "IMPOSIBBLE" << "\n";
        else
            cout << solve(a, b) << "\n";
    }


    return 0;
}