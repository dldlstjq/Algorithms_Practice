/*
백준문제에서도 풀어본 타일링 문제이다.
반복문이 아닌 재귀함수로 푼 풀이인데 이렇게 풀도록 연습해 가야겠다.
*/

#include <iostream>
#include <cstring>

using namespace std;

const int MOD = 1000000007;
int cache[101];
int n;
//2*width 크기의 사각형을 채우는 방법의 수를 MOD로 나눈 나머지를 반환한다.
int tiling(int width) {
	//기저 사례: width가 1 이하일 때
	if (width <= 1)
		return 1;
	//메모이제이션
	int& ret = cache[width];
	if (ret != -1)
		return ret;
	return ret = (tiling(width - 2) + tiling(width - 1)) % MOD;

}


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;
	while (t--) {
		memset(cache, -1, sizeof(cache));
		cin >> n;
		cout << tiling(n) << "\n";

	}

	return 0;
}