/*
종만북에서 한 번 접했기 때문에 문제를 쉽게 이해할 수 있었다.
다만 함수의 인자에서 가방의 현재 남은 무게와 아이템 번호를 넘겨야 하는데
무게와 가치를 넘겨서 실패했다.
또한 물건을 담았을 떄와 담지 않았을 때를 고려해야 하는데
이 또한 처음에 고려하지 않았다.

이래저래 한번 봤던 문제라도 확실히 익혀놓지 않으면 다시 풀 때
또 틀리기 마련인 것 같다.
*/

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int n, k;
int weight[100001], value[1001];
int cache[100001][1001];

//무게가 w만큼 남았을 때 item이후 아이템의 물건을 
//담아서 얻을 수 있는 최대 가치
int knapsack(int w, int item) {
	//기저 사례: 더 담을 물건이 없을 때
	if (item == n)
		return 0;
	int& ret = cache[w][item];
	if (ret != -1)return ret;
	//이 물건을 담지 않았을 때
	ret = knapsack(w, item + 1);
	//이 물건을 담을 경우
	if (w - weight[item] >= 0)
		ret = max(ret, knapsack(w - weight[item], item + 1) + value[item]);
	return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	memset(cache, -1, sizeof(cache));
	cin >> n >> k;
	for (int i = 0; i < n; ++i)
		cin >> weight[i] >> value[i];

	cout << knapsack(k, 0);

	return 0;
}