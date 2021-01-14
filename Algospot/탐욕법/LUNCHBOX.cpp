/*
데우는 시간과 관련없이 먹는 데 오래 걸리는 도시락부터 데우는 것이 정답이다.
도시락을 먹는데 걸리는 시간의 역순 정렬을 위해 간단하게 부호를 뒤집어서 정렬했다.

*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX = 10000; //boxNum<=10000
int n;
int m[MAX], e[MAX];

int heat() {
	//어느 순서로 데워야 할 지를 정한다.
	vector<pair<int, int>> order;
	for (int i = 0; i < n; ++i)
		order.push_back(make_pair(-e[i], i));
	//도시락 먹는데 걸리는 시간 역순
	//즉, 오래 먹는 순서 부터
	sort(order.begin(), order.end());
	//해당 순서대로 데워먹는 과정을 시뮬레이션한다.
	int ret = 0, beginEat = 0;
	for (int i = 0; i < n; ++i) {
		int box = order[i].second;
		beginEat += m[box];
		ret = max(ret, beginEat + e[box]);
	}
	return ret;
}


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int c;
	cin >> c;
	while (c--) {
		cin >> n;
		for (int i = 0; i < n; ++i)
			cin >> m[i];
		for (int i = 0; i < n; ++i)
			cin >> e[i];
		cout << heat() << "\n";
	}

	return 0;
}