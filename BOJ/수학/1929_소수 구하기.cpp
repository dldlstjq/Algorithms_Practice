/*
에라토스테네스의 체 사용.
이번에 문제 풀면서 확실히 익힘.
*/

#include <iostream>

using namespace std;

int number = 1000000;
int a[1000001];

void primeNumberSieve(int m, int n) {

	for (int i = 2; i <= n; i++) {
		a[i] = i;
	}
	for (int i = 2; i <= n; i++) {
		if (a[i] == 0)continue;
		for (int j = i + i; j <= n; j += i) {
			a[j] = 0;
		}
	}
	for (int i = m; i <= n; i++) {
		if (a[i] != 0)
			cout << a[i] << "\n";
	}
}


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int m, n, num, result = 0;
	cin >> m >> n;

	primeNumberSieve(m, n);

	return 0;
}