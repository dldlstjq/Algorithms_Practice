/*
처음에 소수의 n제곱을 미리 구해놓고 a와 b사이의 수를 구하는 식으로 구현했다.
소수를 구하는 것은 10^7까지 구했지만 애초에 수 자체가 최대 10^14까지 가능하기 때문에
그 부분에서 많이 헷갈렸던 것 같다.

다른 사람의 코드를 보니 소수만 구해놓고 하나씩 곱하면서 카운트를 셌다.
핵심은 long long 범위를 벗어날 수 있기 때문에 무작정 곱하는 게 아니라
b에서 num을 나누어 b초과여부를 확인했다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

const int MAX = 10000000 + 1;
long long a, b;
bool isPrime[MAX];
vector<long long> prime;

void eratothenes() {
	memset(isPrime, 1, sizeof(isPrime));
	isPrime[0] = isPrime[1] = false;
	int sqrtn = int(sqrt(MAX));
	for (int i = 2; i <= sqrtn; ++i) {
		if (isPrime[i]) {
			for (int j = i * i; j < MAX; j += i)
				isPrime[j] = false;
		}
	}
	//소수만 따로 모은다
	for (int i = 2; i < MAX; ++i)
		if (isPrime[i])
			prime.push_back(i);
}


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> a >> b;
	eratothenes();

	long long ret = 0;

	for (int i = 0; i < prime.size(); ++i) {
		long long num = prime[i];
		//num이 long long 범위 초과하지 않도록 하는 조건
		//prime[i]*num <= b 조건인데 prime[i]*num이 long long을 초과할 수 있으므로
		//prime[i]<=b/num으로 조건을 바꿔준다.
		while (prime[i] <= b / num) {
			if (prime[i] * num >= a)
				ret++;
			num *= prime[i];
		}
	}
	cout << ret;
	return 0;
}


//////////////////////////////////////////////
//초기 작성 코드
//애초에 소수 제곱을 구하는 것 부터 틀린 것 같다.
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

const int MAX = 10000000 + 1;
long long a, b;
bool isPrime[MAX];
vector<long long> prime;

void eratothenes() {
	memset(isPrime, 1, sizeof(isPrime));
	/*for (int i = 0; i < MAX; ++i)
		prime[i] = i;*/
	isPrime[0] = isPrime[1] = false;
	int sqrtn = int(sqrt(MAX));
	for (int i = 2; i <= sqrtn; ++i) {
		if (isPrime[i]) {
			//소수가 아닌 거 먼저 제외시키고
			for (int j = i * i; j < MAX; j += i)
				isPrime[j] = false;
		}
	}

	//소수의 거듭제곱 표시
	//소수의 2제곱 이상인 것들만 따로 저장한다.
	for (int i = 2; i < MAX; i++)
		if (isPrime[i]) {
			long long tmp = (long long)i * i;
			while (tmp <= 100000000000000) {
				sosu_square.push_back(tmp);
				tmp *= i;
			}
		}
	sort(sosu_square.begin(), sosu_square.end());
}


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> a >> b;
	eratothenes();

	long long ret = 0;

	//a와 b사이에 있는 거의 소수를 센다.
	for (int i = 0; i < sosu_square.size(); ++i)
		if (a <= sosu_square[i] && sosu_square[i] <= b)
			ret++;
	cout << ret;


	return 0;
}