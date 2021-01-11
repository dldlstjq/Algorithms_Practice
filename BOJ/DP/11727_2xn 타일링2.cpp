//2019년 8월 풀이. 11726이랑 비슷한 문제
#include <stdio.h>

//재귀함수로 푼 풀이
const int MOD = 10007;
int n;
int cache[1001];

int solve(int num) {
	if (num == 1)
		return 1;
	if (num == 2)
		return 3;
	int& ret = cache[num];
	if (ret != -1)return ret;
	ret = 0;
	ret = (solve(num - 1) + 2 * solve(num - 2)) % MOD;
	return ret % MOD;
}

int main()
{
	int dp[1001] = { 0 };
	int n = 0;

	scanf("%d", &n);

	dp[0] = 0;
	dp[1] = 1;
	dp[2] = 3;
	for (int i = 3; i <= n; i++) {
		dp[i] = (dp[i - 2] * 2) + dp[i - 1];
		dp[i] %= 10007;
	}
	printf("%d", dp[n]);
	return 0;
}