/*
5076_Web Pages처럼 문자열을 파싱해야 해서 연습 겸 풀어봤다.
[] 안의 원소들을 쉼표를 기준으로 파싱해서 덱에 저장했고
R, D에 따라 명령을 수행한 후 출력했다.

제출 일지
첫번째 : 런타임 에러 (AccessEmptyContainer). 덱이 비었을 때 출력을 고려하지 않았다.

두번째 : 런타임 에러 (BufferOverflow). char배열에 저장할 때 쉼표 또한 크기에 들어간다는 것을
고려하지 않았다.

세번째: 시간초과. 처음엔 char 배열 초기화가 문제인 줄 알았는데 R명령때 reverse 함수가 시간초과가 났다.
dir이란 변수를 둬서 front, back을 구분했다.

네번째: 런타임 에러 (BufferOverflow). 또다시 두번째와 같은 문제가 났다. char 배열에 저장할때 문제가 발생한 것
같았는데 정확히 왜 에러가 났는지 원인을 몰랐다.

네번의 실패 끝에 다른 사람 코드를 참고해 파싱하지 않고 배열 변수를 0부터 돌면서 숫자를 저장하는 것으로 해결했다.

그래도 미련이 남아 질문 검색에서 런타임 에러 항목을 보던 중에 문제를 발견했다.
string을 문자로 저장하기 때문에 한자리 숫자는 한자리만 차지하지만 두자리, 세자리 숫자는 두 칸, 세 칸을 차지했다.
결국 100,000개의 숫자가 모두 100으로 들어오면 300,000개의 공간이 필요하고 
쉼표까지 고려하면 99,999가 추가 되어 최대 400,000개의 공간이 필요했다.

이를 바꿔주니 파싱함수를 이용해서 정답을 받을 수 있었다.

문자열 파싱을 연습한다고 파싱 함수를 짰는데 하나의 문자를 저장하는 데는 괜찮지만
숫자의 경우 몇 자리 수인가에 따라 저장되는 공간이 달라진다는 것을 확실하게 깨달을 수 있었다.
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <deque>
using namespace std;

//문자열 파싱 부분. 이 문제는 굳이 파싱으로 풀지 않아도 된다.
char str[400001];

deque<int> parse(string s) {
	deque<int> dq;
	//배열 원소만 골라낸다.
	int start = s.find("[");
	int end = s.find("]");
	string tmp = s.substr(1, end - start - 1);

	for (int i = 0; i < 400001; ++i)
		str[i] = 0;
	//fill(str, str + 200001, 0);
	strcpy(str, tmp.c_str());
	char* tok = strtok(str, ",");
	while (tok != nullptr) {
		dq.push_back(stoi(tok));
		tok = strtok(nullptr, ",");
	}
	return dq;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;
	while (t--) {
		string order;	//수행할 함수
		int n;	//수 개수
		string arr;	//배열
		cin >> order;
		cin >> n;
		cin >> arr;

		deque<int> dq;

		//방법1: 배열을 파싱해서 숫자만 덱에 담는다.
		deque<int> dq = parse(arr);

		//방법2: 0부터 돌면서 숫자를 덱에 담는다.
		string tmp;	//두 자릿수 이상 숫자를 위해
		//dq에 숫자만 저장
		for (int i = 0; i < arr.length(); ++i) {
			if (arr[i] == '[')
				continue;
			else if ('0' <= arr[i] && arr[i] <= '9')
				tmp += arr[i];
			else if (arr[i] == ',' || arr[i] == ']') {
				if (!tmp.empty()) {
					dq.push_back(stoi(tmp));
					tmp.clear();
				}

			}
		}

		bool error = false;
		//방향 설정. 0이면 front, 1이면 back방향
		int dir = 0;
		for (int i = 0; i < order.length(); ++i) {
			if (order[i] == 'R')
				dir = (dir == 0) ? 1 : 0;

			else if (order[i] == 'D') {
				//배열이 비었는데 D가 들어오면 에러
				if (dq.empty()) {
					error = true;
					break;
				}
				else
					(dir == 0) ? dq.pop_front() : dq.pop_back();
			}
		}

		if (error)
			cout << "error" << "\n";
		else {
			//덱이 비었을때도 생각해야 함
			if (dq.empty())
				cout << "[]" << "\n";
			else {
				//front부터 출력
				if (dir == 0) {
					cout << "[";
					int size = dq.size() - 1;
					for (int i = 0; i < size; ++i) {
						cout << dq.front() << ",";
						dq.pop_front();
					}
					cout << dq.front() << "]\n";
				}
				//back부터 출력
				else {
					cout << "[";
					int size = dq.size() - 1;
					for (int i = 0; i < size; ++i) {
						cout << dq.back() << ",";
						dq.pop_back();
					}
					cout << dq.back() << "]\n";
				}
			}
		}
	}
	return 0;
}