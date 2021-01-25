/*
1406_에디터에서 스택풀이를 따라하려다 시간이 오래 걸렸다.
에디터 문제에서 스택에 미리 문자를 삽입한 상태에서 시작한 것을 보고
이 문제에서도 문자열을 미리 스택에 삽입한 채로 시작하려다 많이 헤맸다.
에디터의 경우 끝에서 시작하기 때문에 스택에 미리 넣어도 상관없었지만
여기서는 문자열 맨 처음에서 시작하기 때문에 스택에 넣으면 애로사항이 많았다.
따라서 문자열 처음부터 반복해서 조건에 맞게 스택에 넣고 빼면 된다.

알고리즘
1. 결과를 저장하는 result와 화살표 입력시 필요한 temp 스택을 각각 정의합니다.
2. 왼쪽 화살표를 입력하는 경우 result의 top에 있는 문자를 temp에 push하고 result에서 pop합니다.
3. 오른쪽 화살표를 입력하는 경우 temp의 top에 있는 문자를 result에 push하고 temp에서 pop합니다.
4. 백스페이스를 하는 경우 단순히 result에서 한번 pop합니다.
5. 2, 3, 4번 외에는 단순히 result에 push 합니다.
6. 반복문을 탈출했을 때, temp에 여전히 문자들이 남아있을 수 있습니다. 따라서 temp에 있는 문자들을 전부 result에 push합니다.
7. stack은 LIFO(Last In First Out) 구조이기 때문에 거꾸로 출력을 해줘야합니다!
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <stack>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;
	while (t--) {
		string s;
		stack<char> ret;	//결과 저장
		stack<char> tmp;	//화살표 임시 저장

		cin >> s;
		for (int i = 0; i < s.length(); ++i) {
			//백스페이스면 ret에서 한개 삭제
			if (s[i] == '-') {
				if (!ret.empty())
					ret.pop();
			}
			//왼쪽 이동이면 tmp에 있는 문자를 ret으로 이동
			else if (s[i] == '<') {
				if (!ret.empty()) {
					tmp.push(ret.top());
					ret.pop();
				}
			}
			//오른쪽 이동이면 ret에 있는 문자를 tmp으로 이동
			else if (s[i] == '>') {
				if (!tmp.empty()) {
					ret.push(tmp.top());
					tmp.pop();
				}
			}
			else {
				ret.push(s[i]);
			}
		}

		//tmp에 있는걸 ret으로 모두 이동
		while (!tmp.empty()) {
			ret.push(tmp.top());
			tmp.pop();
		}
		//스택에 저장된 ret을 거꾸로 출력
		string ans;
		while (!ret.empty()) {
			ans += ret.top();
			ret.pop();
		}
		reverse(ans.begin(), ans.end());
		cout << ans << "\n";
	}
	return 0;
}