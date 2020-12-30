/*
크룩스칼과 프림 두 알고리즘 모두 사용가능한 MST문제이다.
단순히 MST를 적용하면 되긴 한데 책의 코드를 수정하지 않고
그대로 쓰려다가 데이터 저장에 어려움을 겪었다.
코드를 적절하게 바꾸는 융통성이 필요함을 느꼈다.
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

int N, M;
vector<int> x;
vector<int> y;
//(가중치, (정점1, 정점2))의 목록을 얻는다.
vector<pair<double, pair<int, int>>> edges;

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


double distance(double x1, double x2, double y1, double y2)
{
    double ret = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
    return ret;
}

void init(DisjointSet& sets)
{
    edges.clear();
    x = y = vector<int>(N);
    for (int i = 0; i < N; ++i)
        cin >> x[i];
    for (int i = 0; i < N; ++i)
        cin >> y[i];
    double r;
    for (int i = 0; i < N; ++i)
        for (int j = i + 1; j < N; ++j)
        {
            r = distance(x[i], x[j], y[i], y[j]);
            edges.push_back(make_pair(r, make_pair(i, j)));
        }
    sort(edges.begin(), edges.end());
    int a, b;
    for (int i = 0; i < M; ++i)
    {
        cin >> a >> b;
        sets.merge(a, b);
    }
}

//주어진 그래프에 대해 최소 스패닝 트리에 포함된 간선의 목록을 selected에
//저장하고, 가중치의 합을 반환한다.
double kruskal(DisjointSet& sets)
{
    int u, v;
    double ret = 0;
    double cost;
    for (int i = 0; i < edges.size(); ++i)
    {
        //간선 (u, v)를 검사한다.
        cost = edges[i].first;
        u = edges[i].second.first;
        v = edges[i].second.second;
        //이미 u와 v가 연결되어 있을 경우 무시한다.
        if (sets.find(u) == sets.find(v)) 
            continue;
        //이 둘을 합친다.
        sets.merge(u, v);
        ret += cost;
    }
    return ret;
}

int main()
{
    int C; cin >> C;
    cout << fixed;
    cout.precision(8);
    for (int tn = 0; tn < C; ++tn)
    {
        cin >> N >> M;
        DisjointSet sets(N);
        init(sets);
        cout << kruskal(sets) << "\n";
    }
}