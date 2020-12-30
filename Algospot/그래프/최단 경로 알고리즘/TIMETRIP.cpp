/*
코드는 어느정도 이해가 갔는데 입,출력 과정에 문제가 있다.
다시 풀어볼것
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

const int INF = 987654321;
const int MAX_V = 100 + 1;

//정점의 개수, 간선 개수
int V, E;
//그래프의 인접리스트. (연결된 정점 번호, 간선 가중치) 쌍을 담는다.
vector<pair<int, int>> adj[MAX_V];
//reachable[u][v]=u에서 v로 가는 경로가 있는가?
bool reachable[MAX_V][MAX_V];
//src에서 target으로 가는 최단 거리를 계산한다.
//가중치가 음의 무한대인 경로가 있으면 -INF를 반환한다.
pair<int, int> bellman2(int src, int target) {
    //시작점을 제외한 모든 정점까지의 최단 거리 상한을 INF로 둔다.
    vector<pair<int, int>> upper(V, { INF,INF });
    upper[src].first = upper[src].second = 0;
    //V-1번 순회한다.
    for (int iter = 0; iter < V - 1; ++iter)
        for (int here = 0; here < V; ++here)
            for (int i = 0; i < adj[here].size(); ++i) {
                int there = adj[here][i].first;
                int cost = adj[here][i].second;
                //(here, there)간선을 따라 완화를 시도한다.
                upper[there].first = min(upper[there].first, upper[here].first + cost);
                upper[there].second = max(upper[there].second, upper[here].second + cost);
                reachable[here][there] = true;
            }
    //음수 사이클의 존재 여부를 확인하자.
    for (int here = 0; here < V; ++here)
        for (int i = 0; i < adj[here].size(); ++i) {
            int there = adj[here][i].first;
            int cost = adj[here][i].second;
            //완화가 성공한다면 here는 음수 사이클에 들어 있다.
            if (upper[here].first + cost < upper[there].first)
                //이 음수 사이클을 포함하는 경로가 있는가?
                if (reachable[src][here] && reachable[here][target])
                    return { -INF, -INF };
        }
    return upper[target];
}



int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int c;
    cin >> c;
    while (c--) {

        cin >> V >> E;
        vector<int> a(E, 0);
        vector<int> b(E, 0);
        for (int i = 0; i < E; ++i) {
            int d;
            cin >> a[i] >> b[i] >> d;
            adj[a[i]].push_back({ b[i],d });
        }
        pair<int, int> ans = bellman2(a[0], 1);
        if (ans.first == -INF)
            cout << "INFINITY" << " " << ans.second << "\n";
        else if (ans.second == INF)
            cout << ans.first << " " << "INFINITY" << "\n";
        else if (ans.first == INF && ans.second == INF)
            cout << "UNREACHABLE" << "\n";
        else
            cout << ans.first << " " << ans.second << "\n";

    }

    return 0;
}