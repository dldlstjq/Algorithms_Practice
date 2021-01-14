/*
문제를 보자마 knapsack 문제가 생각났다.
백트래킹으로 물건 하나를 넣었다 빼는 방식으로 구현해야 한다.
*/

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

int N, W;
int volume[100], need[100];
string name[100];
int cache[1001][100];
int chocies[100];

//캐리어에 남은 용량이 capacity일 때, item 이후의 물건들을
//담아 얻을 수 있는 최대 절박도의 합을 반환한다.
int pack(int capacity, int item) {
	//기저 사례: 더 담을 물건이 없을 때
	if (item == N)
		return 0;
	int& ret = cache[capacity][item];
	if (ret != -1)return ret;
	//이 물건을 담지 않을 경우
	ret = pack(capacity, item + 1);
	//이 물건을 담을 경우
	if (capacity >= volume[item])
		ret = max(ret, pack(capacity - volume[item], item + 1) +
			need[item]);
	return ret;
}

//pack(capacity, item)이 선택한 물건들의 목록을 picked에 저장한다.
void reconstruct(int capacity, int item,
	vector<string>& picked) {
	//기저 사례: 모든 물건을 다 고려했음
	if (item == N)return;
	//item을 선택하지 않아도 최대 절박도 동일(즉, item 선택 안해도 된다)
	if (pack(capacity, item) == pack(capacity, item + 1)) {
		reconstruct(capacity, item + 1, picked);
	}
	else {
		picked.push_back(name[item]);
		reconstruct(capacity - volume[item], item + 1, picked);
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int c;
	cin >> c;
	while (c--) {
		memset(cache, -1, sizeof(cache));
		cin >> N >> W;
		for (int i = 0; i < N; ++i)
			cin >> name[i] >> volume[i] >> need[i];

		vector<string> picked;
		reconstruct(W, 0, picked);
		cout << pack(W, 0) << " " << picked.size() << "\n";
		for (int i = 0; i < picked.size(); ++i)
			cout << picked[i] << "\n";
	}

	return 0;
}