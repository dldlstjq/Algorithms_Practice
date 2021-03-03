/*
위상정렬 문제.
종만북에서는 dfs로 위상정렬을 구하는 법이 나왔는데
사이클을 확인하는 과정을 적용시키기가 쉽지 않았다.
구글링 해보니 큐를 이용하면 더 쉽게 사이클 여부를 확인할 수 있고
정답도 더 쉽게 도출할 수 있었다.

일단은 dfs와 큐 두가지 방법으로 위상정렬을 할 수 있다는 걸 알았다.
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

//간선 (i,j)는 알파벳 i가 j보다 앞에 와야 함을 나타낸다.
vector<vector<int>> adj;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    vector<int> indegree(n + 1, 0);
    adj = vector<vector<int>>(n + 1);
    for (int i = 0; i < m; ++i) {
        //보조pd가 담당한 가수의 수
        int k;
        cin >> k;
        vector<int> singer(k);
        //가수 순서
        for (int j = 0; j < k; ++j)
            cin >> singer[j];
        //인접리스트로 저장.
        //현재 j위치가 정점이 되고 그와 연결된 정점이 j+1.
        //j와 j+1 연결하고 j+1에 들어온 간선 증가
        for (int j = 0; j < k - 1; ++j) {
            adj[singer[j]].push_back(singer[j + 1]);
            indegree[singer[j + 1]]++;
        }

    }

    //cycle은 사이클 여부, ret은 정답 저장.
    bool cycle = false;
    vector<int> ret;
    queue<int> q;
    //위상정렬 시작: 큐에 indegree가 0인 정점을 다 넣음
    for (int i = 1; i <= n; ++i)
        if (indegree[i] == 0)
            q.push(i);

    //위상 정렬
    for (int i = 1; i <= n; ++i) {
        //도중에 큐가 비면 불가능
        if (q.empty()) {
            cycle = true;
            break;
        }

        int cur = q.front();
        q.pop();
        ret.push_back(cur);
        //인접한 정점을 순회하면서 indegree 1씩 감소. 0이 되면 큐에 넣음
        for (int j = 0; j < adj[cur].size(); ++j) {
            int next = adj[cur][j];
            indegree[next]--;
            if (indegree[next] == 0)
                q.push(next);
        }

    }

    //cycle이 treu면 사이클 존재
    if (cycle)
        cout << 0;
    else
        for (int i = 0; i < n; ++i)
            cout << ret[i] << "\n";

    return 0;
}


///////////////////////////////////////
/*
DFS 풀이이다. 종만북에서 설명한것 처럼 DFS 결과를 뒤집은 다음
역방향 간선이 있는지 확인하면 되는데 전에 풀때 역방향 간선을 확인하는 것에서 어려움을 겪었다.
인접 행렬로 나타낼 때 2차원 벡터로 나타냈는데 애초에 역방향 간선이 없으면 NULL값이 되어 
런타임 에러가 났다. 이걸 해결하기 위해 벡터가 아닌 일반 배열을 사용해서
정점 연결을 0,1로 나타내니 답을 맞을 수 있었다.
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

//간선 (i,j)는 알파벳 i가 j보다 앞에 와야 함을 나타낸다.
int adj[1001][1001];
int n, m;
vector<bool> visited;
vector<int> order;

void dfs(int here) {
    visited[here] = true;
    for (int i = 1; i <= n; ++i) {
        //i가 here과 연결된 정점을 나타낸다.
        if (adj[here][i] == 1 && !visited[i])
            dfs(i);
    }
    order.push_back(here);
}

vector<int> topologicalSort() {
    //1부터 시작하게 하기 위해 adj크기는 n+1이다.
    int size = n + 1;
    visited = vector<bool>(size, false);
    order.clear();
    for (int i = 1; i < size; ++i)
        if (!visited[i])
            dfs(i);
    reverse(order.begin(), order.end());

    //order의 경우 크기는 n이고, 인덱스는 0부터 n-1까지이다.
    //역방향 간선이 있으면 사이클이 있다는 것이다. 빈 벡터 반환
    for (int i = 0; i < order.size(); ++i)
        for (int j = i + 1; j < order.size(); ++j)
            if (adj[order[j]][order[i]])
                return vector<int>();

    return order;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    memset(adj, 0, sizeof(adj));
    cin >> n >> m;
    //adj = vector<vector<int>>(n + 1);
    for (int i = 0; i < m; ++i) {
        //보조pd가 담당한 가수의 수
        int k;
        cin >> k;
        vector<int> singer(k);
        //가수 순서
        for (int j = 0; j < k; ++j)
            cin >> singer[j];
        //인접행렬 저장.
        //현재 j위치가 정점이 되고 그와 연결된 정점이 j+1.
        //j와 j+1 연결
        for (int j = 0; j < k - 1; ++j)
            adj[singer[j]][singer[j + 1]] = 1;
    }

    vector<int>ans = topologicalSort();
    if (ans.empty())
        cout << 0;
    else
        for (int i = 0; i < ans.size(); ++i)
            cout << ans[i] << "\n";

    return 0;
}