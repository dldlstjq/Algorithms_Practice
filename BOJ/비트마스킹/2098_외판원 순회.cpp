/*
N이 작을 때 완전탐색보다 DP로 풀면 훨씬 더 빨리 풀 수 있다.
핵심은 비트마스크를 이용해서 0번부터 n비트까지로 마을을 표현해서
k번 비트는 k번 마을을 방문했으면 1, 아니면 0을 표시한다.
*/

#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX = 16;

int n, dist[MAX][MAX];
int cache[MAX][1 << MAX];	//-1로 초기화해 둔다.
const int INF = 987654321;
//here: 현재 위치
//visited: 각 도시의 방문 여부
//here에서 시작해 남은 도시들을 방문할 수 있는 최단 경로의 길이를 반환한다.
//나머지 도시들을 모두 방문하는 경로들 중 가장 짧은 것의 길이를 반환한다.
//항상 0번 도시에서 시작한다고 가정한다.
int shortestPath2(int here, int visited) {
	//기저 사례: 모든 도시들을 다 방문했을 때는 0번도시로 돌아가고 종료한다.
	if (visited == (1 << n) - 1)
		if (dist[here][0] != 0)
			return dist[here][0];
		else
			return INF;
	//메모이제이션
	int& ret = cache[here][visited];
	if (ret != -1)return ret;
	ret = INF;	//매우 큰 값으로 초기화
	//다음 방문할 도시를 전부 시도해 본다.
	for (int next = 0; next < n; ++next) {
		//이미 방문한 도시의 경우
		if (visited & (1 << next) || dist[here][next] == 0)
			continue;
		int cand = dist[here][next] +
			shortestPath2(next, visited + (1 << next));
		ret = min(ret, cand);
	}
	return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			cin >> dist[i][j];

	memset(cache, -1, sizeof(cache));
	cout << shortestPath2(0, 1);
	return 0;
}