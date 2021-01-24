/*
2차원 배열의 경우 psum을 만드는게 은근 헷갈린다.
0,0부터 시작할 경우 0행, 0열의 예외상황을 만들어서 따로 처리해야 한다.
메모리를 아끼고 싶다면 원래 배열을 만들지 않아도 된다.
우선 연습을 위해 원래 배열을 입력받아 거기서 psum을 만들고
구간 합을 구했다.
*/

#include <iostream>
using namespace std;

int n, m;
int psum[1025][1025];
int a[1025][1025];

void make_psum() {
	psum[0][0] = a[0][0];
	for (int j = 1; j < n; ++j)
		psum[0][j] = psum[0][j - 1] + a[0][j];

	for (int i = 1; i < n; ++i)
		for (int j = 0; j < n; ++j) {
			if (j == 0)
				psum[i][j] = psum[i - 1][j] + a[i][j];
			else
				psum[i][j] = psum[i - 1][j] + psum[i][j - 1] - psum[i - 1][j - 1] + a[i][j];
		}
}

int gridSum(int x1, int y1, int x2, int y2) {
	int ret = psum[x2][y2];
	if (x1 > 0)ret -= psum[x1 - 1][y2];
	if (y1 > 0)ret -= psum[x2][y1 - 1];
	if (y1 > 0 && x1 > 0)ret += psum[x1 - 1][y1 - 1];
	return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			cin >> a[i][j];

	make_psum();

	for (int i = 0; i < m; ++i) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		cout << gridSum(x1 - 1, y1 - 1, x2 - 1, y2 - 1) << "\n";

	}
	return 0;
}


/////////////////////////////
/*
(1,1)부터 시작하는 코드.
원래 배열을 따로 선언하지 않고 숫자를 입력받는 즉시 psum을 만든다.
*/
#include <cstdio>
using namespace std;

int main() {
	// 입력받으면서 prefix sum을 채움(행, 열 1칸씩 더 필요함에 유의)
	int N, M, pSum[1025][1025] = { 0 };
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			int A;
			scanf("%d", &A);
			pSum[i + 1][j + 1] = pSum[i + 1][j] + pSum[i][j + 1] - pSum[i][j] + A;
		}
	}

	// 각 쿼리를 처리
	for (int i = 0; i < M; ++i) {
		int x1, y1, x2, y2;
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		printf("%d\n", pSum[x2][y2] - pSum[x1 - 1][y2] - pSum[x2][y1 - 1] + pSum[x1 - 1][y1 - 1]);
	}
}