/*
knapsack 문제랑 비슷한데 최대 예산인 10억을 해결하기위해
100으로 나누는 것이 핵심이었다.
*/

#include <iostream>
#include <algorithm>

using namespace std;

//회전초밥 문제를 해결하는 메모이제이션 동적 계획법 알고리즘
//int n, m;
//int price[21], pref[21];
//int cache[MAX_BUDGET+1];
////budget만큼의 예산으로 초밥을 먹어서 얻을 수 있는 최대 선호도
//int sushi(int budget) {
//	//메모이제이션
//	int& ret = cache[budget];
//	if (ret != -1)return ret;
//	ret = 0;
//	for (int dish = 0; dish < n; ++dish) {
//		if (budget < price[dish])
//			continue;
//		ret = max(ret, sushi(budget - price[dish]) + pref[dish]);
//	}
//	return ret;
//}

//int c[MAX_BUDGET + 1];
////sushi()를 반복적 동적 계획법으로 구현하기
//int sushi2() {
//	int ret = 0;
//	for (int budget = 1; budget <= m; ++budget) {
//		c[budget] = 0;
//		for (int dish = 0; dish < n; ++dish)
//			if (budget >= price[dish])
//				c[budget] = max(c[budget],
//					c[[budget] - price[dish]] + pref[dish]);
//		ret = max(ret, c[budget]);
//	}
//	return ret;
//}

int n, m;
int price[20], pref[20];
int cache[201];
//최대 만족도의 합을 반환한다.
//m과 price[]는 이미 100으로 나뉘어 있다고 가정한다.
int sushi3() {
	int ret = 0;
	cache[0] = 0;
	for (int budget = 1; budget <= m; ++budget) {
		int cand = 0;
		for (int dish = 0; dish < n; ++dish)
			if (budget >= price[dish])
				cand = max(cand,
					cache[(budget - price[dish]) % 201] + pref[dish]);
		cache[budget % 201] = cand;
		ret = max(ret, cand);
	}
	return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);


	int c;
	cin >> c;
	while (c--) {
		memset(cache, -1, sizeof(cache));

		cin >> n >> m;
		m /= 100;
		for (int i = 0; i < n; ++i) {
			cin >> price[i] >> pref[i];
			price[i] /= 100;
		}
		cout << sushi3() << "\n";

	}

	return 0;
}