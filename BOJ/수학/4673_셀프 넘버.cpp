/*
1부터 10000까지 계산해서 있으면 true 표시해주고
false인 것만 출력하면 된다.
*/

#include <iostream>

using namespace std;

bool arr[10001] = { 0 };

int d(int num) {
	int ret = 0;
	ret += num;
	while (num > 0) {
		ret += (num % 10);
		num /= 10;
	}
	return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	for (int i = 1; i < 10001; ++i) {
		int next = d(i);
		if (next <= 10001)
			arr[next] = true;
	}

	for (int i = 1; i < 10001; ++i)
		if (arr[i] == false)
			cout << i << "\n";

	return 0;
}