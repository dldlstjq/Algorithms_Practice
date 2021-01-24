/*
1. 소가 위치할 수 있는 범위가 1, 000, 000 * 1, 000, 000이므로 이차원 배열로는 표현할 수 없습니다.
2. 따라서, 좌표 해쉬 맵과 이진 탐색 트리(set)을 이용하여 좌표를 오름차순으로 압축합니다.
3. 좌표를 압축한 순서대로 전처리를 진행합니다.
4. 울타리를 모든 가능한 구간에 세워보고 사분면에 있는 소의 최대 수가 최소가 되는 지점을 업데이트합니다.

--------------------------------------------------------------------------------------------------------------

unordered map은 자바의 hashMap과 기능이 같다. 정렬되지않은 사전 구조로써 삽입 검색 삭제가 상수시간에 이뤄진다.

일단 x,y배열에 입력 값들을 받고 -> 배열에 저장된 것들을 순서대로 조회하며 xSet, ySet에 중복제거, 정렬된 값을 저장하고 
-> set에 저장된 것들을 순서대로 조회하면서 상대적 순서를 xHash와 yHash에 저장한다.

ex)입력이 (3, 2), (3,7), (10,6), (11,11)인 경우
xSet : 3, 10, 11
ySet : 2, 6, 7, 11
xHash[3] = 0, xHash[10] = 1, xHash[11] = 2;
yHash[2] = 0, yHash[6] =1, yHash[7] = 2, yHash[11] = 3;

x[i] = r, y[i] = c라고 하면 (xHash[r], yHash[c])가 (x[i], y[i])의 차원압축된 값이다.
(1차원압축과 다를 바 없음. 더 어려워지는 것이 아니다.)

차원압축만 되면 바로 풀릴 줄 알았는데, 네 구간에 포함된 소의 개수를 세는 로직을 O(4*n)으로 짜면 시간초과가 난다.
-> 2차원 구간합배열을 사용해야한다.
*/

#include <cstdio>
#include <set>
#include <unordered_map>
#include <algorithm>
using namespace std;

int pSum[1001][1001];

inline int rangeSum(int x1, int y1, int x2, int y2) {
	return pSum[x2][y2] - pSum[x2][y1] - pSum[x1][y2] + pSum[x1][y1];
}

int main() {
	int N, x[1000], y[1000], X = 0, Y = 0;
	unordered_map<int, int> xHash, yHash;
	set<int> xSet, ySet;
	scanf("%d", &N);
	for (int i = 0; i < N; ++i) {
		scanf("%d %d", x + i, y + i);
		xSet.insert(x[i]);
		ySet.insert(y[i]);
	}
	for (int x : xSet)
		xHash[x] = X++;
	for (int y : ySet)
		yHash[y] = Y++;
	int A[1000][1000] = { 0, };
	for (int i = 0; i < N; ++i)
		++A[xHash[x[i]]][yHash[y[i]]];
	for (int i = 0; i < X; ++i)
		for (int j = 0; j < Y; ++j)
			pSum[i + 1][j + 1] = pSum[i + 1][j] + pSum[i][j + 1] - pSum[i][j] + A[i][j];

	int result = N;
	for (int i = 0; i <= X; ++i) {
		for (int j = 0; j <= Y; ++j) {
			int temp = max(rangeSum(0, 0, i, j), rangeSum(i, j, X, Y));
			temp = max(rangeSum(0, j, i, Y), temp);
			temp = max(rangeSum(i, 0, X, j), temp);
			result = min(temp, result);
		}
	}
	printf("%d\n", result);
}




////////////////////////////////////////////////////
//다른 블로그의 코드를 따라했는데 답이 안나온다....
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_map>

using namespace std;

const int MAX = 1000 + 1;

int arr[MAX][MAX], psum[MAX][MAX];
int y[MAX], x[MAX];
//좌표 압축을 위해
unordered_map<int, int> yHash, xHash;
set<int> ySet, xSet;

int func(int y, int x, int y2, int x2) {
	return psum[y2][x2] - psum[y2][x] - psum[y][x2] + psum[y][x];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> y[i] >> x[i];
		ySet.insert(y[i]);
		xSet.insert(x[i]);
	}

	int Y = 0, X = 0;
	for (int y : ySet)
		yHash[y] = Y++;
	for (int x : xSet)
		xHash[x] = X++;

	//좌표 압축한 결과
	for (int i = 0; i < n; ++i)
		arr[yHash[y[i]]][xHash[x[i]]]++;

	//부분합 전처리
	for (int i = 0; i < Y; ++i)
		for (int j = 0; j < X; ++j)
			psum[i + 1][j + 1] = psum[i + 1][i] + psum[i][j + 1] - psum[i][j] + arr[i][j];

	int ret = n;
	//i, j를 기준으로 울타리를 이어나갈 때 사분면에 존재하는 최소 소의 숫자를 구한다
	for (int i = 0; i <= X; ++i)
		for (int j = 0; j <= Y; ++j) {
			int temp = max(func(0, 0, i, j), func(i, j, Y, X));
			temp = max(temp, func(0, j, i, X));
			temp = max(temp, func(i, 0, Y, j));
			ret = min(ret, temp);
		}
	cout << ret;
	return 0;
}