/*
단순한 완전탐색 문제인데 오랫동안 문제를 풀지 않아서 그런지
확실한 방법이 딱 떠오르지 않았다.
처음에는 수를 하나씩 더해가며 100을 넘으면 빼는 식으로 하려고 했는데
구현에 어려움이 있었다.

이전에도 비슷한 문제를 푼 것 같은데 전체를 다 더한 다음 수를 빼면서
정답을 찾으면 훨씬 수월하게 문제를 풀 수 있었다.

그리고 정답을 구하자마자 프로그램을 종료시키지 않아 오답이 나왔다.
*/

/*
* 2021.07.01 다시 풀어도 풀이가 생각 안났다. 처음부터 하나씩 더해가며 100이 되는걸 찾는 줄 알았는데
* 다 더하고 난 후 2개씩 빼면서 확인하면 더 쉽게 찾을 수 있다.
*/


#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> v(9);

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int sum = 0;
	for (int i = 0; i < 9; ++i) {
		cin >> v[i];
		sum += v[i];
	}

	sort(v.begin(), v.end());

	for (int i = 0; i < 9; ++i) {
		for (int j = i + 1; j < 9; ++j) {
			if (sum - v[i] - v[j] == 100) {
				for (int k = 0; k < 9; ++k)
					if (k != i && k != j)
						cout << v[k] << "\n";
				return 0;
			}
		}
	}

	return 0;
}