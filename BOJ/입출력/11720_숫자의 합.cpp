#include <iostream>

using namespace std;

int main() {
	int n = 0;
	int sum = 0, num;
	cin >> n;
	for (int i = 0; i < n; i++) {
		scanf("%1d", &num);
		sum += num;
	}
	cout << sum << endl;
	return 0;
}