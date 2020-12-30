/*
크루스칼 알고리즘을 변형하면 문제를 쉽게 풀 수 있다.
아직 이해가 잘 안돼 나중에 볼 때 더 자세히 봐야겠다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct DisjointSet {
    vector<int> parent, rank;
    DisjointSet(int n) :parent(n), rank(n, 1) {
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }
    //u가 속한 트리의 루트의 번호를 반환한다.
    int find(int u)const {
        if (u == parent[u])return u;
        return find(parent[u]);
    }
    //u가 속한 트리와 v가 속한 트리를 합친다.
    void merge(int u, int v) {
        u = find(u); v = find(v);
        //u와 v가 이미 같은 트리에 속하는 경우를 걸러낸다.
        if (u == v)return;
        if (rank[u] > rank[v])swap(u, v);
        //이제 rank[v]가 항상 rank[u] 이상이므로 u를 v의 자식으로 넣는다.
        parent[u] = v;
        if (rank[u] == rank[v])++rank[v];
    }
};

const int INF = 987654321;
const int MAX_V = 2000 + 1;
int V, E;
//그래프의 연결 리스트 표현
vector<pair<int, int>>adj[MAX_V];
//모든 간선의 가중치의 목록. 정렬해 둔다.
vector<int> weights;
//(가중치, (정점1, 정점2))의 목록. 미리 정렬해 둔다.
vector < pair<int, pair<int, int>>> edges;

int kruskalMinUpperBound(int low) {
    DisjointSet sets(V);
    for (int i = 0; i < edges.size(); ++i) {
        if (edges[i].first < weights[low])continue;
        //edges[i]를 그래프에 추가하자.
        sets.merge(edges[i].second.first, edges[i].second.second);
        //0과 V-1이 연결되었다면 마지막에 추가한 간선의 가중치를 반환한다.
        if (sets.find(0) == sets.find(V - 1))
            return edges[i].first;
    }
    return INF;
}

//0과 V-1을 연결하는 경로 중 가중치의 상한과 하한 차이의
//최소 값을 계산한다.
int minWeightDifference() {
    int ret = INF;
    for (int i = 0; i < weights.size(); ++i)
        ret = min(ret, kruskalMinUpperBound(i) - weights[i]);
    return ret;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        cin >> V >> E;
        edges.clear();
        weights.clear();
        for (int i = 0; i < E; ++i) {
            int a, b, c;
            cin >> a >> b >> c;
            edges.push_back({ c, { a,b } });
            weights.push_back(c);
        }
        sort(edges.begin(), edges.end());
        sort(weights.begin(), weights.end());
        cout << minWeightDifference() << "\n";
    }

    return 0;
}