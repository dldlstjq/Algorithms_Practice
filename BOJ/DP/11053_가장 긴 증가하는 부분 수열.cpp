//2019년 8월 풀이

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int MAX(int a, int b)
{
	return a > b ? a : b;
}

int main()
{
	int n;
	int ary[1001] = { 0 };
	int dp[1001] = { 0 };
	int result = 0;

	scanf("%d", &n);

	for (int i = 1; i <= n; i++) {
		scanf("%d", &ary[i]);
	}


	for (int i = 1; i <= n; i++) {
		dp[i] = 1;

		for (int j = 0; j < i; j++) {
			if (ary[j] < ary[i]) {
				dp[i] = MAX(dp[i], dp[j] + 1);
			}
		}
		if (result < dp[i])
			result = dp[i];
	}

	printf("%d\n", result);

	return 0;
}