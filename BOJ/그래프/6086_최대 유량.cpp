/*
간단한 네트워크 유량 문제.
책의 코드를 변형해서 써야하는데 무작정 쓰다가 잘 안돼서
고생했다.
입력 데이터를 그래프로 만든 뒤 그에 맞게 코드를 변형해야 된다.
네트워크 유량 문제는 처음 접한 개념이다보니 익숙해질 때까지
많은 연습이 필요할 것 같다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;

const int INF = 987654321;
const int MAX_V = 52;
int V;
//capacity[u][v]=u에서 v로 보낼 수 있는 용량
//flow[u][v]=u에서 v로 흘러가는 유량(반대 방향인 경우 음수)
int capacity[MAX_V][MAX_V], flow[MAX_V][MAX_V];
int parent[MAX_V];

vector<int> adj[MAX_V]; // 인접 리스트

//flow[][]를 계산하고 총 유량을 반환한다.
int networkFlow(int source, int sink) {
    //flow를 0으로 초기화한다.
    memset(flow, 0, sizeof(flow));
    int totalFlow = 0;
    while (true) {
        //너비 우선 탐색으로 증가 경로를 찾는다.
        vector<int> parent(MAX_V, -1);
        queue<int> q;
        parent[source] = source;
        q.push(source);
        while (!q.empty() && parent[sink] == -1) {
            int here = q.front(); q.pop();
            //싱크에 도달하면 나온다.
            if (here == sink)
                break;
            for (int there = 0; there < adj[here].size(); ++there) {
                int next = adj[here][there];
                //잔여 용량이 남아 있는 간선을 따라 탐색한다.
                // c[i][j]-f[i][j] > 0: i에서 j로 유량을 흘릴 여유가 남았는가?
                // prev[next] == -1: next 정점을 아직 방문하지 않았는가?
                if (capacity[here][next] - flow[here][next] > 0 &&
                    parent[next] == -1) {
                    q.push(next);
                    parent[next] = here;
                }
            }

        }
        //증가 경로가 없으면 종료한다.
        if (parent[sink] == -1)
            break;
        //증가 경로를 통해 유량을 얼마나 보낼지 결정한다.
        int amount = INF;
        for (int p = sink; p != source; p = parent[p])
            amount = min(capacity[parent[p]][p] - flow[parent[p]][p],
                amount);
        //증가 경로를 통해 유량을 보낸다.
        for (int p = sink; p != source; p = parent[p]) {
            flow[parent[p]][p] += amount;
            flow[p][parent[p]] -= amount;
        }
        totalFlow += amount;
    }
    return totalFlow;

}

// 정점 문자를 0~51 사이의 번호로 바꿔주는 간단한 함수
int toNumber(char c) {
    if (c <= 'Z')
        return c - 'A';
    return c - 'a' + 26;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> V;

    memset(capacity, 0, sizeof(capacity));
    for (int i = 0; i < V; ++i) {
        char p1, p2;
        int weight;
        cin >> p1 >> p2 >> weight;

        int s = toNumber(p1), e = toNumber(p2);
        adj[s].push_back(e);
        adj[e].push_back(s);

        capacity[s][e] += weight;
        capacity[e][s] += weight;
    }

    int source = toNumber('A');
    int sink = toNumber('Z');

    cout << networkFlow(source, sink);

    return 0;
}