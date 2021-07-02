/*
문제 자체는 그렇게 어렵게 느껴지지 않았는데 사탕 개수 구하는 부분에서
헤맸다.
양 옆과 아래위를 바꾼 후 최대 개수를 구하는데 사탕을 바꾼 위치부터
구하는 것이 아니라 처음부터 하나씩 다 살펴보는 것이 핵심이었다.
*/

// 2021.07.02 서로 인접한 두 개만 바꾸면 되기 때문에 현재 위치에서 오른쪽, 아래만 바꾼 뒤 전체 배열을 확인한다.
// 전체 개수 확인 시 배열 인덱스와 길이 체크를 잘 해야 된다.
#include <iostream> 
#include <vector> 
#include <algorithm>
#include <queue>
#include <string>
using namespace std;

const int MAX = 50 + 1;
int N;
char board[MAX][MAX];
bool visited[MAX][MAX];

int dy[4] = { 0,1 };
int dx[4] = { 1,0 };
int ret;

void check() {
	// 행
	for (int i = 0; i < N; ++i) {
		int sum = 1;
		for (int j = 1; j < N; ++j) {
			if (board[i][j - 1] == board[i][j])
				sum++;
			else {
				// 한 행에서 중간에 끊길 때 확인
				ret = max(ret, sum);
				sum = 1;
			}
		}
		// 한 행이 끝날 때 확인
		ret = max(ret, sum);
	}

	// 열
	for (int i = 0; i < N; ++i) {
		int sum = 1;
		for (int j = 1; j < N; ++j) {
			if (board[j - 1][i] == board[j][i])
				sum++;
			else {
				ret = max(ret, sum);
				sum = 1;
			}
		}
		ret = max(ret, sum);
	}


}

void solve(int y, int x, int sum) {
	for (int i = 0; i < 2; ++i) {
		int ny = y + dy[i];
		int nx = x + dx[i];

		// 범위 밖
		if (!(0 <= ny && ny < N && 0 <= nx && nx < N))
			continue;

		// 같은 문자
		if (visited[ny][nx] || board[y][x] == board[ny][nx])
			continue;

		swap(board[y][x], board[ny][nx]);
		check();
		swap(board[y][x], board[ny][nx]);
	}
}

int main(int argc, char** argv) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> N;
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			cin >> board[i][j];

	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N - 1; ++j) {
			solve(i, j, 0);
		}

	cout << ret;


	return 0;
}

/////////////////////////////////

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int n;
vector<string> board;

int candy() {
	int ret = 1;
	//양 옆
	for (int i = 0; i < n; ++i) {
		int temp = 1;
		for (int j = 1; j < n; ++j) {
			if (board[i][j - 1] == board[i][j])
				temp++;
			else {
				ret = max(ret, temp);
				temp = 1;
			}
		}
		//이 부분이 필요한 이유는 -> n=3, YYY일때 저 부분이 없다면 0이 된다. 
		//(Why? else을 지나지 않게 되기떄문에 ret변경x
		ret = max(ret, temp);
	}
	//위 아래
	for (int i = 0; i < n; ++i) {
		int temp = 1;
		for (int j = 0; j < n - 1; ++j) {
			if (board[j + 1][i] == board[j][i])
				temp++;
			else {
				ret = max(ret, temp);
				temp = 1;
			}
		}
		//이 부분이 필요한 이유는 -> n=3, YYY일때 저 부분이 없다면 0이 된다. 
		//(Why? else을 지나지 않게 되기떄문에 ret변경x
		ret = max(ret, temp);
	}
	return ret;
}


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	board.resize(n);
	for (int i = 0; i < n; ++i)
		cin >> board[i];

	int result = 0;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n - 1; j++) {
			//양 옆 swap
			swap(board[i][j], board[i][j + 1]);
			result = max(result, candy());
			swap(board[i][j], board[i][j + 1]);

			//위 아래 swap
			swap(board[j][i], board[j + 1][i]);
			result = max(result, candy());
			swap(board[j][i], board[j + 1][i]);
		}
	cout << result << "\n";


	return 0;
}