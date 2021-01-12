/*
슬라이딩 윈도를 사용해서 메모리를 최소한으로 사용해 구현했다.
*/

#include <iostream>
#include <cstring>

using namespace std;

long long fibo(int n) {
	if (n <= 1)return 1;
	long long cache[3];
	cache[0] = 0;
	cache[1] = 1;

	for (int i = 2; i <= n; ++i)
		cache[i % 3] = cache[(i - 1) % 3] + cache[(i - 2) % 3];

	return cache[n % 3];
}


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	memset(cache, -1, sizeof(cache));
	int n;
	cin >> n;
	cout << fibo(n);

	return 0;
}

