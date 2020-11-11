#include <iostream>
#include <math.h>

using namespace std;

int main() {
	std::ios_base::sync_with_stdio(false);
	int n;

	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = -1 * (n - 1); j <= n - 1; j++) {
			if (i >= abs(j))
				cout << "*";
			else if (j > i)
				break;
			else
				cout << " ";
		}
		cout << "\n";
	}
	return 0;
}