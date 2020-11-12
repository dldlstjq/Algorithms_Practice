#include <iostream>

int dp[1001][10];

int main() {
	int n = 0;
	int sum = 0;

	cin >> n;

	//길이 1일때는 갯수 1개씩
	for (int i = 0; i < 10; i++)
		dp[1][i] = 1;


	//열이 0~9까지이고 각 열의 의미는 열로 시작하는 오름차순 수 개수이다
	for (int i = 2; i <= n; i++) {
		for (int j = 0; j <= 9; j++) {
			for (int k = j; k <= 9; k++) {
				dp[i][k] += dp[i - 1][j];
				dp[i][k] %= 10007;
			}
		}
	}

	for (int i = 0; i < 10; i++) {
		sum += dp[n][i];
	}

	cout<< sum % 10007;

	return 0;
}