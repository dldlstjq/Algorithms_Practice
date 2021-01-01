/*
완전탐색 답게 n의 범위인 1부터 1000000까지 전부 계산해서
생성자가 있는지 찾아본다.
자리수 합은 string으로 변환해 반복문으로 하나씩 더했다.
i가 n보다 크거나 같으면 생성자가 없기때문에 종료한다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;
	int ans = -1;
	for (int i = 1; i <= 1000000; ++i) {
		int sum = 0;
		string s = to_string(i);

		for (int j = 0; j < s.length(); ++j)
			sum += s[j] - '0';
		sum += i;

		//합이 n과 같으면 생성자
		if (sum == n) {
			ans = i;
			break;
		}
		//i가 n과 크거나 같으면 생성자가 없음
		else if (i >= n)
			break;
	}

	if (ans == -1)
		cout << 0;
	else
		cout << ans;

	return 0;
}