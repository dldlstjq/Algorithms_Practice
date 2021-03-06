//깊이 우선 탐색을 이용한 오일러 서킷 찾기
vector<vector<int>> adj;
//무향 그래프의 인접 행렬 adj가 주어질 때 오일러 서킷을 계산한다.
//결과로 얻어지는 circuit을 뒤집으면 오일러 서킷이 된다.
void getEulerCircuit(int here, vector<int>& circuit) {
	for (int there = 0; there < adj[here].size(); ++there) {
		while (adj[here][there] > 0) {
			adj[here][there]--;	//양쪽 간선을 모두 지운다.
			adj[there][here]--;
			getEulerCircuit(there, circuit);
		}
	}
	circuit.push_back(here);
}


//방향 그래프에서 오일러 서킷 혹은 트레일을 찾아내기
void getEulerCircuit(int here, vector<int>& circuit) {
	for (int there; there < adj[here].size(); ++i) {
		while (adj[here][there] > 0) {
			//간선을 지운다.
			//방향 그래프이기 때문에 양쪽을 다 지우지 않는다.
			adj[here][there]--;	
			getEulerCircuit(there, circuit);
		}
	}
	circuit.push_back(here);
}
//현재 그래프의 오일러 트레일이나 서킷을 반환한다.
vector<int> getEulerTrailOrCircuit() {
	vector<int> circuit;
	//우선 트레일을 찾아본다. 시작점이 존재하는 경우
	for (int i = 0; i < 26; ++i)
		if (outdegree[i] == indegree[i] + 1) {
			getEulerCircuit(i, circuit);
			return circuit;
		}
	//아니면 서킷이니, 간선에 인접한 아무 정점에서나 시작한다.
	for(int i=0;i<26;++i)
		if (outdegree[i]) {
			getEulerCircuit(i, circuit);
			return circuit;
		}
	//모두 실패한 경우 빈 배열을 반환한다.
	return circuit;
}