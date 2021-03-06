//TSP 재귀호출 알고리즘

int n;	//도시의 수
double dist[MAX][MAX];	//두 도시간의 거리를 저장하는 배열
const int INF = 987654321;

//path: 지금까지 만든 경로
//visited: 각 도시의 방문 여부
//currentLength: 지금까지 만든 경로의 길이
//나머지 도시들을 모두 방문하는 경로들 중 가장 짧은 것의 길이를 반환한다.
double shortestPath(vector<int>& path, vector<bool>& visited,
	double currentLength) {
	//기저 사례: 모든 도시를 다 방문했을 때는 시작 도시로 돌아가고 종료한다.
	if (path.size() == n)
		return currentLength + dist[path[0]][path.back()];
	double ret = INF;	//매우 큰 값으로 초기화
	//다음 방문할 도시를 전부 시도해 본다.
	for (int next = 0; next < n; ++next) {
		if (visited[next])
			continue;
		int here = path.back();
		path.push_back(next);
		visited[next] = true;
		//나머지 경로를 재귀 호출을 통해 완성시키고 가장 짧은 경로의 길이를 얻는다.
		double cand = shortestPath(path, visited, currentLength +
			dist[here][next]);
		ret = min(ret, cand);
		visited[next] = false;
		path.pop_back();
	}
	return ret;
}




//TSP 동적계획법 알고리즘(비트마스크 이용)
int n, dist[MAX][MAX];
double cache[MAX][1 << MAX];	//-1로 초기화해 둔다.
const int INF = 987654321;
//here: 현재 위치
//visited: 각 도시의 방문 여부
//here에서 시작해 남은 도시들을 방문할 수 있는 최단 경로의 길이를 반환한다.
//나머지 도싣르을 모두 방문하는 경로들 중 가장 짧은 것의 길이를 반환한다.
//항상 0번 도시에서 시작한다고 가정한다.
double shortesPath2(int here, int visited) {
	//기저 사례: 모든 도시들을 다 방문했을 때는 0번도시로 돌아가고 종료한다.
	if (visited == (1 << n) - 1)
		return dist[here][0];
	//메모이제이션
	double& ret = cache[here][visited];
	if (ret >= 0)return ret;
	ret = INF;	//매우 큰 값으로 초기화
	//다음 방문할 도시를 전부 시도해 본다.
	for (int next = 0; next < n; ++next) {
		//이미 방문한 도시의 경우
		if (visited & (1 << next))
			continue;
		double cand = dist[here][next] +
			shortesPath2(here, vistied + (1 << next));
		ret = min(ret, cand);
	}
	return ret;
}