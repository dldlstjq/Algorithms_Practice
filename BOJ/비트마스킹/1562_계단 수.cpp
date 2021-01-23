/*
계단 수 자체는 10844_쉬운 계단 수를 통해 익혔는데
0~9가 모두 등장하는 수를 구해야 한다.
어디서 비트마스크를 적용해야 할지 감이 안왔는데
0~9가 사용되었는지 여부를 확인할 때 썼다.

발전소 문제와 마찬가지로 DP 식을 만드는 게 어려웠다.
전체 길이와 사용되는 숫자를 통해 2차원 배열까지는 생각했는데
0~9가 사용되었는지를 확인하는 비트계산도 만들어야 문제를 풀 수 있었다.
또한 기저사례에서 단순히 길이가 n이라서 종료하는게 아니라 
길이가 n일때 0~9가 다 사용되었는지를 확인하고 최종적으로 값을 반환해야 했다.

처음엔 단순히 길이가 n일때만 반환한다고 생각했고
모든 계단수를 만들 때 1을 더하고 빼는 것만 고려햐면 되는데 for문으로
생각하려다 문제를 해결하지 못했다.

아직도 재귀DP랑 반복문 DP가 헷갈리는것 같다.
*/

#include <iostream>
#include <cstring>

using namespace std;

const int MOD = 1000000000;
const int MAX = 101;

int n;
//자리수 길이, 시작하는 수, 0~9까지 비트
int cache[10][MAX][1 << 10];

//start: 현재 숫자
//length: 숫자 길이
//used: 0~9까지 사용된 숫자 체크. 0000000000~1111111111
int solve(int start, int length, int used) {
	//기저 사례: 더 이상 채울 자리가 없을 때 0~9를 사용했으면
	//1, 아니면 0
	if (length == n)
		return used == (1 << 10) - 1 ? 1 : 0;
	int& ret = cache[start][length][used];
	if (ret != -1)return ret;
	ret = 0;
	//계단 수: 하나씩 차이
	if (start - 1 >= 0)
		ret += solve(start - 1, length + 1, used | 1 << (start - 1));
	if (start + 1 < 10)
		ret += solve(start + 1, length + 1, used | 1 << (start + 1));
	ret %= MOD;
	return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	int ans = 0;
	for (int i = 1; i <= 9; ++i) {
		memset(cache, -1, sizeof(cache));
		//맨 처음엔 0이 올 수 없다.
		ans += solve(i, 1, 1 << i);
		ans %= MOD;
	}
	cout << ans;
	return 0;
}