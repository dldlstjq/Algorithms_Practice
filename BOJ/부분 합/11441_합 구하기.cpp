#include <iostream>
using namespace std;

int n;
int psum[100001];

int partialSum(int a, int b) {
	if (a == 1)return psum[b];
	return psum[b] - psum[a - 1];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;

	for (int i = 1; i <= n; ++i) {
		int a;
		cin >> a;
		if (i == 1)
			psum[i] = a;
		else
			psum[i] = psum[i - 1] + a;
	}

	int m;
	cin >> m;
	for (int i = 0; i < m; ++i) {
		int c, d;
		cin >> c >> d;
		cout << partialSum(c, d) << "\n";
	}
	return 0;
}