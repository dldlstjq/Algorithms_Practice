/*
이 문제도 처음에 문제이해가 잘 안됐다.
알파벳의 순서 A가 주어지고 원문 W를 알파벳 순서에 맞게 하나씩 시프트 시켰을 때
암호문 S에 한번만 나타나면 그 시프트 값을 저장하는 것이었다.

문제 이해가 된 뒤로는 문자를 쉬프트 하되 알파벳 순서에 맞게 해야했는데
그 방법이 잘 떠오르지 않았다.
해결하지 못해 다른 사람의 풀이를 보니 map을 써서 인덱스와 알파벳을 같이 저장했다.
map 사용이 아직 많이 미숙한 것 같고 잘 떠오르지가 않는다.
뭔가 둘이 쌍을 지어 저장하거나 찾을 떄 사용하면 좋을 것 같다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
using namespace std;

vector<int> getPi(const string& s) {
	int n = s.size();
	int j = 0;
	vector<int> pi(n, 0);
	for (int i = 1; i < n; ++i) {
		while (j > 0 && s[i] != s[j])
			j = pi[j - 1];
		if (s[i] == s[j])
			pi[i] = ++j;
	}
	return pi;
}

vector<int> kmp(const string& h, const string& p) {
	int n = h.size(), m = p.size();
	vector<int> pi = getPi(p);
	vector<int> ret;
	int j = 0;
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

	int t;
	cin >> t;
	while (t--) {
		string alpha, origin, password;
		cin >> alpha >> origin >> password;
		int n = alpha.length();

		vector<int> ret;    //kmp 결과 저장
		vector<int> ans;    //정답 저장

		//알파벳의 순서를 map으로 관리한다.
		map<char, int> mp;
		map<int, char> rmp;
		for (int i = 0; i < n; ++i) {
			mp[alpha[i]] = i;
			rmp[i] = alpha[i];
		}

		//인덱스를 한번씩 쉬프트하면서 암호에 한번만 나타나면 ok.
		for (int i = 0; i < n; ++i) {
			if (i) {
				for (int j = 0; j < origin.length(); ++j) {
					origin[j] = rmp[(mp[origin[j]] + 1) % n];
				}
			}
			ret = kmp(password, origin);
			if (ret.size() == 1)
				ans.push_back(i);
		}

		//출력
		if (ans.empty())
			cout << "no solution";
		else if (ans.size() == 1)
			cout << "unique: " << ans.back();
		else {
			cout << "ambiguous: ";
			for (int i = 0; i < ans.size(); ++i)
				cout << ans[i] << " ";
		}
		cout << "\n";
	}
	return 0;
}