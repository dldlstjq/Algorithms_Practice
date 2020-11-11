#include <iostream>

using namespace std;

int main() {
	std::ios_base::sync_with_stdio(false);
	int n;

	cin >> n;

	for (int i = 1; i <= n; ++i) {
		//맨 마지막에는 모두 출력
		if (i == n) {
			for (int j = 1; j <= 2 * n - 1; j++)
				cout << "*";
			break;
		}

		//그 외에는 규칙에 맞게
		for (int j = 1; j <= n - i; ++j) {
			cout << " ";
		}

		for (int j = 1; j < 2 * i - 1; ++j) {
			if (j == 1 || j == 2 * i - 1)
				cout << "*";
			else
				cout << " ";
		}
		cout << "*\n";
	}
	return 0;
}