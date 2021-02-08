/*
1167번이랑 똑같은 문제.
루트에서 거리가 제일 먼 노드를 구한 후 그 노드에서 제일 거리가 먼 노드까지가 트리의 지름 
*/
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <utility>

using namespace std;
#define MAX 10001
vector<pair<int, int>>graph[MAX];
bool visited[MAX];
int diameter[MAX];
int n;

void bfs(int num) {
    queue<int> q;
    visited[num] = true;
    q.push(num);
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        for (int i = 0; i < graph[now].size(); i++) {
            int next = graph[now][i].first;
            int w = graph[now][i].second;

            //방문 안한곳이면 큐에 넣고 지름 더해줌
            if (!visited[next]) {
                q.push(next);
                visited[next] = true;
                diameter[next] = diameter[now] + w;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;

    for (int i = 0; i < n - 1; i++) {
        int v1, v2, weight;
        cin >> v1 >> v2 >> weight;
        graph[v1].push_back(make_pair(v2, weight));
        graph[v2].push_back(make_pair(v1, weight));
    }

    //루트인 1에서 제일 먼 노드를 구함
    bfs(1);
    int far_node = 1;
    int max = 0;
    for (int i = 2; i <= n; i++) {
        if (diameter[i] > max) {
            max = diameter[i];
            far_node = i;
        }
    }

    memset(visited, false, sizeof(visited));
    memset(diameter, 0, sizeof(diameter));

    //1에서 제일 먼 노드에서 bfs실행. 지름 구함
    bfs(far_node);
    int ans = diameter[1];
    for (int i = 2; i <= n; i++) {
        if (diameter[i] > ans) {
            ans = diameter[i];
        }
    }
    cout << ans;
    return 0;
}