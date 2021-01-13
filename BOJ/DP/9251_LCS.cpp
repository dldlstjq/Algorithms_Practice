/*
처음 코드를 짰을 때 문자가 같은 경우에만 1을 더해줘야 하는데
다른 경우에도 1을 더해주게 해서 답이 제대로 안나왔다.
디버깅을 하다가 겨우 알아냈는데 재귀함수는 디버깅하기가 까다로워
답이 틀렸을 때 그걸 알아내는게 쉽지 않은 것 같다.

그리고 반복문을 사용해서 푸는 방법도 있는데
확실히 시간이 더 빠르게 나온다
반복문 -> 4ms
재귀   -> 12ms

종만북에서 적혀있는대로 재귀함수는 직관적으로 쉽게 이해할 수 있는데
반복문은 왜 저런 공식이 나오는지 바로 이해하기는 어려운 것 같다.
*/

#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

string s1;
string s2;
int cache[1001][1001];

//s1의 인덱스가 a, s2의 인덱스가 b일 때 LCS반환
int solve(int a, int b) {
	//기저사례: 둘 중 하나라도 문자열 끝일 경우
	if (a == s1.length() || b == s2.length())
		return 0;
	int& ret = cache[a][b];
	if (ret != -1)return ret;
	ret = 0;

	//문자열 범위 안에 있으면서
	//두 문자가 같으면 인덱스 1씩 증가
	//다르면 a,b 둘 중 하나씩 증가시킨 것중 최대가 정답
	if (a < s1.length() && b < s2.length()) {
		if (s1[a] == s2[b])
			ret = max(ret, solve(a + 1, b + 1) + 1);
		else
			//처음 여기에도 1을 더해서 답이 안 나왔다.
			ret = max(solve(a, b + 1), solve(a + 1, b));
	}
	return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	memset(cache, -1, sizeof(cache));
	cin >> s1;
	cin >> s2;

	cout << solve(0, 0);
	return 0;
}

////////////////////////////
//반복문
/*
두 문자열의 길이+1만큼의 행과 열을 갖는 이차원 배열을 선언하고 0으로 초기화시킨다. 
그리고 문자를 하나씩 비교하며 같다면 왼쪽 대각선 + 1, 다르다면 max(왼쪽, 위쪽)값을 취한다.
*/
#include <iostream>
#include <string>

using namespace std;

int dp[1001][1001];

int main() {
	string s1, s2;
	getline(cin, s1);
	getline(cin, s2);

	for (int j = 0; j < s2.length(); j++) {
		dp[0][j] = 0;
	}
	for (int i = 0; i < s1.length(); i++) {
		dp[i][0] = 0;
	}

	for (int i = 1; i <= s1.length(); i++) { // s1
		for (int j = 1; j <= s2.length(); j++) { // s2
			if (s1[i - 1] != s2[j - 1]) {
				dp[i][j] = dp[i - 1][j] > dp[i][j - 1] ? dp[i - 1][j] : dp[i][j - 1];
			}
			else {
				dp[i][j] = dp[i - 1][j - 1] + 1;
			}
		}
	}
	cout << dp[s1.length()][s2.length()];
}