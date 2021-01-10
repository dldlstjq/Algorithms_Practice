/*
반복문이 아닌 재귀함수로 먼저 풀었다.
k만 함수 인자로 넣어줘서 동전 가격만큼 빼면서 그 값이 0이면 0울,
0이 아니면 값이 없으므로 INF를 반환하게 했다.
*/

#include <iostream>
#include <cstring>

using namespace std;

const int INF = 987654321;
int n, k;
int cache[10001];
int coin[101];

//k원을 0원으로 만들 수 있을 때 최소 동전 개수를 구한다.
int solve(int start) {
	//start가 음수면 딱 k원이 될 수 없다.
	if (start < 0)
		return INF;
	//start=0이면 동전으로 k원을 만들 수 있다.
	if (start == 0)
		return 0;
	int& ret = cache[start];
	if (ret != -1)return ret;
	ret = INF;
	//동전을 하나씩 빼면서 최소 갯수를 구한다.
	for (int i = 0; i < n; ++i) {
		ret = min(ret, solve(start - coin[i]) + 1);
	}
	return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	memset(cache, -1, sizeof(cache));
	cin >> n >> k;
	for (int i = 0; i < n; ++i)
		cin >> coin[i];
	if (solve(k) == INF)
		cout << -1;
	else
		cout << solve(k);
	return 0;
}


//////////////////////////////////////////
//반복문을 이용한 풀이

#include <cstdio>
#include <climits>

using namespace std;

int get_min(int a, int b) { return a < b ? a : b; }

int main() {

	int n, k, i, j;

	scanf("%d %d", &n, &k);

	int dp[100001];
	int coins[100];

	dp[0] = 0;
	for (i = 1; i <= k; i++) dp[i] = INT_MAX;

	for (i = 0; i < n; i++) {
		scanf("%d", &coins[i]);
		dp[coins[i]] = 1;
	}

	for (i = 1; i <= k; i++) {
		for (j = 0; j < n; j++) {
			if (dp[i] == 1) break;
			else if (i - coins[j] < 0 || dp[i - coins[j]] == INT_MAX) continue;
			else dp[i] = get_min(dp[i], 1 + dp[i - coins[j]]);
		}
	}

	if (dp[k] == INT_MAX) printf("-1\n");
	else printf("%d\n", dp[k]);
	return 0;
}