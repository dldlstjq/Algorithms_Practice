//2019년 8월 풀이. 11726이랑 비슷한 문제
#include <stdio.h>

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