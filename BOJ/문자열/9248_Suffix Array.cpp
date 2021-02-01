/*
Suffix Array의 시간 복잡도는 O(nlgn)의 크기로 시간내에 가능하지만 LCP를 책에 있는 코드를 이용해서
구현하니 O(n^2)의 시간이 걸려 시간초과를 받았다.

다른 사람 코드를 참고하여 시간초과를 해결했다.
이를 해결하기 위해서 생각을 해보았는데, KMP의 알고리즘을 생각해보면, 
반복되는 계산을 줄이기 위해 pi라는 배열을 만들어 필요 없는 부분을 뛰어 넘어가는 구현을 하는 것을 보았었다.
이를 비슷하게 활용하면 되지 않을까? 라는 생각으로 나아갔다.

결과적으로 이러한 논리가 성립하였는데, LCP Array의 계산은 가장 긴 문자열부터 시작을 하는 것이었다.

suffixArray에 담긴 가장 긴 문자열(size = N)과 그 아래 문자열(길이는 랜덤)을 비교한다. 그리고 일치한 문자열의 길이가 k(k는 0이 아닌 정수)라 가정하자.
그 다음으로 긴 문자열(size = N-1)과 그 아래 문자열을 비교할 때, 그 길이는 최소 k-1가 되는 것을 보일 수 있었다.

뭐 이게 성립하는 이유는 suffixArray가 사전순으로 정렬이 되어있고, 자신의 아래에 있는 문자열은 자신과 첫 글자가 일치하는 부분이 없거나, 자신보다 더 긴 경우 2가지로 나뉘어진다.
문제에 banana예시를 생각해보면,
a
ana
anana
banana
na
nana

뭐, 이런식으로 ana에서는 3, na에서는 2, a에서는 1이 ACP Array에 담기게 된다
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int pos[500001];

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

	string s;
	cin >> s;

	vector<int> suffix = getSuffixArray(s);
	vector<int> lcp = LCPArray(s, suffix);

	int N = s.size();
	//인덱스 0부터 시작했기 때문에 1을 더해서 정답과 맞춰줌
	for (int i = 0; i < N; ++i)
		cout << suffix[i] + 1 << " ";

	cout << "\nx ";
	for (int i = 0; i < N - 1; ++i)
		cout << lcp[i] << " ";
	return 0;
}


////////////////////////////////////////////
//이렇게 해도 답은 나오지만 O(n^2)의 시간이 걸려 이 문제에서는 시간초과를 받는다.

//s[i..]와 s[j..]의 공통 접두사의 최대 길이를 계산한다.
int commonPrefix(const string& s, int i, int j) {
	int k = 0;
	while (i < s.size() && j < s.size() && s[i] == s[j]) {
		++i; ++j; ++k;
	}
	return k;
}

//s의 서로 다른 부분 문자열의 수를 센다.
//메인함수에서 접미사 배열을 구했기 때문에 여기서 또 구할 필요 없이 함수 매개변수로
//접미사 배열을 넣었다.
vector<int> countSubstrings(const string& s, const vector<int>& a) {
	//vector<int> a = getSuffixArray(s);
	vector<int> ret;
	int n = s.size();
	for (int i = 0; i < a.size(); ++i) {
		int cp = 0;
		if (i > 0)cp = commonPrefix(s, a[i - 1], a[i]);
		//중복되는 접두사의 길이를 저장한다.
		ret.push_back(cp);
	}
	return ret;
}