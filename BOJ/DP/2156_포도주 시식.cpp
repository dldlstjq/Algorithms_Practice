//2019년 8월 풀이

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int dp[10001];
int wine[10001];

int maximum(int a, int b, int c) {
	return a > b ? (a > c ? a : c) : (b > c ? b : c);
}

int main()
{
	int n;
	int sum = 0;

	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d", &wine[i]);

	//처음과 두번째는 다 먹어야 최대
	dp[1] = wine[1];
	dp[2] = wine[1] + wine[2];

	//포도주를 두번연속 안먹을때 dp[i-1]
	//현재 포도주를 먹고 이전 포도주 안먹었을때  dp[i - 2] + wine[i]
	//현재와 이전 포도주 먹었을 때 dp[i - 3] + wine[i - 1] + wine[i]
	//이 중 최대값이 정답
	for (int i = 3; i <= n; i++) {
		dp[i] = maximum(dp[i - 1], dp[i - 2] + wine[i], dp[i - 3] + wine[i - 1] + wine[i]);
	}

	printf("%d", dp[n]);



	return 0;
}