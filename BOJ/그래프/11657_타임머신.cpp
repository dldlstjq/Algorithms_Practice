/*
벨만 포드 알고리즘을 사용해서 푸는 문제.
처음에는 출력 초과가 나서 자료형을 long long으로 바꿔주었다.
그래도 오답이 나와서 간선 완화 조건문에서 upper[here]!=INF로 바꿔주니 정답을 맞았다.
아무래도 간선이 자기자신으로 가는 사이클을 고려하지 않아서 틀렸던 것 같다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

const long long INF = 1e18;
const int MAX_V = 500 + 1;

//정점의 개수, 간선 개수
int V, E;
//그래프의 인접리스트. (연결된 정점 번호, 간선 가중치) 쌍을 담는다.
vector<pair<int, int>> adj[MAX_V];
//음수 사이클이 있을 경우 텅 빈 배열을 반환
vector<long long> bellmanFord(int src) {
    //시작점을 제외한 모든 정점까지의 최단 거리 상한을 INF로 둔다.
    vector<long long> upper(V, INF);
    upper[src] = 0;
    bool updated;
    //V번 순회한다.
    for (int iter = 0; iter < V; ++iter) {
        updated = false;
        for (int here = 0; here < V; ++here)
            for (int i = 0; i < adj[here].size(); ++i) {
                int there = adj[here][i].first;
                int cost = adj[here][i].second;
                //(here, there)간선을 따라 완화를 시도한다.
                if (upper[here] != INF && upper[there] > upper[here] + cost) {
                    //성공
                    upper[there] = upper[here] + cost;
                    updated = true;
                }
            }
        //모든 간선에 대해 완화가 실패했을 경우 V-1번 돌 필요 없이 곧장 종료한다.
        if (!updated)break;
    }
    //V번째 순회에서도 완화가 성공했다면 음수 사이클이 있다.
    if (updated)upper.clear();
    return upper;
}



int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> V >> E;
    for (int i = 0; i < E; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a - 1].push_back({ b - 1,c });
    }

    vector<long long> ans = bellmanFord(0);

    //빈 배열이면 음수 사이클이 존재한다.
    if (ans.empty())
        cout << -1 << "\n";
    else {
        for (int i = 1; i < ans.size(); ++i)
            if (ans[i] == INF)
                cout << -1 << "\n";
            else
                cout << ans[i] << "\n";
    }
    return 0;
}