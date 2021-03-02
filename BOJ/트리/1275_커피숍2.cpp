/*
구간 트리를 사용하여 문제에 맞게 구현하면 된다.
합이 int형을 벗어날 수 있는 것과 x>y인 경우만 생각해주면 쉽게 풀린다.

구간 트리 구하는 함수를 종만북의 함수로 이용해도 되지만 생각이 안나는 경우
굳이 구조체로 구현하지 않고도 init, query, update 함수를 구현할 수 있다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, Q;
vector<long long>segment;

long long init(const vector<int>& array, int left, int right, int node) {
	if (left == right)
		return segment[node] = array[left];
	int mid = (left + right) / 2;
	return segment[node] = init(array, left, mid, node * 2) + init(array, mid + 1, right, node * 2 + 1);
}

long long query(int left, int right, int node, int nodeLeft, int nodeRight) {
	if (right < nodeLeft || nodeRight < left)
		return 0;
	if (left <= nodeLeft && nodeRight <= right)
		return segment[node];
	int mid = (nodeLeft + nodeRight) / 2;
	return query(left, right, node * 2, nodeLeft, mid) +
		query(left, right, node * 2 + 1, mid + 1, nodeRight);
}

long long update(int index, int newValue, int node, int nodeLeft, int nodeRight) {
	if (index < nodeLeft || nodeRight < index)
		return segment[node];
	if (nodeLeft == nodeRight)
		return segment[node] = newValue;
	int mid = (nodeLeft + nodeRight) / 2;
	return segment[node] = update(index, newValue, node * 2, nodeLeft, mid) +
		update(index, newValue, node * 2 + 1, mid + 1, nodeRight);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> Q;
	vector<int> v(N);

	for (int i = 0; i < N; ++i)
		cin >> v[i];

	segment.resize(N * 4);
	init(v, 0, N - 1, 1);

	for (int i = 0; i < Q; ++i) {
		int x, y, a, b;
		cin >> x >> y >> a >> b;
		//x>y인 경우 y번째 부터 x번째 이다.
		if (x <= y) {
			cout << query(x - 1, y - 1, 1, 0, N - 1) << "\n";
			update(a - 1, b, 1, 0, N - 1);
		}
		else {
			cout << query(y - 1, x - 1, 1, 0, N - 1) << "\n";
			update(a - 1, b, 1, 0, N - 1);
		}
	}
	return 0;
}