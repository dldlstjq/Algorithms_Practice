/*
kmp알고리즘과 관련한 문제여서 kmp만 사용하면 될 줄 알았는데
dp를 써야 해결이 되는 문제였다.
kmp로 일치하는 부분을 찾는 것 까지는 이해되는데
dp에서 ans를 구하는 부분이 잘 이해가 가지 않는다.

제출해도 틀렸다가 나온다. 
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
using namespace std;

string s;
string b[501];
vector<int> pi;
vector<vector<int>> ret;
int cache[100010];

//cache[pos]는 긴 문자열의 pos번째 부터 붙여넣을 수 있는 최대 횟수
int solve(int pos) {
	if (pos == s.length())
		return 0;
	int& ans = cache[pos];
	if (ans != -1)return ans;

	ans = solve(pos + 1);
	for (int i = 0; i < ret[pos].size(); ++i) {
		ans = max(ret[pos][i] - pos + 1 + solve(ret[pos][i] + 1), ans);
	}
	return ans;
}

void getpi(int x) {
	pi.clear();
	pi.resize(b[x].length());
	int matched = 0;
	for (int i = 1; i < b[x].length(); ++i) {
		while (matched > 0 && b[x][i] != b[x][matched])
			matched = pi[matched - 1];
		if (b[x][i] == b[x][matched])
			pi[i] = ++matched;
	}
}

void kmp(int x) {
	int matched = 0;
	for (int i = 0; i < s.length(); ++i) {
		while (matched > 0 && s[i] != b[x][matched])
			matched = pi[matched - 1];
		if (s[i] == b[x][matched]) {
			if (i == b[x].length() - 1) {
				ret[i - b[x].length() + 1].push_back(i);
				matched = pi[matched];
			}
			else
				++matched;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	memset(cache, -1, sizeof(cache));
	cin >> s;
	ret.resize(s.length() + 1);
	int n;
	cin >> n;

	for (int i = 0; i < n; ++i)
		cin >> b[i];

	for (int i = 0; i < n; ++i) {
		getpi(i);
		kmp(i);
	}
	cout << solve(0);
	return 0;
}



//////////////////////////////////////////////////
#include <bits/stdc++.h>
#define rep(i,n) for(int i=0;i<n;++i)
#define REP(i,n) for(int i=1;i<=n;++i)
#define FAST cin.tie(NULL);cout.tie(NULL); ios::sync_with_stdio(false)
using namespace std;


string S, W;
bitset<100005> can_use[505];
int N, s;
int fail[10001], len[10001], cache[100001];

int solve(int idx) {
	if (idx == s) return 0;
	int& ret = cache[idx];
	if (ret != -1) return ret;
	ret = solve(idx + 1);
	rep(i, N) {
		if (can_use[i][idx]) ret = max(ret, len[i] + solve(idx + len[i]));
	}
	return ret;
}

int main() {
	FAST;

	memset(cache, -1, sizeof(cache));
	cin >> S >> N;
	s = S.size();

	rep(k, N) {
		cin >> W;
		memset(fail, 0, sizeof(fail));

		int w = W.size();
		len[k] = w;

		for (int i = 1, j = 0; i < w; ++i) {
			while (j && W[i] != W[j]) j = fail[j - 1];
			if (W[i] == W[j]) fail[i] = ++j;
		}

		for (int i = 0, j = 0; i < s; ++i) {
			while (j && S[i] != W[j]) j = fail[j - 1];
			if (S[i] == W[j]) {
				if (j == w - 1) {
					can_use[k][i - j] = true;
					j = fail[j];
				}
				else ++j;
			}
		}
	}
	cout << solve(0);
	return 0;
}