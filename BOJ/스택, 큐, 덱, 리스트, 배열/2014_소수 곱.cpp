/*
시간 초과를 해결하는데 애먹었다.
처음엔 1부터 2^31-1까지 반복해서 k개의 소수로 나눠지면 카운트해서
n이 되면 출력하게 했다.

설마 했는데 역시나 시간초과를 받았고 어떻게 해야 우선순위 큐를 쓰면서
풀 수 있을지 생각했는데 떠오르지 않았다.

알고리즘은 아래와 같습니다.
1. 숫자를 중복 삽입하는 것을 방지하기 위해 map을 이용합니다.
2. 소수의 곱을 우선순위 큐에 입력하는데 우선순위 큐의 크기가 N을 초과하고 우선순위 큐 내 최댓값보다 현재 숫자가 더 크면 삽입하지 않습니다.
-> 우선순위 큐 내 최댓값보다 현재 숫자가 작으면 현재 숫자가 더 먼저 등장하므로 우선순위 큐에 넣습니다.
3. 반복문을 탈출한 뒤 우선순위 큐의 top을 출력합니다.

*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <functional>
using namespace std;

const int MAX = 100;
map<long long, bool> visited;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int k, n;
	vector<long long> v;
	//최소 힙
	priority_queue<long long, vector<long long>, greater<long long>> pq;
	vector<long long> ans;

	cin >> k >> n;
	v.resize(k);
	for (int i = 0; i < k; ++i)
		cin >> v[i];

	pq.push(1);
	long long maxValue = 0;
	while (n) {
		long long cur = pq.top();
		pq.pop();

		for (int i = 0; i < k; ++i) {
			long long next = cur * v[i];
			//pq안에 있는 숫자들 중 최댓값보다 크고 pq의 크기가
			//n을 넘으면 더 이상 숫자를 넣을 필요가 없다
			if (pq.size() > n && next > maxValue)
				continue;

			//중복 삽입 방지
			if (!visited.count(next)) {
				maxValue = max(maxValue, next);
				visited[next] = true;
				pq.push(next);
			}
		}
		n--;
	}
	cout << pq.top();
	return 0;
}