/*
와일드 카드는 다양한 운영체제에서 파일 이름의 일부만으로 파일 이름을 지정하는 방법이다.
와일드카드 패턴을 앞에서 한 글자씩 파일명과 비교해서 모든 글자가 일치했을 때
해당 와일드카드 패턴이 파일명과 대응된다고 말한다.
단, 와일드카드 패턴에 포함된 ?는 어떤 글자와도 대응된다고 가정하며,
*는 0글자 이상의 어떤 문자열에도 대응된다고 가정한다


와일드카드 패턴과 함께 파일명의 집합이 주어질 때,
그 중 패턴에 대응되는 파일명들을 찾아내는 프로그램을 작성하시오

재귀호출을 이용한 동적 계획법에 익숙해지기 위해서 많은 문제를 풀어봐야 할 것 같다.
*/


#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;


//-1은 아직 답이 계산되지 않았음을 의미한다.
//1은 해당 입력들이 서로 대응됨을 의미한다.
//0은 해당 입력들이 서로 대응되지 않음을 의미한다.
int cache[101][101];
//패턴과 문자열
string W, S;
//와일드카드 패턴 W[w..]가 문자열 S[s..]에 대응되는지 여부를 반환한다.
bool matchMemoized(int w, int s) {
	//메모이제이션
	int& ret = cache[w][s];
	if (ret != -1)
		return ret;
	//W[w]와 S[s]를 맞춰나간다.
	/*while (s < S.size() && w < W.size() &&
		(W[w] == '?' || W[w] == S[s])) {
		++w;
		++s;
	}*/
	//while을 재귀호출로 변환
	if (s < S.size() && w < W.size() &&
		(W[w] == '?' || W[w] == S[s]))
		return ret = matchMemoized(w + 1, s + 1);

	//더이상 대응할 수 없으면 왜 while문이 끝났는지 확인한다
	//2. 패턴 끝에 도달해서 끝난 경우: 문자열도 끝났어야 참
	if (w == W.size())
		return ret = (s == S.size());
	//4. *를 만나서 끝난 경우: *에 몇 글자를 대응해야 할 지 재귀호출하면서 확인한다.
	/*if (W[w] == '*')
		for (int skip = 0; skip + s <= S.size(); ++skip)
			if (matchMemoized(w + 1, s + skip))
				return ret = 1;*/
	//for문을 재귀호출로 변환
	if (W[w] == '*') {
		//*에 문자를 대응하지 않을지 아니면 한 글자 더 대응할지
		if (matchMemoized(w + 1, s) ||
			s < S.size() && matchMemoized(w, s + 1))
			return ret = 1;
	}


	//3. 이 외의 경우에는 모두 대응되지 않는다.
	return ret = 0;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;
	while (t--) {
		vector<string> v;
		cin >> W;
		int n;
		cin >> n;
		if (n < 1 || n>50)
			exit(-1);

		for (int i = 0; i < n; ++i) {
			memset(cache, -1, sizeof(cache));
			cin >> S;
			if (matchMemoized(0, 0) == 1)
				v.push_back(S);
		}
		sort(v.begin(), v.end());
		for (int i = 0; i < v.size(); ++i)
			cout << v[i] << "\n";
	}

	return 0;
}