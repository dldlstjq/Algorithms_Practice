/*
부분합(구간합)을 합 연산에만 사용할 수 있는게 아니라
비트 연산에도 이용할 수 있다.
아무래도 중복되는 연산을 계속 사용해야 할 때 부분합 알고리즘을 사용하면
시간이 적게 든다.
*/

#include <iostream>
using namespace std;

const int MAX = 1000000 + 1;
int pxor[MAX];
int n, q;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> q;
	for (int i = 1; i <= n; ++i) {
		int a;
		cin >> a;
		pxor[i] = pxor[i - 1] ^ a;
	}

	//맨 처음 값을 ret에 넣어주고 두번째부터 반복해서 xor 계산한다.
	int s, e;
	cin >> s >> e;
	int ret = pxor[e] ^ pxor[s - 1];
	for (int i = 1; i < q; ++i) {
		cin >> s >> e;
		ret ^= pxor[e] ^ pxor[s - 1];
	}
	cout << ret;
	return 0;
}