﻿/*
문제를 보자마자 그리디가 생각났다.
각 시험장에 총감독관은 1명만 있어야 하기 때문에 총감독관부터 계산해준다.
만약 총감독관으로 감시가 되면 다음으로 넘어가고 아니면 부감독관수를 세어준다.

시험장 개수가 1,000,000개이고 응시자 수 역시 1,000,000이기 때문에 결과값을 long long 으로 선언해야 한다.
처음에 부감독관 수를 구할때 응시자 수에서 C를 빼면서 반복문을 돌렸다.
그런데 시험장 개수와 응시자 수가 백만으로 최대이고 B=C=1이면 반복문이 999,999번x1,000,000번 돌아야한다.
무조건 시간초과가 날 것 같아 나눗셈과 모듈러 연산을 통해 몫과 나머지로 부감독관 수를 구했다.

돌려보니 모듈러 연산을 이용한 풀이를 통과했고 하나씩 빼는 코드는 시간초과를 받았다.
*/

#include <iostream>
using namespace std;

const int MAX = 1000000 + 1;
int N;
int A[MAX];
int B, C;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;
	for (int i = 0; i < N; ++i)
		cin >> A[i];
	cin >> B >> C;


	long long ret = 0;
	for (int i = 0; i < N; ++i) {
		//각 시험장마다 총 감독관은 1명씩 있어야한다.
		A[i] -= B;
		ret++;
		if (A[i] <= 0) {
			continue;
		}
		//부감독관은 여러명 있어도 된다.
		//몫이 0이면 부감독관 1명만 있어도 된다.
		if (A[i] / C == 0)
			ret++;
		//몫이 0이 아니면서 나누어 떨어지면 몫만큼의 부감독관 필요
		else if (A[i] / C != 0 && A[i] % C == 0)
			ret += A[i] / C;
		//나누어 떨어지지 않으면 몫+1만큼의 부감독관 필요
		else if (A[i] % C != 0)
			ret += (long long)(A[i] / C) + 1;

		//하나씩 뺀다. 시간초과 남
		/*while (A[i] > 0) {
			A[i] -= C;
			ret++;
		}*/
	}

	cout << ret;

	return 0;
}