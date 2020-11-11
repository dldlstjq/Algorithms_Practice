#include <iostream>

using namespace std;

int main() {
	std::ios_base::sync_with_stdio(false);
	int n;
	cin >> n;
	cout << n * (n + 1) / 2 << '\n';
	return 0;
}