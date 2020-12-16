/*
위상 정렬 문제인데 가장 기본적인 형태인것 같다.
문제에서 답이 없는 경우-사이클이 있는 경우에 대한 말이 없어서
예외처리를 안해도 정답이 나오긴 나온다.
큐를 이용한 풀이, dfs를 이용한 풀이 2개가 있다.
사이클이 없다는 가정이 있어서 dfs로 해도 되는데 사이클이 있다면 
검사를 어떻게 하는지는 공부가 필요하다.
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
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        indegree[b]++;
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
            cout << ret[i] << " ";

    return 0;
}


////////////////dfs(스택)풀이
#include <cstdio>
#include <algorithm>
#include <vector>
#include <stack>
#define MAX_N 32000
using namespace std;
vector<vector<int>> vt;
stack<int> st;
int n, m, x, y, visited[MAX_N + 1];
void dfs(int v) {
    visited[v] = true;
    for (auto i : vt[v]) {
        if (visited[i])
            continue;
        dfs(i);
    }
    st.push(v);
}
int main() {
    scanf("%d%d", &n, &m);
    vt.resize(n + 1);
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &x, &y);
        vt[x].push_back(y);
    }
    for (int i = 1; i <= n; i++) {
        if (!visited[i])
            dfs(i);
    }
    while (st.size()) {
        printf("%d ", st.top());
        st.pop();
    }
    return 0;
}
