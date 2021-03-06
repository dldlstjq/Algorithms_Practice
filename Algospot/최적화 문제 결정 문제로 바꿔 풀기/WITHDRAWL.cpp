﻿#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

int n, k;
int c[1000], r[1000];
//결정문제: 누적 등수 average가 되도록 할 수 있나?
bool decision(double average) {
	//sum(c[i]/r[i]) <= x
	//sum(c[i])/sum(r[i]) <= x
	//sum(c[i]) <= x*sum(r[i])
	//0 <= x*sum(r[i])-sum(c[i])
	//0 <= sum(x*r[i]-c[i])
	//v[i]=x*r[i]-c[i]를 계산한다.
	vector<double> v;
	for (int i = 0; i < n; ++i)
		v.push_back(average * c[i] - r[i]);
	sort(v.begin(), v.end());
	//이 문제는 v중 k개의 합이 0 이상이 될 수 있는지로 바뀐다. 탐욕법으로 해결
	double sum = 0;
	for (int i = n - k; i < n; ++i)
		sum += v[i];
	return sum >= 0;
}
//최적화 문제: 얻을 수 있는 최소의 누적 등수를 계산한다.
double optimize() {
	//누적 등수는 [0,1]범위의 실수이다.
	//반복문 불변식: !decision(lo)&&decision(hi)
	double lo = -1e-9, hi = 1;
	for (int iter = 0; iter < 100; +iter) {
		double mid = (lo + hi) / 2;
		//누적 등수 mid를 달성할 수 있나?
		if (decision(mid))
			hi = mid;
		else
			lo = mid;
	}
	return hi;
}
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;
	while (t--) {
		cin >> n >> k;
		for (int i = 0; i < n; ++i)
			cin >> r[i] >> c[i];
		cout << fixed << setprecision(10);
		cout << optimize() << "\n";
	}

	return 0;
}