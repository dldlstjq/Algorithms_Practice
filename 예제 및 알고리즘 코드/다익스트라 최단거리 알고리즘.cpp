// 정점의 개수
int V;
// 그래프의 인접 리스트.(연결된 정점 번호, 간선 가중치) 쌍을 담는다.
vector<pair<int, int>> adj[MAX_V];
vector<int> dijkstra(int src, vector<int>& parent) {
	vector<int> dist(V, INF);
	parent = vector<int>(adj.size(), -1);
	dist[src] = 0;
	parent[start] = start;

	//pair를 비교할 때는 첫번재 원소를 먼저 비교하므로 정점까지 거리를 첫번째 원소, 정점의 번호를 두번째 원소로 한다.
	//prioirty_queue는 기본적으로 가장 큰 원소가 위로 가도록 큐를 구성하기 때문에,
	//거리의 부호를 바꿔서 거리가 작은 정점부터 꺼내지도록 하는 것에 주목.
	//그렇지 않으면 복잡하게 우선순위 큐 구현.
	//priority_queue<pair<int, int>, vector<pair<int,int>>, greater<pair<int, int>>> pq;
	priority_queue<pair<int, int> > pq;
	pq.push(make_pair(0, src));
	while (!pq.empty()) {
		int cost = -pq.top().frist;
		int here = pq.top().second;
		pq.pop();
		//만약 지금 꺼낸 것보다 더 짧은 경로를 알고 있다면 지금 꺼낸 것을 무시한다.
		if (dist[here] < cost)continue;
		//인접한 정점들을 모두 검사한다.
		for (int i = 0; i < adj[here].size(); ++i) {
			int there = adj[here][i].first;
			int nextDist = cost + adj[here][i].second;
			//더 짧은 경로를 발견하면, dist[]를 갱신하고 우선순위 큐에 넣는다.
			if (dist[here] > nextDist) {
				dist[there] = nextDist;
				pq.push(make_pair(-nextDist, there));
				parent[there] = here;
			}
		}
	}
	return dist;
}


//v로 부터 시작점까지의 최단 경로를 계산한다.
vector<int> shortestPath(int v, const vector<int>& parent) {
	vector<int> path(1, v);
	while (parent[v] != v) {
		v = parent[v[;
		path.push_back(v);
	}
	reverse(path.begin(), path.end());
	return path;
}