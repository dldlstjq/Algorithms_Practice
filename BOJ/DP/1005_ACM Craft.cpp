/*
건물 짓는 순서가 정해져 있어 처음에는 위상정렬을 해서 구해야 하는걸로 생각했다.
하지만 특정 건물을 짓는데 필요한 시간을 구해야 해서 위상정렬을 사용하는게
힘들어 보였고 이래저래 생각해봤는데 딱히 생각이 나지 않았다.
못풀겠어서 검색해보니 코드가 생각보다 간단했다.
건물 짓는 조건을 하나씩 다 탐색하면서 제일 시간이 오래 걸리는 것을
선택해서 건설 시간과 더해 값을 구하면 되는 거였다.
*/

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int N, K;	//건물 수, 건설순서규칙
int time[1001];	//건물 건설 시간
int X, Y;	//건설 순서 (X다음 Y건설 가능)
int W;	//건설해야할 건물 번호
int order[1001][1001];	//건물 짓는 조건
int cache[1001];

//k는 건물번호, t는 건설시간
int solve(int dest) {
	int& ret = cache[dest];
	if (ret != -1)return ret;
	int t = 0;
	//건물 조건을 탐색한다.
	for (int i = 1; i <= N; ++i)
		if (order[i][dest])
			//dest를 만들기 전 동시에 만들 건물 중 제일 시간 오래 걸리는 건물
			t = max(t, solve(i));
	ret = t + time[dest];
	return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int c;
	cin >> c;
	while (c--) {
		memset(cache, -1, sizeof(cache));
		memset(order, 0, sizeof(order));
		cin >> N >> K;
		for (int i = 1; i <= N; ++i)
			cin >> time[i];

		for (int i = 0; i < K; ++i) {
			int a, b;
			cin >> a >> b;
			order[a][b] = 1;

		}
		cin >> W;
		cout << solve(W) << "\n";
	}

	return 0;
}