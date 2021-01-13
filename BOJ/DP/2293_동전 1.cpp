/*
재귀함수로 푸는 연습을 하기 위해 재귀로 풀었는데 터무니 없이 큰 값이
나와서 재귀로는 해결하지 못했다.
인터넷에 찾아보니 순서는 달라도 같은 종류의 동전을 사용하면 같은 것인데
이를 모두 다른 값으로 취급하여 큰 수가 나온다는 것이었다.
1,1,1,2와 2,1,1,1은 같은 종류지만 순서가 달라 다른 경우로 취급해서 큰 값이 나온다.
따라서 재귀로 문제를 해결하기 위해서는 2차원 배열을 사용해야 한다.

반복문을 사용하면 한결 간결하게 코드를 짤 수 있다.
재귀함수 풀이 연습을 위해 무작정 재귀함수로만 풀려고 하는데
잘 안되면 반복문 풀이도 해봐야 되겠다고 느꼈다.
*/

#include <iostream>
#include <cstring>
using namespace std;

int n, k;
int cache[10001];
int coin[101];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	memset(cache, 0, sizeof(cache));
	cin >> n >> k;
	for (int i = 1; i <= n; ++i)
		cin >> coin[i];

	cache[0] = 1;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= k; ++j)
			if (j >= coin[i])
				cache[j] += cache[j - coin[i]];
	cout << cache[k];

	return 0;
}


/////////////////////////////////////////
//재귀로 구현한 코드. 재귀로 해결할거면 2차원배열 사용.
//근데 이마저도 메모리 초과가 난단다.
int solve(int start) {
	if (start == 0)
		return 1;

	int& ret = cache[start];
	if (ret != -1)return ret;
	ret = 0;

	for (int i = 1; i <= n; ++i)
		if (start - coin[i] >= 0)
			ret += solve(start - coin[i]);
	return ret;
}