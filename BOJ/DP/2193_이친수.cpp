#include <iostream>

using namespace std;

long long int dp[91][2];

int main() {
	int n = 0;
	long long int sum = 0;
	cin >> n;

	//dp[n][a]=b
	//길이가 n이고 끝자리가 a인 2친수의 개수는 b

	dp[1][0] = 0;
	dp[1][1] = 1;

	for (int i = 2; i <= n; i++) {
		for (int j = 0; j <= 1; j++) {
			if (j == 0) {
				dp[i][j] = dp[i - 1][j] + dp[i - 1][j + 1];
			}
			else
				dp[i][j] = dp[i - 1][j - 1];
		}
	}

	for (int i = 0; i <= 1; i++)
		sum += dp[n][i];

	cout << sum << '\n';
	return 0;
}