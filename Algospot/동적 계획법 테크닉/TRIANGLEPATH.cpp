/*
8장에서는 재귀함수로 구현했지만 여기서는 반복문을 활용했다.
내가 반복문으로 풀었을때는 위에서 아래로 내려왔지만
책에서는 아래에서 위로 올라가는 식으로 코드를 구현했다.

그리고 공간복잡도를 줄이기 위해 캐시를 다 사용하는 것이 아니라
두 줄만 사용해서 계산에 필요한 것만 남겼다.
*/

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

//삼각형 위 최대경로문제 반복적 동적 계획법 알고리즘
int n, triangle[100][100];
int C[100][100];
int iterative() {
	//기저 사례를 계산한다.
	for (int x = 0; x < n; ++x)
		C[n - 1][x] = triangle[n - 1][x];
	//다른 부분을 계산한다.
	for (int y = n - 2; y >= 0; --y)
		for (int x = 0; x < y + 1; ++x)
			C[y][x] = max(C[y + 1][x], C[y + 1][x + 1]) + triangle[y][x];
	return C[0][0];
}

//슬라이딩 윈도롤 이용한 삼각형 위 최대경로 알고리즘
int C2[2][10000];
int iterative2() {
	//기저 사례를 계산한다.
	for (int x = 0; x < n; ++x)
		C2[(n - 1) % 2][x] = triangle[n - 1][x];
	//다른 부분을 계산한다.
	for (int y = n - 2; y >= 0; --y)
		for (int x = 0; x < y + 1; ++x)
			C2[y % 2][x] = max(C2[(y + 1) % 2][x], C2[(y + 1) % 2][x + 1]) + triangle[y][x];
	return C2[0][0];
}
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);


	int c;
	cin >> c;
	while (c--) {
		//memset(C, -1, sizeof(C));
		memset(C2, -1, sizeof(C2));

		cin >> n;
		for (int i = 0; i < n; ++i)
			for (int j = 0; j <= i; ++j)
				cin >> triangle[i][j];
		//cout << iterative() << "\n";
		cout << iterative2() << "\n";

	}
	return 0;
}