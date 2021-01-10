/*
책의 재귀호출을 이용한 알고리즘이 아닌 for문을 이용해서도 풀 수 있을 것 같아
for문을 사용해 풀었다.

(0,0)의 경우 그대로 넣어주고
열이 0인 경우와 행의 맨 마지막 부분은 더하는 수가 하나밖에 없기 때문에 따로 구현해주고
다른 부분은 바로 위쪽과 왼쪽 대각선 합 중 최대값을 계산하면 된다.

cache를 계산할 때 현재 값과 이전에 계산해둔 값을 이용해야 하는데
이전에 계산해둔 cache값이 아닌 triangle 값을 이용해서 오답을 많이 받았다.

재귀함수를 이용하면 한결 더 간단한 코드를 얻을 수 있지만
이해하는데는 for문을 이용하는 것이 더 직관적으로 와 닿는다.
*/

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int n;	//삼각형 높이
int triangle[100][100];
int cache[100][100];

int cache2[100][100];
//(y,x) 위치부터 맨 아래줄까지 내려가면서 얻을 수 있는 최대 경로의 합을 반환한다.
int path2(int y, int x) {
	//기저사례
	if (y == n - 1)
		return triangle[y][x];
	//메모이제이션
	int& ret = cache2[y][x];
	if (ret != -1)
		return ret;
	return ret = max(path2(y + 1, x), path2(y + 1, x + 1)) + 
		triangle[y][x]);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;
	while (t--) {
		
		cin >> n;
		if (n < 2 || n>100)
			exit(-1);


		for (int i = 0; i < n; ++i)
			for (int j = 0; j <= i; ++j)
				cin >> triangle[i][j];

		memset(cache, -1, sizeof(cache));

		//0, 1행은 경우가 하나밖에 없으므로 바로 구해줌
		cache[0][0] = triangle[0][0];
		cache[1][0] = triangle[0][0] + triangle[1][0];
		cache[1][1] = triangle[0][0] + triangle[1][1];

		for (int i = 2; i < n; ++i) {
			for (int j = 0; j <= i; ++j) {
				//세로가 0인 부분은 자기자신과 바로 위 숫자의 합
				if (j == 0)
					cache[i][j] = triangle[i][j] + cache[i - 1][j];
				//각 행의 제일 끝부분은 왼쪽 대각선 위의 합 하나밖에 없다.
				else if (i == j)
					cache[i][j] = triangle[i][j] + cache[i - 1][j - 1];
				//나머지 부분은 바로 위의 값과 왼쪽 대각선 위의 합중 최대
				else
					cache[i][j] = max(triangle[i][j] + cache[i - 1][j],
						triangle[i][j] + cache[i - 1][j - 1]);
			}
		}

		cout << *max_element(&cache[n - 1][0], &cache[n - 1][n - 1]) << "\n";
		/*int ret = 0;
		for (int i = 0; i < n; ++i)
			ret = max(ret, cache[n - 1][i]);
		cout << ret << "\n";*/
	}

	return 0;
}