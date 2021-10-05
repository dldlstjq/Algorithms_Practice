/*
문제를 제대로 안 읽어서 맞는 답이 안나왔다.

처음에 K번만 시계방향으로 돌리는 줄 알고 K번 시계방향을 돌리면서 진행했다.
그런데 2번째 테스트케이스에 정답이 제대로 안 나왔고 이거땜에 1시간가까이 소요됐다.

문제 어디에도 K번 돌리라는 말이 없었기 때문에 N/4만큼 돌리면서 중복된 원소를 제거하면 끝이었다.

다시 한번 문제를 제대로 잘 읽어봐야 한다.

그리고 파일 입출력을 써야 하는 줄 알았는데 단순히 테스트 확인할 떄 일일이 입력하지 말라고 해놓은 것 같다.
*/
#include<iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int N, K;
string num;

//수를 저장할 변수
vector<long long> v;

//16진수 A~F 나타내는 수 저장
int alpha[6] = { 10,11,12,13,14,15 };

void rotate() {
	//생성 가능한 수를 저장한다.
	int len = N / 4;

	for (int j = 0; j < N; j += len) {
		long long sum = 0;
		int a = len - 1;
		for (int k = j; k < j + len; ++k) {
			if ('0' <= num[k] && num[k] <= '9')
				sum += (long long)pow(16, a--) * (num[k] - '0');
			else {
				int idx = (num[k] - 'A');
				sum += (long long)pow(16, a--) * alpha[idx];
			}
		}

		//마이너스를 붙여 정렬하면 가장 큰 값이 위로 온다.
		v.push_back(-sum);
	}

	string tmp = num;
	//회전
	for (int i = 0; i < N; ++i) {
		num[(i + 1) % N] = tmp[i];
	}
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	/*
	   아래의 freopen 함수는 input.txt 를 read only 형식으로 연 후,
	   앞으로 표준 입력(키보드) 대신 input.txt 파일로부터 읽어오겠다는 의미의 코드입니다.
	   //여러분이 작성한 코드를 테스트 할 때, 편의를 위해서 input.txt에 입력을 저장한 후,
	   freopen 함수를 이용하면 이후 cin 을 수행할 때 표준 입력 대신 파일로부터 입력을 받아올 수 있습니다.
	   따라서 테스트를 수행할 때에는 아래 주석을 지우고 이 함수를 사용하셔도 좋습니다.
	   freopen 함수를 사용하기 위해서는 #include <cstdio>, 혹은 #include <stdio.h> 가 필요합니다.
	   단, 채점을 위해 코드를 제출하실 때에는 반드시 freopen 함수를 지우거나 주석 처리 하셔야 합니다.
	*/
	//freopen("input.txt", "r", stdin);
	cin >> T;
	/*
	   여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
	*/
	for (test_case = 1; test_case <= T; ++test_case)
	{
		cin >> N >> K;
		cin >> num;
		v.clear();

		//0회전
		rotate();

		//4번 돌면 원래 위치와 똑같다
		for (int i = 0; i < N / 4; ++i) {
			rotate();
		}

		//정렬 후 중복 원소 제거
		sort(v.begin(), v.end());
		v.erase(unique(v.begin(), v.end()), v.end());

		cout << '#' << test_case << " " << -v[K - 1] << "\n";

	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}