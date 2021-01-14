/*
제일 작은 원소 두개를 골라 더하고 그걸 다시 큐에 넣어 반복한다.
큐의 원소가 하나밖에 없으면 그때 반복이 종료된다.

탐욕법에서는 최소, 최대값을 뽑아내는 경우가 많아 보이는데
그때 유용한 stl함수를 잘 익혀놔야겠다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int concat(const vector<int>& s) {
	priority_queue<int, vector<int>, greater<int>> pq;
	for (int i = 0; i < s.size(); ++i)
		pq.push(s[i]);
	int ret = 0;
	//원소가 하나 이상 남은 동안 반복한다.
	while (pq.size() > 1) {
		//가장 짧은 문자열 두 개를 찾아서 합치고 큐에 넣는다.
		int a = pq.top(); pq.pop();
		int b = pq.top(); pq.pop();
		pq.push(a + b);
		ret += a + b;
	}
	return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int c;
	cin >> c;
	while (c--) {
		int n;
		cin >> n;
		vector<int> s;
		for (int i = 0; i < n; ++i) {
			int tmp;
			cin >> tmp;
			s.push_back(tmp);
		}
		cout << concat(s) << "\n";
	}

	return 0;
}