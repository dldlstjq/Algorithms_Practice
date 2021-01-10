/*
난이도를 구하는 코드와 동적 계획법을 구현하는 코들 나눠져 있다.
재귀호출을 이용한 동적계획법은 아직 잘 이해가 되지 않는 것 같고
난이도를 구하는 것은 특별히 어려운 것이 아닌 문제 설명대로 난이도 별로 
케이스를 나눠 구현하면 된다.
*/

#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

const int INF = 987564231;
string N;
int cache[10000];

//N[a..b] 구간의 난이도를 반환한다.
int classify(int a, int b) {
	//숫자 조각을 가져온다.
	string M = N.substr(a, b - a + 1);
	//첫 글자만으로 이루어진 문자열과 같으면 난이도는 1
	if (M == string(M.size(), M[0]))
		return 1;
	//등차수열인지 검사한다.
	bool progressive = true;
	for (int i = 0; i < M.size() - 1; ++i)
		if (M[i + 1] - M[i] != M[1] - M[0])
			progressive = false;
	//등차수열이고 공차가 1혹은 -1이면 난이도는 2
	if (progressive && abs(M[1] - M[0]) == 1)
		return 2;
	//두 수가 번갈아 등장하는지 확인한다.
	bool alternating = true;
	for (int i = 0; i < M.size(); ++i)
		if (M[i] != M[i % 2])
			alternating = false;
	if (alternating)
		return 4;	//두 수가 번갈아 등장하면 난이도는 4
	if (progressive)
		return 5;	//공차가 1이 아닌 등차수열의 난이도는 5
	return 10;		//이 외의 모두 난이도 10
}

int memorize(int begin) {
	//기저 사례: 수열의 끝에 도달했을 경우
	if (begin == N.size())
		return 0;
	int& ret = cache[begin];
	if (ret != -1)
		return ret;
	ret = INF;
	for (int i = 3; i <= 5; ++i)
		if (begin + i <= N.size())
			ret = min(ret, memorize(begin + i) +
				classify(begin, begin + i - 1));
	return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;
	while (t--) {
		memset(cache, -1, sizeof(cache));
		cin >> N;
		cout << memorize(0) << "\n";
	}

	return 0;
}