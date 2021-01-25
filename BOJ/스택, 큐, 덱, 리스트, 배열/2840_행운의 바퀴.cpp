/*
예외처리에 신경을 많이 써야 한다.
우선 인덱스 움직이는 걸 조금 복잡하게 구현했었고 예외처리도 다소 복잡했다.
그래서 다른 사람의 코드를 찾아봐서 인덱스 조절을 더 간단하게 바꿨고
중복을 제일 먼저 검사한 다음 중복인 경우 같은 자리에 같은 문자면 상관없지만
그 자리에 다른 문자가 있으면 실패인 것으로 했다.
중복이 아닌 경우 비어있으면 문자를 넣고 다른 문자가 있으면 실패로 처리했다.
*/

#include <iostream>
using namespace std;

int n, k;
char wheel[27];
bool visited[26];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> k;

	for (int i = 0; i < n; ++i)
		wheel[i] = '?';

	int mark = 0;	//화살표
	while (k--) {
		int s;
		char word;

		cin >> s >> word;

		//화살표 이동
		s %= n;
		if (mark - s < 0)
			mark = (mark - s) + n;
		else
			mark -= s;

		//중복 확인.
		if (!visited[word - 'A']) {
			//칸이 비었을 때
			if (wheel[mark] == '?') {
				wheel[mark] = word;
				visited[word - 'A'] = true;
			}

			//이미 같은 글자가 있으면 상관 없음
			else if (wheel[mark] != '?' && wheel[mark] == word) {
				continue;
			}

			//해당 칸에 다른 글자가 이미 있으면 실패
			else if (wheel[mark] != '?' && wheel[mark] != word) {
				cout << "!";
				return 0;
			}
		}
		//중복 문자일때 같은 위치에 같은 문자가 아니라면 실패
		else {
			if (wheel[mark] != word) {
				cout << "!";
				return 0;
			}
		}
	}
	//출력
	for (int i = 0; i < n; ++i)
		cout << wheel[(i + mark) % n];
	return 0;
}