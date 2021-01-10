/*
전체에서 대칭되는 타일링을 빼서 구하는 것 까지는 알았는데
대칭되는 타일링 계산이 생각이 나지 않았다.
n이 홀수일때, 짝수일때로 나누어서 대칭을 계산한다.
간단하게 전체 길이 n에서 가운데 부분을 뺀 대칭되는 부분을 구하면 되기 때문에
2로 나누면 되는데 그게 생각이 안났다.

그리고 MOD같은 경우 빼기 연산을 하면 음수가 나올 수 있기 때문에
MOD를 더하고 나눠준다.

직접 비대칭 타일을 구하는 방법도 있다.
*/

#include <iostream>
#include <cstring>

using namespace std;

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

//2*width 크기의 사각형을 채우는 비대칭 방법의 수를 반환한다.
int asymmetric(int width) {
	//가로 길이가 홀수
	if (width % 2 == 1)
		//가운데 2*1 직사각형 하나를 기준으로 대칭인 경우 뺀다.
		return (tiling(width) - tiling((width - 1) / 2) + MOD) % MOD;
	int ret = tiling(width);
	//가로의 길이가 짝수일 경우에는 가운데 1*2 직사각형 두개를 기준으로 대칭인 경우(1)와
	//반으로 갈랐을 때 양 옆이 대칭인 경우(2)를 고려해야 한다.
	//즉 두가지 경우를 고려해야 하기 때문에 식이 두개
	ret = (ret - tiling(width / 2) + MOD) % MOD;	//(2)
	ret = (ret - tiling(width / 2 - 1) + MOD) % MOD;	//(1)
	return ret;
}

int cache2[101];
//2*width 크기의 사각형을 채우는 비대칭 방법의 수를 반환한다.
//(1) 양쪽에 2*1 직사각형을 놓을 경우(남은 칸 대칭이면 안됨)
//(2) 양쪽에 1*2 직사각형을 놓을 경우(남은 칸 대칭이면 안됨)
//(3) 왼쪽 끝에는 2*1 직사각형 오른쪽 끝에는 1*2 직사각형(남은 칸 대칭어여도 됨)
//(4) 왼쪽 끝에는 1*2 직사각형 오른쪽 끝에는 2*1 직사각형(남은 칸 대칭어여도 됨)
int asymmetric2(int width) {
	//기저 사례: 너비가 2이하인 경우
	if (width <= 2)
		return 0;
	//메모이제이션
	int& ret = cache2[width];
	if (ret != -1)return ret;
	ret = asymmetric2(width - 2) % MOD;	//(1)
	ret = (ret + asymmetric2(width - 4)) % MOD;	//(2)
	ret = (ret + asymmetric2(width - 3)) % MOD;	//(3)
	ret = (ret + asymmetric2(width - 3)) % MOD;	//(4)
}


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;
	while (t--) {
		memset(cache, -1, sizeof(cache));
		cin >> n;
		cout << asymmetric(n) << "\n";

	}
	return 0;
}