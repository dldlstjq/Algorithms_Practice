/*
완전탐색 답게 n의 범위인 1부터 1000000까지 전부 계산해서
생성자가 있는지 찾아본다.
자리수 합은 string으로 변환해 반복문으로 하나씩 더했다.
i가 n보다 크거나 같으면 생성자가 없기때문에 종료한다.
*/

// 2021.07.01 1부터 끝까지 다 해보면 된다. 배열을 따로 선언할 필요가 없는데 선언해서 메모리만 잡아먹었다;;
// 문자열로 바꿔 계산해도 되지만 숫자인 상태에서 모듈러와 나머지 연산을 이용하는게 더 깔끔하다.
#include <iostream> 
using namespace std;

const int MAX = 1000000 + 1;
int N;
int arr[MAX];

int calc(int num) {
	int sum = num;

	while (num > 0) {
		sum += num % 10;
		num /= 10;
	}
	return sum;
}

int main(int argc, char** argv) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> N;

	int ans = -1;

	for (int i = 1; i <= N; ++i) {
		arr[i] = calc(i);

		if (arr[i] == N) {
			ans = i;
			break;
		}

	}

	if (ans != -1)
		cout << ans;
	else
		cout << 0;

	return 0;
}


/////////////////////////////////
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;
	int ans = -1;
	for (int i = 1; i <= 1000000; ++i) {
		int sum = 0;
		string s = to_string(i);

		for (int j = 0; j < s.length(); ++j)
			sum += s[j] - '0';
		sum += i;

		//합이 n과 같으면 생성자
		if (sum == n) {
			ans = i;
			break;
		}
		//i가 n과 크거나 같으면 생성자가 없음
		else if (i >= n)
			break;
	}

	if (ans == -1)
		cout << 0;
	else
		cout << ans;

	return 0;
}