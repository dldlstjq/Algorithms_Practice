/*
비트마스크를 사용한 동적 계획법
가격이 아닌 가격의 나머지만 전달하더라고 m의 배수 여부를 판별할수 있고
중복된 숫자를 세지 않는다는 것 주의해야한다.

제출하면 오답이 나오는데 여러번 봐야 이해할 수 있을 것 같다.
*/

#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <bitset>

using namespace std;

//웨브바짐 문제의 답을 모두 찾는 완전 탐색 알고리즘
//digits: e의 자릿수들을 정렬한 것
//string e, digits;
//int n, m;
////e의 자릿수로 만들 수 있는 숫자들을 모두 출력한다.
////price: 지금까지 만든 가격
////taken: 각 자릿수의 사용 여부
//void generate(string price, bool taken[15]) {
//	//기저 사례
//	if (price.size() == n) {
//		if (price < e)
//			cout << price << "\n";
//		return;
//	}
//	for(int i=0;i<n;++i)
//		if (!taken[i] &&
//			(i == 0 || digits[i - 1] != digits[i] || taken[i - 1])) {
//			taken[i] = true;
//			generate(price + digits[i], taken);
//			taken[i] = false;
//		}
//}

//웨브바짐 문제를 해결하는 동적 계획법 알고리즘
const int MOD = 1000000007;
//digits:e의 자릿수들을 정렬한 것
string e, digits;
int n, m;	//n은 e의 자릿수, e는 m으로 나누어 떨어져야 한다.
//자릿수가 최대 14자리이므로 1<<14, m<=20, 그리고 e보다 작은지 여부
int cache[1 << 14][20][2];
//과거 가격을 앞 자리부터 채워나가고 있다.
//index: 이번에 채울 자리의 인덱스
//taken: 지금까지 사용한 자릿수들의 집합
//mod: 지금까지 만든 가격의 m에 대한 나머지
//less: 지금까지 만든 가격이 이미 e보다 작으면 1, 아니면 0
int price(int index, int taken, int mod, int less) {
	//기저 사례
	if (index == n)
		return (less && mod == 0) ? 1 : 0;
	//메모이제이션
	int& ret = cache[taken][mod][less];
	if (ret != -1)return ret;
	ret = 0;
	for (int next = 0; next < n; ++next)
		//next번째 숫자를 사용한 적이 없다면
		if ((taken & (1 << next)) == 0) {
			//과거 가겨은 새 가격보다 항상 작아야만 한다.
			if (!less && e[index] < digits[next])
				continue;
			//같은 숫자는 한 번만 선택한다.
			//next-1번째 숫자를 이미 사용했고 연속해서 같은 숫자이면
			if (next > 0 && digits[next - 1] == digits[next] &&
				(taken & (1 << (next - 1))) == 0)
				continue;
			int nextTaken = taken | (1 << next);	//next번째 숫자를 사용했다고 표기
			//나머지가 같을 경우 앞에 어떤 수가 왔는지는 중요하지 않다. 나머지만 전달해도 계란 가격이 m의 배수인지 알 수 있다.
			int nextMod = (mod * 10 + digits[next] - '0') % m;	//다음 나머지
			int nextLess = less || e[index] > digits[next];	//작은 숫자 여부 확인
			ret += price(index + 1, nextTaken, nextMod, nextLess);
			ret %= MOD;
		}
	return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);


	int c;
	cin >> c;
	while (c--) {
		n = 0;
		vector<long long> candidate;
		memset(cache, -1, sizeof(cache));
		cin >> e >> m;
		long long num = atoll(e.c_str());
		candidate.clear();
		while (num > 0) {
			candidate.push_back(num % 10);
			num /= 10;
			n++;
		}
		sort(candidate.begin(), candidate.end());
		for (int i = 0; i < n; ++i)
			digits += candidate[i] + '0';
		cout << price(0, 0, 0, 0) << "\n";
	}

	return 0;
}