/*
kmp알고리즘에서 이 문제를 접했을때는 일치하는 부분의 인덱스와 끝나는 인덱스를 저장해서
푸는 방식으로 해결하려 했는데 실패했다.

여기서는 두 문자열을 합치되 두 문자에서 쓰이지 않는 토큰 문자를 하나($,# 등)를 넣어서 합친다.
접미사 배열과 LCP를 구한 뒤 인접한 LCP를 검사할 때, 하나의 Suffix는 A의 일부를 포함해야 하지만, 다른 하나는
A를 포함해서는 안된다는 점이다.

A와 B 두 문자열의 공통부분을 뽑아야 하는데 A나 B내에서만 문자열을 뽑을 수 있기 때문에
처리를 해줘야 한다는 것 같은데 코드는 이해가 잘 가지 않는다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int pos[200001];

struct Comparator {
	const vector<int>& group;
	int t;
	Comparator(const vector<int>& _group, int _t) : group(_group), t(_t) {
	}
	bool operator()(int a, int b) {
		//첫 t글자가 다르면 이들을 이용해 비교한다.
		if (group[a] != group[b])return group[a] < group[b];
		//아니라면 S[a+t..]와 S[b+t..]의 첫 t글자를 비교한다.
		return group[a + t] < group[b + t];
	}
};

//접미사 배열을 계산하는 맨버와 마이어스의 알고리즘
//s의 접미사 배열을 계산한다.
vector<int> getSuffixArray(const string& s) {
	int n = s.size();
	//group[i]=접미사들을 첫 t글자를 기준으로 정렬했을 때,
	//			S[i..]가 들어가는 그룹 번호.
	//t=1일 때는 정렬할 것 없이 S[i..]의 첫 글자로 그룹 번호를
	//정해 줘도 같은 효과가 있다.
	int t = 1;
	vector<int> group(n + 1);
	for (int i = 0; i < n; ++i)group[i] = s[i];
	group[n] = -1;
	//결과적으로 접미사 배열이 될 반환 값. 이 배열을 lg(n)번 정렬한다.
	vector<int> perm(n);
	for (int i = 0; i < n; ++i)perm[i] = i;
	while (t < n) {
		//group[]은 첫 t글자를 기주으로 계산해 뒀다.
		//첫 2t글자를 기준으로 perm을 다시 정렬한다.
		Comparator compareUsing2T(group, t);
		sort(perm.begin(), perm.end(), compareUsing2T);
		//2t글자가 n을 넘는다면 이제 접미사 배열 완성!
		t *= 2;
		if (t >= n)break;
		//2t글자를 기준으로 한 그룹 정보를 만든다
		vector<int> newGroup(n + 1);
		newGroup[n] = -1;
		newGroup[perm[0]] = 0;
		for (int i = 1; i < n; ++i)
			if (compareUsing2T(perm[i - 1], perm[i]))
				newGroup[perm[i]] = newGroup[perm[i - 1]] + 1;
			else
				newGroup[perm[i]] = newGroup[perm[i - 1]];
		group = newGroup;
	}
	return perm;
}

//계산의 반복을 줄이기 위해 구상을 해보자.
//접두사의 길이를 비교할 때 매번 자기 아래의 수와 비교를 하는 방법이 존재한다.
//하지만, 필요 없는 반복이 계속된다는 느낌이 든다.
//이것은 KMP에서 pi배열과 비슷하게 계산을 줄일 수 있는 방법이 존재 할 것 같다.
vector<int> LCPArray(const string& S, const vector<int>& suffixArray) {
	int N = S.size();
	vector<int> ret(N, 0);
	//길이가 긴 순서대로 비교를 할 것이다.
	//이를 위해 순서대로 자신의 위치를 표시해주는
	//pos[]배열을 만들어주었다.
	for (int i = 0; i < N; i++)
		pos[suffixArray[i]] = i;

	for (int i = 0, k = 0; i < N; i++, k = max(k - 1, 0)) {
		//suffixArray의 마지막은 비교가 불가능하다.
		if (pos[i] == N - 1) continue;

		//바로 아래의 접미사와 비교해서 몇 개의 글자가 일치하는지 비교한다.
		for (int j = suffixArray[pos[i] + 1]; S[i + k] == S[j + k]; k++);
		ret[pos[i]] = k;
	}
	return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	string A, B;
	cin >> A >> B;

	//두 문자를 합칠 때 안 쓰는 EOS(End of String) 토큰 문자를 하나 넣어주는 게 좋다.
	//보통 이럴 땐 '$'를 많이 씁니다. '#'도 예제로 자주 등장합니다. 
	//단, A, B에 등장하는 모든 알파벳보다 아스키코드가 작아야 한다(사전순으로 앞서야 한다)
	string total = A + "$" + B;
	vector<int> suffix = getSuffixArray(total);
	vector<int> lcp = LCPArray(total, suffix);

	//인접한 LCP를 검사할 때, 하나의 Suffix는 A의 일부를 포함해야 하지만, 
	//나머지 Suffix는 A를 포함해선 안된다는 점입니다
	//이 점을 유의하지 않으면 A 또는 B내에서만 LCP를 뽑아버리므로 두 문자열의 공통 부분 문자열을 얻지 못하게 된다.
	int n = total.size();
	int a = A.size();
	int ans = 0, idx = 0;
	for (int i = 0; i < n - 1; ++i) {
		if (suffix[i] < a && a < suffix[i + 1] || suffix[i + 1] < a && a < suffix[i]) {
			if (lcp[i] <= a) {
				if (ans < lcp[i]) {
					ans = lcp[i];
					idx = suffix[i];
				}
			}
		}
	}
	cout << ans << "\n";
	cout << total.substr(idx, ans);
	return 0;
}