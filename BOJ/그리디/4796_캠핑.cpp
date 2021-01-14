/*
사용할 수 있는 날인 L일을 고려해야 하는데 P일로 조건을 짜다가 틀렸다.
휴가기간 V가 L일보다 크면 L일만큼 머물 수 있고 작으면 남은 날만큼 머물 수 있다.
구글링 해보니 공식에 따라 한줄만 쳐도 바로 답을 구할 수 있었다.
*/

#include <iostream>
using namespace std;

int p, l, v;

//처음 생각난 풀이
int solve() {
	int ret = 0;
	//휴가 기간이 다 될때까지 반복
	while (v > 0) {
		//휴가기간이 머물 수 있는 날보다 많은 경우
		if (v > l) {
			//l일만큼 머물 수 있고 휴가기간에서 p일만큼 빼준다.
			v -= p;
			ret += l;
		}
		//반대 경우 남은 휴가일만큼 머물 수 있다.
		else {
			ret += v;
			v -= l;
		}

	}
	return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	for (int i = 1;; ++i) {
		cin >> l >> p >> v;
		if (p == 0 && l == 0 && v == 0)
			break;
		cout << "Case " << i << ": " << solve() << "\n";
	}
	return 0;
}


/*
연속하는 P일 중 L일만 사용 가능하므로 아래와 같은 두 가지 경우를 생각해봐야합니다.

1. V를 P로 나누었을 때 몫 (V/P * L)
2. V를 P로 나누었을 때 나머지
2.1 V%P가 L 이하인 경우 (V%P)
2.2 V%P가 L보다 큰 경우 (L)
*/
#include <iostream> 
using namespace std;

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	for (int t = 1; ; t++) {
		int L, P, V;
		cin >> L >> P >> V;
		if (L == 0) {
			break;

			cout << "Case " << t << ": " << V / P * L + (V % P <= L ? V % P : L) << "\n";
		}
		return 0;
	}
