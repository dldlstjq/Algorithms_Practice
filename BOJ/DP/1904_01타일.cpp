/*
점화식을 세워보면 피보나치 수열과 같다.
최대 백만개의 배열을 선언하는 것 보다 종만북에서 본 대로
슬라이딩 윈도를 이용한 방식을 사용하면 메모리 사용량이
반이상 줄어든 것을 확인할 수 있었다.

solve() -> 5924KB
solve2() -> 2016KB
*/

#include <iostream>
#include <cstring>
using namespace std;

const int MOD = 15746;

int n;
int cache[1000001];

//백만개의 배열 생성한 풀이
int solve() {
	cache[1] = 1;
	cache[2] = 2;
	for (int i = 3; i <= n; ++i)
		cache[i] = (cache[i - 1] + cache[i - 2]) % MOD;
	return cache[n] % MOD;
}

//슬라이딩 윈도를 이용한 풀이
int solve2() {
	if (n <= 1)return n;
	int seq[3];
	seq[0] = 0;
	seq[1] = 1;
	seq[2] = 2;
	for (int i = 3; i <= n; ++i)
		seq[i % 3] = (seq[(i - 1) % 3] + seq[(i - 2) % 3]) % MOD;
	return seq[n % 3] % MOD;
}


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	memset(cache, -1, sizeof(cache));
	cin >> n;
	cout << solve();

	return 0;
}