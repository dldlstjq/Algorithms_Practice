/*
위상 정렬을 이용해야 하는 문제이다.
처음에 데이터 입력 부분에서 조금 헤맸다.
입력받고 나서 해당 건물을 짓는데 걸리는 시간은 들어오는 정점들 중
가장 늦은 건설완료시간이 결정한다.
그 시간에 더해 자신의 건설시간을 더하면 답이 된다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;

const int MAX = 501;
vector<int> adj[MAX];
int indegree[MAX];
int time[MAX];
int result[MAX];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    for (int i = 1; i <= n; ++i) {
        //시간 저장
        int num;
        cin >> num;
        time[i] = num;
        //먼저 지어야 하는 건물 그래프에 표시
        while (1) {
            int pre;
            cin >> pre;
            if (pre == -1)
                break;
            indegree[i]++;
            adj[pre].push_back(i);
        }
    }

    //들어오는 간선이 없는 정점을 큐에 추가하고 시간을 result에 저장
    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        if (indegree[i] == 0) {
            result[i] = time[i];
            q.push(i);
        }

    }

    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        for (int i = 0; i < adj[cur].size(); ++i) {
            int next = adj[cur][i];
            indegree[next]--;
            //먼저 지어야할 건물이 여러개인 경우 
            //가장 늦은 건설완료시간이 해당 건물 시간을 결정한다
            result[next] = max(result[next], result[cur] + time[next]);

            if (indegree[next] == 0)
                q.push(next);
        }
    }

    for (int i = 1; i <= n; ++i) {
        cout << result[i] << "\n";
    }
    return 0;
}