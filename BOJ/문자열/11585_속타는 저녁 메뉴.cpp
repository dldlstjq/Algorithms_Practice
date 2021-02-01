/*
환형문자열에서 부분문자열이 몇 번 일치하는지 구하는 문제이므로 
Algospot JAEHASAFE의 문제와 상당히 유사한 문제였다.
따라한다고 나름 따라했는데 정답이 잘 안나왔다.

우선 환형문자열은 주어진 문자열을 2배 즉, 이어 붙인 상태로 kmp알고리즘을 수행하는 것이 핵심이다.
알고스팟과 달리 몇 번 일치하는지가 중요하기때문에 kmp의 사이즈를 리턴했고
분수를 약분해야하기 때문에 유클리드 알고리즘을 이용해 두 수의 최대공약수를 구했다.

그리고 shifts 함수를 호출할 때 반시게 방향으로 탐색할 경우 매개변수로
original, target 순으로 전달하지만 시계 방향으로 탐색할 경우 그 반대인 
target, original 순으로 전달한다.

마지막으로, original=target인 경우 orignal을 두배 하였을 경우 두번 일치한다고 여긴다.
따라서 orinal을 두 배한 상태에서 마지막 인덱스를 제외하고 찾아야 정답을 맞을 수 있다.

여러모로 문자열 특히 kmp알고리즘은 알고리즘 자체도 어려운데다 문제도 어려운것 같다.
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> getpi(const string& s) {
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
	vector<int> pi = getpi(p);
	vector<int> ret;
	//현재 대응된 글자의 수
	int j = 0;
	//짚더미의 각 글자를 순회
	for (int i = 0; i < n; ++i) {
		//j번 글자와 짚더미 글자가 불일치할 경우
		//현재 대응된 글자의 수를 pi[j-1]로 줄인다.
		while (j > 0 && h[i] != p[j])
			j = pi[j - 1];
		//글자 대응될 경우
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

//환형문자열은 original 문자열을 이어붙여서 부분문자열을 찾는 방식
int shifts(const string& original, const string& target) {
	//original=target이면 doubleOriginal에서 다 찾다보면 두 번 찾게 되므로 doubleOriginal의 마지막 인덱스는 패스
	string doubleOriginal = original + original.substr(0, original.size() - 1);
	return kmp(doubleOriginal, target).size();
}

//유클리드 호제법
int gcd(int p, int q) {
	if (q == 0)return p;
	return gcd(q, p % q);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	string target, original;

	cin >> n;
	for (int i = 0; i < n; ++i) {
		char temp;
		cin >> temp;
		target += temp;
	}

	for (int i = 0; i < n; ++i) {
		char temp;
		cin >> temp;
		original += temp;
	}

	int ret = shifts(target, original);	//시계방향이므로 매개변수를 거꾸로

	//약분
	int divider = gcd(n, ret);
	cout << ret / divider << "/" << n / divider;
	return 0;
}