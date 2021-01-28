/*
최소 힙을 써서 가장 작은 수 두개를 뽑아 더한 뒤 다시 큐에 넣고
원소 하나 남을때 까지 반복한다.

n=1일 때는 비교할 필요가 없기 때문에 0인 것을 처리 해야 하고
다시 큐에 넣을 때는 최소값 두 개를 더한 걸 넣어야 하는데 전체 합을 넣어 두번 틀렸다.

예제로 해볼 때 입력값이 최소, 최대일 때를 생각하고 풀어야겠다.
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	priority_queue<int, vector<int>, greater<int>> pq;

	int n;
	int ret = 0;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		int num;
		cin >> num;
		pq.push(num);
	}

	//원소 하나밖에 없으면 비교할 필요 없다.
	while (pq.size() > 1) {
		int first = 0, second = 0;
		first = pq.top();
		pq.pop();
		second = pq.top();
		pq.pop();
		ret += first + second;
		pq.push(first + second);
	}

	cout << ret;
	return 0;
}