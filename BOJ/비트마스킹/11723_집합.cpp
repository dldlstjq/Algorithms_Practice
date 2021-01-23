/*
집합을 배열이 아니라 비트마스크를 이용해 표현해야 한다.
만약 배열로 표현했으면 메모리 초과를 받았을 것 같긴 하다.
*/

#include <iostream>
using namespace std;

int M;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> M;
	int S = 0;
	while (M--) {
		string str;
		int x;
		cin >> str;
		//원소 추가
		if (str == "add") {
			cin >> x;
			S |= (1 << x);
		}
		//원소 삭제
		else if (str == "remove") {
			cin >> x;
			S &= ~(1 << x);
		}
		//원소 포함 여부 확인
		else if (str == "check") {
			cin >> x;
			if (S & (1 << x))
				cout << 1 << "\n";
			else
				cout << 0 << "\n";
		}

		//토글
		else if (str == "toggle") {
			cin >> x;
			S ^= (1 << x);
		}

		//꽉 찬 집합
		//1~20이기 때문에 21만큼 옮기고 1빼줌
		else if (str == "all")
			S = (1 << 21) - 1;
		//공집합
		else if (str == "empty")
			S = 0;
	}

	return 0;
}