//첫 t글자로 묶인 그룹 정보를 이용해 첫 2t글자를 비교하는 비교자의 구현
//각 접미사들의 첫 t글자를 기준으로 한 그룹 번호가 주어질 때,
//주어진 두 접미사를 첫 2*t글자를 기준으로 비교한다.
//group[]은 길이가 0인 접미사도 포함한다.
struct Comparator {
	const vector<int>& group;
	int t;
	Comparator(const vector<int>& _group, int _t) :group(_group),
		t(_t) {
		group = _group, t = _t;
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

//LCP 및 서로 다른 부분 문자열 개수 구하는 법
//O(n^2)의 시간이 걸려 밑의 LCPArray를 사용하는 것이 좋다.
//s[i..]와 s[j..]의 공통 접두사의 최대 길이를 계산한다.
int commonPrefix(const string& s, int i, int j) {
	int k = 0;
	while (i < s.size() && j < s.size() && s[i] == s[j]) {
		++i; ++j; ++k;
	}
	return k;
}
//s의 서로 다른 부분 문자열의 수를 센다.
int countSubstrings(const string& s) {
	vector<int> a = getSuffixArray(s);
	int ret = 0;
	int n = s.size();
	for (int i = 0; i < a.size(); ++i) {
		int cp = 0;
		if (i > 0)cp = commonPrefix(s, a[i - 1], a[i]);
		//a[i]의 (n-a[i])개의 접두사들 중에서 cp개는 중복이다.
		ret += n - a[i] - cp;
	}
	return ret;
}

//LCP 계산 방법
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
