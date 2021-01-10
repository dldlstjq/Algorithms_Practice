/*
생소한 개념이 많은 문제였다.
규칙성을 찾으려 이것저것 그려봤는데 확실한 규칙성을 찾지 못했다.

동적 계획법에서는 재귀함수를 사용할 수 있는 형태인 점화식을
잘 세워야 하는데 그걸 찾는게 관건이다.
이 문제 같은 경우 딱 보고 점화식을 찾는데 쉽지 않아 다양한 유형의
문제들을 풀어보며 감을 익혀야 할 것 같다.
*/

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int MOD = 10000000;
int cache[101][101]; //최대 100이고 0번째 index를 사용하지 않으므로


//n개의 정사각형으로 이루어졌고, 맨 위 가로줄에 first개의
//정사각형을 포함하는 폴리오미노의 수를 반환한다.
int poly(int n, int first) {
	//기저 사례: n == first
	if (n == first)
		return 1;
	//메모이제이션
	int& ret = cache[n][first];
	if (ret != -1)return ret;
	ret = 0;
	//맨 위 가로줄에서부터 second번째 밑에 있는 층의 블록 수
	//poly(n, first)=∑(second+first-1) * poly(n-first, second);
	for (int second = 1; second <= n - first; ++second) {
		//맨 윗줄에 first개의 정사각형이 있고, 나머지 사각형으로 만든 폴리오미노의 첫 줄에 second개의
		//정사각형이 있다고 했을 때  이들을 붙일 수 있는 방법의 수는 first+second-1
		//ex) first 2 second 2(2+2-1=3가지)
		//  ㅁㅁ ㅁㅁ ㅁㅁ
		//ㅁㅁ   ㅁㅁ   ㅁㅁ
		//ex) first 2 second 3(2+3-1=4가지)
		//  ㅁㅁ     ㅁㅁ ㅁㅁ   ㅁㅁ
		//ㅁㅁㅁ ㅁㅁㅁ   ㅁㅁㅁ   ㅁㅁㅁ
		int add = second + first - 1;
		add *= poly(n - first, second);	//n-first개의 정사각형 중 해당 층에는 second개 사용
		add %= MOD;
		ret += add;
		ret %= MOD;
	}
	return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;
	while (t--) {
		memset(cache, -1, sizeof(cache));
		int n, sum = 0;
		cin >> n;
		for (int i = 1; i <= n; ++i) {
			sum += poly(n, i);
			sum %= MOD;
		}
		cout << sum << "\n";

	}

	return 0;
}