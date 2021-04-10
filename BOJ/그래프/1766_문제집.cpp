/*
위상 정렬 문제인데 최소인 문제부터 푸는 것이 좋다.
일반 큐를 이용하면 최소인 문제부터 꺼내는 것이 힘들기 때문에
우선순위 큐를 이용하면 훨씬 쉽게 풀린다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int MAX = 32001;
vector<int> graph[MAX];
int indegree[MAX];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        indegree[b]++;
    }

    //최소인 문제를 먼저 풀어야하기 때문에 우선순위 큐를 사용하면 쉽게 풀린다.
    vector<int> ret;
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 1; i <= n; ++i) {
        if (indegree[i] == 0)
            pq.push(i);
    }

    while (!pq.empty()) {
        //가장 최소인 문제가 먼저 나온다.
        int cur = pq.top();
        pq.pop();

        ret.push_back(cur);
        for (int i = 0; i < graph[cur].size(); ++i) {
            int next = graph[cur][i];
            indegree[next]--;
            if (indegree[next] == 0)
                pq.push(next);
        }
    }

    for (int i = 0; i < n; ++i)
        cout << ret[i] << " ";

    return 0;
}