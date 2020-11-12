/*
처음에 푸는 방법을 몰라 많이 헤매다 다른 풀이 방법을 찾아봐서 이해함.

풀이 방법
먼저 임의의 정점부터 모든 정점까지의 거리를 구하여 가장 먼 거리를 가진 정점을 구한다. 
그 후에 그 정점으로부터 모든 정점까지의 거리를 다시 구해서 그 거리들 중 가장 먼 값이 트리의 지름이 된다.
*/
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <utility>

using namespace std;
#define MAX 100001
vector<pair<int, int>> tree[MAX];
bool visited[MAX];
int node_dist[MAX];   //거리 저장

void bfs(int v) {
    queue <int> q;
    visited[v] = true;
    q.push(v);
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        for (int i = 0; i < tree[now].size(); i++) {
            //next는 현재노드(now)와 연결된 노드
            //dist는 now와 next 사이 거리
            int next = tree[now][i].first;
            int dist = tree[now][i].second;
            //방문하지 않았으면 큐에 넣고 거리 합 구함
            if (!visited[next]) {
                q.push(next);
                visited[next] = true;
                node_dist[next] = node_dist[now] + dist;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    int v1, v2, dist;

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> v1;

        while (1) {
            cin >> v2;
            if (v2 == -1)
                break;
            cin >> dist;
            tree[v1].push_back(make_pair(v2, dist));
        }
    }

    //1과 가장 먼 거리에 있는 노드 구함
    bfs(1);

    //거리 합이 제일 큰 인덱스가 제일 먼 노드
    int index = 1;
    for (int i = 2; i <= n; i++) {
        int max = 0;
        if (node_dist[i] > node_dist[index])
            index = i;
    }

    //초기화
    memset(visited, false, sizeof(visited));
    memset(node_dist, 0, sizeof(node_dist));

    //거리가 제일 먼 노드부터 지름 구함
    bfs(index);

    int diameter = node_dist[1];
    for (int i = 2; i <= n; i++) {
        if (diameter < node_dist[i])
            diameter = node_dist[i];
    }
    cout << diameter;
    return 0;
}