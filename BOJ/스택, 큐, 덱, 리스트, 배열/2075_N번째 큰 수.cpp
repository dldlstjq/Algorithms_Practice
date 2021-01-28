/*
pq를 최소 힙으로 하고 모든 원소를 넣었다가 메모리초과를 받았다.
pq에 모든 원소를 넣는 것이 아니라 n개의 원소만 넣고 새로운 숫자마다 top과 비교해
크면 새로 집어 넣으면 최종적으로 top에 있는 것이 n번째 큰 수가 된다.
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;

	//pq의 사이즈를 n개로 유지한다.
	//첫 행만 모두 넣고 두번째 행부터 최소원소랑 num이랑 비교한다.
	//더 크면 새로 넣고 아니면 다른 원소랑 비교한다.
	//가장 마지막에 top에 있는 것이 n번째로 큰 수
	priority_queue<int, vector<int>, greater<int>> pq;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			int num;
			cin >> num;
			if (i == 0)
				pq.push(num);
			else {
				if (num > pq.top()) {
					pq.pop();
					pq.push(num);
				}
			}
		}
	}
	cout << pq.top();
	return 0;
}