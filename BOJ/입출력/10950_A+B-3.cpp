#include <iostream>

using namespace std;
int main() {
	int a, b, arr[1001], t;
	cin >> t;
	for (int i = 0; i < t; i++) {
		cin >> a >> b;
		arr[i] = a + b;
	}

	for (int i = 0; i < t; i++) {
		cout << arr[i] << '\n';
	}

	return 0;
}