#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <queue>

using namespace std;

int n;
//두 기지 사이의 거리를 미리 계산해둔다.
double dist[101][101];
//거리 d 이하인 기지들만 연결했을 때 모든 기지가 연결되는지 여부를 반환한다.
bool decision(double d) {
	vector<bool> visited(n, false);
	visited[0] = true;
	queue<int> q;
	q.push(0);
	int seen = 0;
	while (!q.empty()) {
		int here = q.front();
		q.pop();
		++seen;
		for (int there = 0; there < n; ++there)
			if (!visited[there] && dist[here][there] <= d) {
				visited[there] = true;
				q.push(there);
			}
	}
	return seen == n;
}
//모든 기지를 연결할 수 있는 최소의 d를 반환한다.
double optimize() {
	double lo = 0, hi = 1416.00;	//1000√2 ~= 14145...
	for (int it = 0; it < 100; +it) {
		double mid = (lo + hi) / 2;
		//mid가 가능하다면, 더 좋은(작은) 답을 찾는다.
		if (decision(mid))
			hi = mid;
		//mid가 불가능하다면 더 나쁜(큰) 답을 찾는다.
		else
			lo = mid;
	}
	return hi;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int c;
	cin >> c;
	while (c--) {
		cin >> n;
		vector<pair<double, double>> coord;
		for (int i = 0; i < n; ++i) {
			double y, x;
			cin >> y >> x;
			coord.push_back({ y,x });
		}

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				pair<double, double> point1 = coord[i];
				pair<double, double> point2 = coord[j];
				//거리 구하기 공식
				dist[i][j] = sqrt((point2.first - point1.first) * (point2.first - point1.first)
					+ (point2.second - point1.second) * (point2.second - point1.second));
			}
		}
		cout << fixed << setprecision(2);
		cout << optimize() << "\n";
	}

	return 0;
}