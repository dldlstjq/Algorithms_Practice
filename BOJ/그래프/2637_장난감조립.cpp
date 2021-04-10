/*
처음엔 위상정렬을 생각하지 않고 재귀함수로 풀었는데 시간초과가 났다.
다른 사람 풀이를 보니 단순히 위상정렬을 사용해서 필요한 갯수만큼 곱해 더해주면 되는 거였다.
답을 1차원배열에 저장하는게 아니라 2차원 배열에 저장해서 부품 i개를 만드는데 기본 부품 j가 필요하다고 정한뒤
하면 구할 수 있었다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int MAX = 103;
vector<pair<int, int>> adj[MAX];
int ans[MAX][MAX];
int indegree[MAX];


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int x, y, k;
        cin >> x >> y >> k;
        adj[y].push_back({ x,k });
        //중간부품의 들어오는 간선을 증가시킨다.
        //즉, 기본 부품은 들어오는 간선이 없다.
        indegree[x]++;
    }

    //기본 부품을 큐에 넣고 
    //부품 i를 조립하는 데 필요한 기본 부품 j의 개수를 ans[i][j]라 할 때,
    //기본 부품 k에 대해 ans[k][k] = 1인 상태로 시작
    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        if (indegree[i] == 0) {
            q.push(i);
            ans[i][i] = 1;
        }
    }

    //위상정렬을 하면서 필요한 갯수만큼 곱해서 더해주면 된다.
    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        for (int i = 0; i < adj[cur].size(); ++i) {
            int next = adj[cur][i].first;
            for (int j = 1; j <= n; ++j)
                ans[next][j] += ans[cur][j] * adj[cur][i].second;
            indegree[next]--;
            if (indegree[next] == 0)
                q.push(next);
        }
    }

    for (int i = 1; i <= n; ++i)
        if (ans[n][i])
            cout << i << " " << ans[n][i] << "\n";

    return 0;
}