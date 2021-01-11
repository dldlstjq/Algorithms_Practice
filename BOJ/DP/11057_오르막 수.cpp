#include <iostream>


//재귀함수 풀이. num을 1씩 감소시키면서
//digit과 크거나 같은 수에 대해 오르막수의 개수를 더해준다.
//메인에서는 n행에 해당하는 원소를 다 더하면 답이 나온다.
const int MOD = 10007;
int n;
int cache[1001][10];

//길이가 num이고 끝자리가 digit인 오르막수의 갯수
int solve(int num, int digit) {
	//1자리수 이거나 끝이 9인 경우 수가 하나밖에 없음
	if (num == 1 || digit == 9)
		return 1;
	int& ret = cache[num][digit];
	if (ret != -1)return ret;

	ret = 0;
	//digit부터 9까지 모든 수의 합이 오르막수의 갯수
	for (int i = digit; i < 10; ++i)
		ret = (ret + solve(num - 1, i)) % MOD;
	return ret;
}



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