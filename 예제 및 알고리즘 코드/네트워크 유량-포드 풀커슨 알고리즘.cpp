const int INF = 987654321;
const int MAX_V = 200 + 1;
int V;
//capacity[u][v]=u에서 v로 보낼 수 있는 용량
//flow[u][v]=u에서 v로 흘러가는 유량(반대 방향인 경우 음수)
int capacity[MAX_V][MAX_V], flow[MAX_V][MAX_V];
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
            for (int there = 0; there < V; ++there)
                //잔여 용량이 남아 있는 간선을 따라 탐색한다.
                if (capacity[here][there] - flow[here][there] > 0 &&
                    parent[there] == -1) {
                    q.push(there);
                    parent[there] = here;
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




////////////////////////////////////
//인접 리스트로 포드-폴커슨 알고리즘 구현
//간선의 정보를 나타내는 구조체
struct Edge {
    int target, capacity, flow;
    //역방향 간선의 포인터
    Edge* reverse;
    //이 간선의 잔여 용량을 계산한다.
    int residualCapcity()const { return capacity - flow };
    //이 간선을 따라 용량 amt를 보낸다.
    void push(int amt) {
        flow += amt;
        reverse->flow -= amt;
    }
};
//유량 네트워크의 인접 리스트
vector<Edge*> adj[MAX_V];
//u에서 v로 가는 간선을 추가한다.
void addEdge(int u, int v, int capacity) {
    Edge* uv = new Edge(), * vu = new Edge();
    //u에서 v로 가는 간선을 초기화한다.
    uv->target = v;
    uv->capacity = capacity;
    uv->flow = 0;
    uv->reverse = vu;
    //v에서 u로 가는 간선을 초기화한다. 이 간선의 용량은 0이다.
    vu->target = u;
    vu->capacity = 0;
    vu->flow = 0;
    vu->reverse = uv;
    adj[u].push_back(uv);
    adj[v].push_back(vu);
}