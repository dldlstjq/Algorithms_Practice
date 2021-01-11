/*
종만북 동적계획법에서 제일 처음 설명한 이항계수 구하기이다.
탑다운 방식이 재귀로 해결했다.
*/

#include <iostream>
#include <cstring>

using namespace std;

const int MOD = 10007;
int N, K;
int cache[1001][1002];

int bino(int n, int k) {
	//기저 사례
	if (n == k || k == 0)
		return 1;
	int& ret = cache[n][k];
	if (ret != -1)return ret;
	ret = (bino(n - 1, k - 1) + bino(n - 1, k)) % MOD;
	return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	memset(cache, -1, sizeof(cache));
	cin >> N >> K;
	cout << bino(N, K) % MOD;

	return 0;
}

