#include <iostream>

using namespace std;

int main() {
	std::ios_base::sync_with_stdio(false);
	int n, num;
	int max = -10000001, min = 1000001;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> num;
		if (max < num)
			max = num;
		if (min > num)
			min = num;
	}
	cout << min << " " << max << '\n';
	return 0;
}