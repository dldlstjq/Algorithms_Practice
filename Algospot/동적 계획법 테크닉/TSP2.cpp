/*
여행하는 외판원 문제를 해결하는 동적 계획법 알고리즘
visited를 bool형 배열로 작성하는 대신 비트마스크를 활용해 메모리를 아꼈다.
*/

#include <iostream>
#include <algorithm>
#include <bitset>

using namespace std;

//여행하는 외판원 문제를 해결하는 동적 계획법 알고리즘
const int MAX = 15;
const double INF = 987654321.0;

int n, dist[MAX][MAX];
double cache[MAX][1 << MAX];	//-1로 초기화해 둔다.
//here: 현재 위치
//visited: 각 도시의 방문 여부
//here에서 시작해 남은 도시들을 방문할 수 있는 최단 경로의 길이를 반환한다.
//나머지 도시들을 모두 방문하는 경로들 중 가장 짧은 것의 길이를 반환한다.
//항상 0번 도시에서 시작한다고 가정한다.
double shortestPath2(int here, int visited) {
	//기저 사례: 모든 도시를 다 방문했을 때는 0번 도시로 돌아가고 종료한다.
	if (visited == (1 << n) - 1)	//비트마스크 활용. (2^n-1)이면 모든 자릿수가 1이므로 전체 다 방문했다는 뜻
		return dist[here][0];
	//메모이제이션
	double& ret = cache[here][visited];
	if (ret >= 0)return ret;
	ret = INF;	//매우 큰 값으로 초기화
	//다음 방문할 도시를 전부 시도해 본다.
	for (int next = 0; next < n; ++next) {
		//이미 방문한 도시인 경우
		//비트마스크 활용 next만큼 왼쪽으로 쉬프트, 
		//즉 2^next=1이면 visited&(1<<next)는 1이므로 참
		if (visited & (1 << next))continue;
		double cand = dist[here][next] +
			shortestPath2(next, visited + (1 << next));
		ret = min(ret, cand);
	}
	return ret;
}

void initialize(void) {
	for (int i = 0; i < MAX; i++)
		for (int j = 0; j < (1 << MAX); j++)
			cache[i][j] = -1.0; //double에 대해서는 memset 적용 안됨
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int c;
	cin >> c;
	while (c--) {
		cin >> n;
		cout.setf(ios::fixed);
		cin.precision(10);
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				cin >> dist[i][j];
		initialize();
		double result = INF;
		for (int i = 0; i < n; ++i)
			//각 도시를 방문했다는 것을 1<<i로
			result = min(result, shortestPath2(i, 1 << i));
		//cout << fixed;
		cout.precision(10);
		cout << result << "\n";
	}

	return 0;
}