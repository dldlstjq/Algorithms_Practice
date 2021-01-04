/*
핵심은 b를 2로 나누어 재귀함수로 해결해야 한다.
b가 짝수일 때는 (a^b/2)^2로, 홀수일 때는 (a^b/2)^2 * a^1로 계산했다.

처음에는 홀수 계산 시 한번만 c로 모듈러 연산을 했는데 
b/2로 나눈 연산을 다시 곱할 때도 c로 모듈러 연산을 해야 정답이 나왔다.
*/

#include <iostream>

using namespace std;

long long multiply(long long a, long long b, long long c) {
	long long ret = 0;
	if (b == 1) {
		return a * b % c;
	}

	//짝수일 때는 (a^b/2)^2으로 계산
	if (b % 2 == 0)
		ret = multiply(a, b / 2, c) * multiply(a, b / 2, c) % c;
	//홀수일 떄는 (a^b/2)^2 * a^1로 계산
	else
		ret = (multiply(a, b / 2, c) * multiply(a, b / 2, c)) % c * multiply(a, 1, c) % c;
	return ret % c;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	long long a, b, c;
	cin >> a >> b >> c;

	cout << multiply(a, b, c);

	return 0;
}