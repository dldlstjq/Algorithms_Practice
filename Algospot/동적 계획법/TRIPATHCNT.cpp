/*
TRIANGLEPATH 문제에서 구한 path에서 값이 더 큰쪽으로 가도록 함수를 구현하면
쉽게 풀린다.
*/

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int n, triangle[100][100];
int cache2[100][100];

//(y,x)위치부터 맨 아래줄까지 내려가면서 얻을 수 있는 최대 경로의 합을 반환한다.
int path2(int y, int x) {
	//기저 사례
	if (y == n - 1)
		return triangle[y][x];
	//메모이제이션
	int& ret = cache2[y][x];
	if (ret != -1)
		return ret;
	return ret = max(path2(y + 1, x), path2(y + 1, x + 1)) +
		triangle[y][x];
}

int countCache[100][100];
//(y,x)에서 시작해서 맨 아래줄까지 내려가는 경로 중 최대 경로의
//개수를 반환한다.
int count(int y, int x) {
	//기저사례: 맨 아래줄에 도달한 경우
	if (y == n - 1)
		return 1;
	//메모이제이션
	int& ret = countCache[y][x];
	if (ret != -1)
		return ret;
	ret = 0;
	if (path2(y + 1, x + 1) >= path2(y + 1, x))
		ret += count(y + 1, x + 1);
	if (path2(y + 1, x + 1) <= path2(y + 1, x))
		ret += count(y + 1, x);
	return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;
	while (t--) {
		memset(cache2, -1, sizeof(cache2));
		memset(countCache, -1, sizeof(countCache));
		cin >> n;
		for (int i = 0; i < n; ++i)
			for (int j = 0; j <= i; ++j)
				cin >> triangle[i][j];
		cout << count(0, 0) << "\n";
	}

	return 0;
}