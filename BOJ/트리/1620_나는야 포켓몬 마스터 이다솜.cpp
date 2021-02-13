/*
map 두개를 써서 string 기준, int 기준으로 만든 뒤 각각 출력했다.
map이 메모리롤 많이 먹는다고 알고 있는데 만약 메모리가 적었다면 
메모리초과를 받을 수도 있겠다 생각했다.

다른사람의 풀이를 보니 map 하나로만 저장하고
들어온 순서대로 string을 정렬해 int형이 들어올때는 정렬된 순으로 출력했다.
*/

#include <iostream>
#include <map>
#include <string>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m;
	cin >> n >> m;

	map<string, int> pocketmon;
	map<int, string> match;
	for (int i = 1; i <= n; ++i) {
		string s;
		cin >> s;
		pocketmon[s] = i;
		match[i] = s;
	}

	for (int i = 0; i < m; ++i) {
		string s;
		cin >> s;
		if ('0' <= s[0] && s[0] <= '9')
			cout << match[stoi(s)] << "\n";
		else
			cout << pocketmon[s] << "\n";
	}
	return 0;
}


////////////////////////////////////////////////////
#include <iostream>
#include <string>
#include <cstdio>
#include <map>
#include <cstdlib>

using namespace std;

int n; //포켓몬의 수
int m; //입력받을 문제의 수

char str[21];   //포켓몬 이름

map<string, int> mp1;   //문자열 기준으로 정렬
string mp2[100001];     //번호 기준으로 정렬

void input() {
	cin >> n;
	cin >> m;

	for (int i = 0; i < n; i++) {
		scanf("%s", str);
		string s = str;

		mp1.insert(pair<string, int>(s, i));
		mp2[i] = s;
	}
}


void solution() {

	for (int i = 0; i < m; i++) {
		scanf("%s", str);

		if (isdigit(str[0])) {
			cout << mp2[atoi(str) - 1] << "\n";
		}
		else {

			string s = str;
			printf("%d\n", mp1[s] + 1);
		}

	}
}


int main(void) {
	input();
	solution();
	return 0;
}