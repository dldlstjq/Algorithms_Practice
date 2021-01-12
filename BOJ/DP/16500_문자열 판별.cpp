/*
여러가지 각도로 생각해봤는데 끝내 풀지 못했다.
A에 포함된 문자열을 한 개 이상 사용할 수 있는데 같은 단어를
여러번 사용해도 된다는 점 때문에 더 어렵게 느껴진것 같았다.
또한 S의 문자가 A의 부분문자열일 때도 가능했기 때문에 그 부분까지
생각하려니 힘들어서 풀지 못한 것 같다.

알고리즘
알고리즘은 아래와 같습니다.

1. S 문자열 idx번째 인덱스부터의 부분문자열이 A에 포함된 단어 중 하나와 일치하는지를 확인합니다.
2. 일치한다면 (idx + 부분문자열의 길이) 번째부터의 부분문자열이 또 A에 포함된 단어 중 하나와 일치하는지를 확인합니다.
3. 위 과정을 반복하다가 S 문자열의 끝까지 도달한다면 A의 단어들로 S를 공백없이 구성할 수 있기 때문에 1 즉, true를 출력해줍니다.

* 주의할 점은 S 문자열의 길이를 초과하면 안된다는 점입니다!

*/

#include <iostream>
#include <string>
#include <cstring>

using namespace std;

string S;
string A[101];
int n;
int cache[101];

bool solve(int idx) {
	//인덱스가 S의 문자열 길이와 같다면 true
	if (idx == S.length())
		return true;
	int& ret = cache[idx];
	if (ret != -1)return ret;
	ret = 0;
	for (int i = 0; i < n; ++i) {
		//A문자열이 S보다 크면 안됨
		if (S.length() < A[i].length() + idx)
			continue;
		bool flag = true;
		for (int j = 0; j < A[i].size(); ++j) {
			if (S[idx + j] != A[i][j]) {
				flag = false;
				break;
			}

		}
		if (flag)
			ret |= solve(idx + A[i].length());
	}
	return ret;

}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	memset(cache, -1, sizeof(cache));
	cin >> S;
	cin >> n;
	for (int i = 0; i < n; ++i)
		cin >> A[i];
	cout << solve(0);


	return 0;
}