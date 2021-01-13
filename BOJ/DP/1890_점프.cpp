/*
1520_내리막길 문제랑 거의 똑같은 문제이다.
여기서는 해당 숫자만큼 점프할 수 있다는 건데 그것만 고쳐주면 정답을 받을 수 있다.
다만 종만북에 나오는 것처럼 짜면 메모리초과가 나온다.
자세한건 코드 참고
*/

#include <iostream>
#include <cstring>

using namespace std;

int n;
int board[100][100];
long long cache[100][100];

//모든 칸이 0안 경우 ret=0을 설정했기 때문에 다시 (0,0)을 하더라도
//ret!=-1이 성립하기 때문에 바로 0을 반환한다.
long long solve(int y, int x) {
	if (y == n - 1 && x == n - 1)
		return 1;
	long long& ret = cache[y][x];
	if (ret != -1)return ret;
	
	//여기서 초기값을 설정하기 때문에 dp가능
	ret = 0;

	int ny = y + board[y][x];
	int nx = x + board[y][x];
	if (nx < n)
		ret += solve(y, nx);

	if (ny < n)
		ret += solve(ny, x);
	return ret;
}

//이렇게 코드를 짜면 모든 칸이 0인 경우
//(0, 0)만 계속 반복하게 되므로 메모리 초과가 발생한다.
//처음엔 배열을 너무 크게 잡은 것 같아 그런 줄 알았는데 이런 문제가 있었다.
int solve(int y, int x) {
	if (y >= n || x >= n) return 0;
	if (y == n - 1 && x == n - 1) return 1;
	if (dp[y][x] != -1) return dp[y][x];
	int jumpsize = board[y][x];
	dp[y][x] = (solve(y + jumpsize, x) + solve(y, x + jumpsize));
	return dp[y][x];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	memset(cache, -1, sizeof(cache));
	cin >> n;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			cin >> board[i][j];

	cout << solve(0, 0);
	return 0;
}