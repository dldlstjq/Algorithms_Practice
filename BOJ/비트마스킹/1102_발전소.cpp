/*
비트연산을 DP랑 접목시켜 풀려고 하니 막상 생각이 잘 안났다.
켜진 발전소의 비트를 1로 만드는 것 까진 생각 났는데
DP를 적용하는데 있어서 종료조건과 최소비용을 계산하는 식이 생각나지 않았다.
2차원 배열로 적용한 것도 있고 1차원 배열로 적용한 코드도 있다.
밑의 1차원 배열로 표현한 코드가 더 이해가 잘 되는것 같다.
*/

#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX = 16 + 1;
const int INF = 987654321;

int n, p;
int plant[MAX][MAX];
int bit = 1 << MAX;
int cache[MAX][1 << MAX];

//비트 내 1 세는법
int bitCount(int x) {
	if (x == 0)return 0;
	return x % 2 + bitCount(x / 2);
}

//발전소 here개를 가동 중이고 가동 상태는 visited일 때 추가 발생하는 비용
int solve(int here, int visited) {
	//조건 충족. -1을 하는 이유는 최초 비트를 (1<<MAX)로 잡았기 때문에
	//1이 이미 추가되어 있는 상태여서 -1을 했다.
	if (bitCount(visited) - 1 >= p)
		return 0;
	int& ret = cache[here][visited];
	if (ret != -1)return ret;
	ret = INF;
	for (int i = 0; i < n; ++i) {
		if ((visited & (1 << i)) == 0) {//꺼진 발전소를 찾고
			int next = visited | (1 << i);	//해당 발전소를 켰다고 가정
			for (int j = 0; j < n; ++j)
				if (next & (1 << j))//해당 발전소를 킨 다음 단계로 이동
					ret = min(ret, plant[here][i] + solve(j, next));
		}
	}
	return ret;

}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	memset(cache, -1, sizeof(cache));
	cin >> n;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			cin >> plant[i][j];

	string is_on;
	cin >> is_on;
	//켜진 발전소의 비트를 1로 만든다.
	for (int i = 0; i < is_on.length(); ++i)
		if (is_on[i] == 'Y')
			bit |= (1 << i);

	cin >> p;
	if (p == 0)
		cout << 0;
	else {
		int ret = INF;
		for (int i = 0; i < n; ++i)
			if (is_on[i] == 'Y')
				ret = min(ret, solve(i, bit));
		if (ret == INF)
			cout << -1;
		else
			cout << ret;
	}
	return 0;
}


////////////////////////////////
//1차원 DP로 해결
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <algorithm>
using namespace std;

int n, p, i, j, cur, full;
int cost[16][16];
int dp[1 << 16];
char str[17];

//num개를 가동 중이고, 가동상태는 비트로 stat일때, 추가로 발생하는 비용
int func(int num, int stat) {
	//기저 사례: p개 가동 중이면 반환
	if (num == p)
		return 0;

	int& ref = dp[stat];
	if (ref != -1)
		return ref;

	ref = INT_MAX;

	for (int from = 0; from < n; ++from) {
		//먼저 가동중인 발전기를 찾고
		if (stat & (1 << from)) {
			//고장난 발전기를 찾는다.
			for (int to = 0; to < n; ++to) {
				if (from == to)
					continue;
				//dp[stat] = min(dp[stat], func(num + 1, stat | (1 << 고장난 발전기)) + cost[가동 발전기][고장 발전기]
				if ((stat & (1 << to)) == 0)
					ref = min(ref, func(num + 1, stat | (1 << to)) + cost[from][to]);
			}
		}
	}

	return ref;
}

int main() {
	memset(dp, -1, sizeof(dp));

	scanf("%d", &n);

	full = (1 << n) - 1;
	for (i = 0; i < n; ++i)
		for (j = 0; j < n; ++j)
			scanf("%d", &cost[i][j]);

	scanf("%s %d", str, &p);

	int cnt = 0;
	for (i = 0; i < n; ++i) {
		if (str[i] == 'Y') {
			cur = cur | (1 << i);
			cnt++;
		}
	}

	if (cnt == 0) {
		if (p == 0)
			puts("0");
		else
			puts("-1");
	}
	else if (cnt >= p)
		puts("0");

	else
		printf("%d", func(cnt, cur));

	return 0;
}