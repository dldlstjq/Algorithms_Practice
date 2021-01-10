/*
기존 우물을 기어오르는 달팽이 코드에서 확률만 곱하면 쉽게 답을 구할 수 있다.
cache가 double형이라서 memset으로 초기화가 안돼 직접 초기화 해줘야 한다.

TILING2, TRIPATHCNT, SNAIL 이 문제들이 다 비슷해서
비슷한 유형들은 규칙성만 찾아내면 쉽게 풀 수 있을 것 같다
*/

#include <iostream>

using namespace std;

const int MAX_N = 1000;
int n, m;
double cache[MAX_N][2 * MAX_N + 1];
//달팽이가 days일 동안 climbed미터를 기어올라 왔다고 할 때,
//m일 전까지 n미터를 기어올라갈 수 있는 경우의 수
double climb(int days, int climbed) {
	//기저 사례: m일이 모두 지난 경우
	if (days == m)
		return climbed >= n ? 1 : 0;
	//메모이제이션
	double& ret = cache[days][climbed];
	if (ret != -1)
		return ret;
	return ret = 0.25 * climb(days + 1, climbed + 1) + 0.75 * climb(days + 1,
		climbed + 2);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;
	while (t--) {
		//memset(cache, -1, sizeof(cache));
		for (int i = 0; i < MAX_N; ++i)
			for (int j = 0; j < 2 * MAX_N + 1; ++j)
				cache[i][j] = -1.0;
		cin >> n >> m;
		cout << fixed;
		cout.precision(11);
		cout << climb(0, 0) << "\n";
	}

	return 0;
}