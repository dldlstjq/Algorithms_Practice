/*
처음엔 부분합을 구하고 그 중에 가장 큰 수가 답인줄 알았다.
하지만 이렇게 구하면 무조건 첫번째 원소부터 시작하는 부분 합중
최대만 찾기 때문에 -1 2 3 의 경우 5가 최대인데 4를 구하게 된다.
따라서 2중 for문을 통해 psum을 돌면서 모든 부분합의 최대를 구해야 한다.
*/

#include <iostream>

using namespace std;

const int MAX = 1001;
int psum[MAX];

int partialSum(int a, int b) {
	if (a == 0)return psum[b];
	return psum[b] - psum[a - 1];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;
	while (t--) {
		for (int i = 0; i < MAX; ++i)
			psum[i] = 0;

		int n;
		int ret = -987654321;
		cin >> n;
		for (int i = 0; i < n; ++i) {
			int num;
			cin >> num;
			if (i == 0)
				psum[i] = num;
			else
				psum[i] = psum[i - 1] + num;
		}

		//모든 부분합에 대해 계산해야 한다.
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j <= i; ++j) {
				ret = max(ret, partialSum(j, i));
			}
		}
		cout << ret << "\n";
	}

	return 0;
}