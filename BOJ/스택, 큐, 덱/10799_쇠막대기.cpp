//스택 활용해서 풀면 됨.
//왼쪽 괄호 다음 오른쪽 괄호인가 아닌가 따라 push, pop 해서 쇠막대기 카운트

#include <iostream>
#include <string>
#include <algorithm>
#include <stack>


using namespace std;

int iron_stick(string str) {
	stack <char> s;
	int answer = 0;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == '(' && str[i + 1] == ')') {
			if (s.empty()) {
				i++;
				continue;
			}
			else {
				answer += s.size();
				i++;
			}
		}

		else if (str[i] == '(' && str[i + 1] != ')')
			s.push(str[i]);

		else if (str[i] == ')') {
			answer++;
			s.pop();
		}
	}
	return answer;
}


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	string str;
	cin >> str;

	cout << iron_stick(str);

	return 0;
}