#include <iostream>

using namespace std;

int main() {
	std::ios_base::sync_with_stdio(false);
	int n;

	cin >> n;

	for (int i = 1; i <= n; i++) {
		for (int j = n; j >= 1; j--) {
			if (i >= j)
				cout << "*";
			else
				cout << " ";
		}
		cout << '\n';
	}

	for (int i = n - 1; i >= 1; i--) {
		for (int j = n; j >= 1; j--) {
			if (i >= j)
				cout << "*";
			else
				cout << " ";
		}
		cout << '\n';
	}
	return 0;
}