/*
접미사(prefix)도 되고 접두사(suffix)도 되는 문자열의 최대 길이를 구해야 한다.
kmp 알고리즘의 pi를 구해서 어떻게 해아할 것 같았는데 정확한 정답을 어떻게 도출해야 할지
생각이 나질 않았다.

블로그를 보니 단순히 pi[L-1]값에 달려있다고 했다.
4354_문자열 제곱과 비슷한 문제였던 것 같은데 함수를 이용하는 방법을 잘 알아야곘다.
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> getpi(const string& s) {
	int n = s.size();
	int j = 0;
	vector<int>pi(n, 0);
	for (int i = 1; i < n; ++i) {
		while (j > 0 && s[i] != s[j])
			j = pi[j - 1];
		if (s[i] == s[j])
			pi[i] = ++j;
	}
	return pi;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int L;
	string s;
	cin >> L;
	cin >> s;

	vector<int> pi = getpi(s);

	cout << L - pi[L - 1];
	return 0;
}