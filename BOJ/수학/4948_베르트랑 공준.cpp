/*
에라토스테네스의 체를 사용해서 소수인 것만 걸러
갯수를 세면 된다.
범위가 n보다 크고 2n보다 작거나 같은 범위여야 하는데 
n~2n을 구해 틀렸다. 문제를 잘 읽는 습관을 들여야겠다.
*/

#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

const int MAX = 123456 * 2 + 1;
int n;
bool isPrime[MAX];
//에라토스테네스의 체
void eratosthenes() {
	memset(isPrime, 1, sizeof(isPrime));
	isPrime[0] = isPrime[1] = false;
	int sqrtn = (int)(sqrt(MAX));
	for (int i = 2; i <= sqrtn; ++i) {
		if (isPrime[i])
			for (int j = i * i; j <= MAX; j += i)
				isPrime[j] = false;
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	eratosthenes();
	while (1) {
		cin >> n;
		if (n == 0)
			break;

		int ret = 0;
		//n보다 크고 2n보다 작거나 같다
		for (int i = n + 1; i <= 2 * n; ++i) {
			if (isPrime[i])
				ret++;
		}
		cout << ret << "\n";
	}
	return 0;
}