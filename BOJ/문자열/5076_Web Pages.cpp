/*
스택을 활용하는 문제지만 문자열 파싱이 관건이라서 이걸 못하면 풀 수 없다.
풀이를 보고 c++에서 공백 기준으로 문자열 파싱 하는 법을 대충 알 수 있었다.
다음에 한 번 꼭 풀어볼 문제이다.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <stack>
using namespace std;


void parse(string s) {
	stack<string> st;

	int pos = 0;
	//pos가 <아닐때 까지 반복.
	//<를 찾지 못하면 string::npos를 반환한다.
	while (s.find("<", pos) != string::npos) {
		//태그 따기
		int start_pos = s.find("<", pos);
		int end_pos = s.find(">", pos);
		string tag = s.substr(start_pos + 1, end_pos - start_pos - 1);

		//공백으로 split해서 vector 집어넣음
		//<br /> 같은 형태를 확인하기 위함
		vector<string> tag_v;
		//0~255글자 까지 입력 가능하다
		char str_buff[255];
		strcpy(str_buff, tag.c_str());
		char* tok = strtok(str_buff, " ");

		while (tok != nullptr) {
			tag_v.push_back(string(tok));
			tok = strtok(nullptr, " ");
		}

		if (tag_v.back() == "/") {}	//마지막 원소가 /면 아무것도 안함
		//처음 단어가 /일 때 스택 탑에 같은 단어가 있는지 확인
		else if (tag_v[0][0] == '/') {
			if (!st.empty() && st.top() == tag_v[0].substr(1, tag_v[0].length())) {
				st.pop();
			}
			else {
				cout << "illegal" << "\n";
				return;
			}
		}
		//시작 태그일때 스택에 푸시
		else
			st.push(tag_v[0]);
		pos = end_pos + 1;
	}

	if (!st.empty())
		cout << "illegal" << "\n";
	else
		cout << "legal" << "\n";
}


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	string text;
	while (getline(cin, text)) {
		if (text == "#")
			break;
		parse(text);
	}
	return 0;
}