/*
답이 자연수로 표현 가능하더라도 소수 둘째자리까지 표현하는 것이 포인트이기 때문에 iomanip 헤더파일을 추가하고
cout << fixed << setprecision(2)를 추가해주는 것이 중요
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

//결정문제: 정렬되어 있는 locations 중 cameras 선택해 모든 카메라 간의 간격이
//gap 이상이 되는 방법이 있는지를 반환한다.
bool decision(const vector<double>& location, int cameras,
	double gap) {
	//카메라를 설치할 수 있을 때마다 설치하는 탐욕적 알고리즘
	double limit = -1;
	int installed = 0;
	for (int i = 0; i < location.size(); ++i) {
		if (limit <= location[i]) {
			++installed;
			//location[i]+gap 이후는 되어야 카메라를 설치할 수 있다.
			limit = location[i] + gap;
		}
	}
	//결과적으로 camera대 이상을 설치할 수 있었으면 성공
	return installed >= cameras;
}
//최적화 문제: 정렬되어 있는 locations 중 cameras를 선택해 최소 간격을 최대화한다.
double optimize(const vector<double>& location, int cameras) {
	double lo = 0, hi = 241;
	//반복문 불변식: decision(lo)&&!decision(hi)
	for (int it = 0; it < 100; ++it) {
		double mid = (lo + hi) / 2.0;
		//간격이 mid 이상이 되도록 할 수 있으면 답은 [mid, hi]에 있다.
		if (decision(location, cameras, mid))
			lo = mid;
		//간격이 mid 이상이 되도록 할 수 없으면 답은 [lo, mid]에 있다.
		else
			hi = mid;
	}
	return lo;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int c;
	cin >> c;
	while (c--) {
		int n, m;
		cin >> n >> m;
		vector<double> loc;
		for (int i = 0; i < m; ++i) {
			double tmp;
			cin >> tmp;
			loc.push_back(tmp);
		}
		sort(loc.begin(), loc.end());
		cout << fixed << setprecision(2);
		cout << optimize(loc, n) << "\n";
	}

	return 0;
}