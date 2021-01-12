/*
상담기간이 n일을 넘을때의 경우를 고려하다 결국 틀렸다.
재귀함수 방식을 푼 코드를 찾았는데 

i일 부터 일을 할 때 얻을 수 있는 급여의 최댓값으로 DP테이블을 잡으면 쉽게 계산할 수 있는 문제이다.
dp[i]의 점화식은 max(dp[i+1],dp[i+t[i])+p[i]) 가 된다.

*/

#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

int n;
int time[16], price[16];
int cache[16];
int func(int pos) {
	if (pos == n + 1)
		return 0;
	if (pos > n + 1)
		return -987654321;
	int& ret = cache[pos];
	if (ret != -1)return ret;
	//해당 날짜에 일 할때와 안할때 중 최대를 반환한다.
	return ret = max(func(pos + 1), func(pos + time[pos]) + price[pos]);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	memset(cache, -1, sizeof(cache));
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> time[i] >> price[i];
	cout << func(1);

	return 0;
}



//틀린풀이
//t날짜 만큼 일해서 얻을 수 있는 최대 이익.
//idx는 날짜. 1일부터 시작
int profit(int t, int idx) {
	//기저 사례: 날짜가 다 되면 0 리턴
	if (t == 0)
		return 0;
	int& ret = cache[idx];
	if (ret != -1)return ret;
	ret = 0;

	int day = idx;
	//idx일 부터 n일까지 상담여부 확인
	for (int i = idx; i <= n; ++i) {
		//핵심 포인트!
		//현재 남아있는 일 수 t가 해당 상담기간 보다 크거나 같고
		//해당 날짜와 상담기간-1을 더한게 n일을 넘어가지 않으면 상담 가능
		//상담기간-1을 하는 이유는 해당 날짜에 상담을 시작하기 때문!!
		//n=7일때 i가 6이고 해당 날짜에 상담기간이 2라면 6,7일 상담이 가능하기 때문에
		//i+(time[i]-1)을 해줘야 한다. i+time[i]를 하면 8이 되어 7일을 넘어가기 때문에
		//상담을 할 수 없는 상태가 된다.
		if (time[i] <= t && i + (time[i] - 1) <= n) {
			day += time[i];
			ret = max(ret, profit(t - time[i], day) + price[i]);

		}
	}


	return ret;
}