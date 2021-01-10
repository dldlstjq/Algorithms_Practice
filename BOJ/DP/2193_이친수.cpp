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


/////////////////////////////////////////////////
/*
재귀함수로 푼 풀이.
num은 n자리, digit은 첫 자리의 수.
digit이 0이면 0과 1 둘다 올 수 있고 1이면 0밖에 오지 못한다.
그걸 이용해서 점화식을 세우면 정답이다.
int형이 아닌 long long형을 써야 정답을 맞을 수 있다.
*/

#include <iostream>
#include <cstring>

using namespace std;

int n;
long long cache[91][2];

long long pinary(int num, int digit) {
	//한 자리 이친수는 1.
	if (num == 1)
		return 1;
	long long& ret = cache[num][digit];
	if (ret != -1)return ret;
	ret = 0;
	//digit이 1이면 0만 올 수 있다.
	if (digit == 1)
		ret += pinary(num - 1, 0);
	//0이면 0,1 둘 다 올 수 있다.
	else {
		ret += pinary(num - 1, 0);
		ret += pinary(num - 1, 1);
	}

	return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	memset(cache, -1, sizeof(cache));
	cin >> n;
	cout << pinary(n, 1);

	return 0;
}