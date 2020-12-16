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
