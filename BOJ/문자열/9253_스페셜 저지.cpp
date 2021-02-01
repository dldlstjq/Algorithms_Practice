/*
9249_최장 공통 부분 문자열의 답이 맞는지 아닌지 판별하는 문제이다.
9249번 문제를 먼저 풀어보려고 했는데 잘 안돼서 블로그를 확인해보니 
최장 공통 부분 문자열을 찾는 알고리즘은 상당히 어렵다고 한다.

이 문제에서는 주어진 정답이 실제 답과 동일하고 길이도 일치한다고 했기 때문에
정답 문자열이 A,B 두 문자열에 나타나는지만 확인하면 되는 거였다.

최장 공통 부분 문자열을 구하는 알고리즘은 무엇인지 찾아봐야겠다.
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> getpi(const string& S) {
	int n = S.size();
	int j = 0;
	vector<int> pi(n, 0);
	for (int i = 1; i < n; ++i) {
		while (j > 0 && S[i] != S[j])
			j = pi[j - 1];
		if (S[i] == S[j])
			pi[i] = ++j;
	}
	return pi;
}

vector< int> kmp(const string& h, const string& p) {
	int n = h.size(), m = p.size();
	int j = 0;
	vector< int> ret;
	vector<int> pi = getpi(p);
	for (int i = 0; i < n; ++i) {
		while (j > 0 && h[i] != p[j])
			j = pi[j - 1];
		if (h[i] == p[j]) {
			++j;
			if (j == m) {
				ret.push_back(i - m + 1);
				j = pi[j - 1];
			}
		}
	}
	return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	string a, b;

	cin >> a;
	cin >> b;

	string ans;
	cin >> ans;

	vector<int> v1 = kmp(a, ans);
	vector<int> v2 = kmp(b, ans);

	//둘 다 일치하는 문자열이 있으면 정답
	if (!v1.empty() && !v2.empty())
		cout << "YES";
	else
		cout << "NO";
	return 0;
}