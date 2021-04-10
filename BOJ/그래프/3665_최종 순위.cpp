/*
단순히 등수에 따라 간선을 하나씩만 연결해 그래프를 만들면 해결할 수 없었다.
현재 자신보다 낮은 등수에 있는 팀 전체에 간선을 연결해야 했다.
그리고 순위가 바뀐 팀에 대해서는 있던 간선을 지우고 역방향 간선을 추가해줘야 한다.

이렇게 하고 나서 큐에 집어넣고 위상정렬을 하면 된다.
순위를 알 수 있는 건 상관 없는데 ?랑 IMPOSSIBLE이 문제였다.
IMPOSSIBLE은 사이클이 있다는 의미이기 때문에 큐가 비었을때
전체 팀이 결과에 들어오지 않아 결과벡터의 사이즈가 n이 되지 않는다.

문제는 애매해서 순위를 찾을 수 없는 건데 이것도 생각해보면
들어오는 간선이 없는 정점을 큐에 넣을때 두 개이상 들어오면 둘 중 어느것이 순위가 더 높은지 모르기 때문에
큐의 사이즈가 2이상이면 ?을 출력하면 된다.

단순하게만 생각하면 접근할 수 없는 문제였던 것 같다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;

const int MAX = 501;
int adj[MAX][MAX];
int last_grade[MAX];
int indegree[MAX];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        memset(adj, 0, sizeof(adj));
        memset(last_grade, 0, sizeof(last_grade));
        memset(indegree, 0, sizeof(indegree));

        int n, m;
        cin >> n;
        for (int i = 1; i <= n; ++i)
            cin >> last_grade[i];

        //자신보다 순위가 낮은 팀에 전부 간선을 이어준다.
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                adj[last_grade[i]][last_grade[j]] = 1;
                indegree[last_grade[j]]++;
            }
        }

        //순위가 바뀐 팀에 대해서는 기존의 간선을 삭제하고 
        //거꾸로 간선을 이어준다.
        cin >> m;
        for (int i = 0; i < m; ++i) {
            int a, b;
            cin >> a >> b;
            if (adj[a][b] == 1) {
                adj[a][b] = 0;
                adj[b][a] = 1;
                indegree[b]--;
                indegree[a]++;
            }

            else {
                adj[b][a] = 0;
                adj[a][b] = 1;
                indegree[a]--;
                indegree[b]++;
            }
        }

        //들어오는 간선이 없는 걸 큐에 넣는다.
        queue<int> q;
        vector<int> ret;
        for (int i = 1; i <= n; ++i) {
            if (indegree[i] == 0)
                q.push(i);
        }

        bool possible = true;
        while (!q.empty()) {
            //큐에 두 개이상의 팀이 들어오면 어느 팀이 더 순위가 높은지 모르기 때문에
            //?를 출력한다.
            if (q.size() >= 2) {
                possible = false;
                break;
            }
            int cur = q.front();
            q.pop();

            ret.push_back(cur);
            for (int i = 1; i <= n; ++i) {
                if (adj[cur][i] == 1) {
                    indegree[i]--;
                    if (indegree[i] == 0)
                        q.push(i);
                }
            }
        }

        //n개의 팀 전부가 들어오지 않으면 사이클이 있다.
        if (ret.size() != n)
            cout << "IMPOSSIBLE";
        //확실한 순위를 찾을 수 없다.
        else if (!possible)
            cout << "?";
        //순위가 정해졌다.
        else
            for (int i = 0; i < n; ++i)
                cout << ret[i] << " ";
        cout << "\n";
    }
    return 0;
}