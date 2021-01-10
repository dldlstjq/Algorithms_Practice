/*
처음엔 구현하기 어려울 것 같았는데 조금만 생각해보면 의외로
간단하게 코드를 구현할 수 있다.

탈옥후 지난날짜와 숨어있는 마을 번호를 넘겨주고
그에 따라 함수를 만들어 가면 된다.

*/

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int n, d, p, q;
//cache[][]는 -1로 초기화해 둔다.
double cache[51][101];
//connected[i][j]=마을 i,j가 연결되어 있나 여부
//deg[i]=마을 i와 연결된 마을의 개수
int connected[51][51], deg[51];

//완전 탐색 알고리즘
//double search(vector<int>& path) {
//	//기저 사례: d일이 지난 경우
//	if (path.size() == d + 1) {
//		//이 시나리오가 q에서 끝나지 않는다면 무효
//		if (path.back() != q)
//			return 0.0;
//		//path의 출현 확률을 계산한다.
//		double ret = 1.0;
//		for (int i = 0; i + 1 < path.size(); ++i)
//			ret /= deg[path[i]];
//		return ret;
//	}
//	double ret = 0;
//	//경로의 다음 위치를 결정한다.
//	for(int there=0;there<n;++there)
//		if (connected[path.back()][there]) {
//			path.push_back(there);
//			ret += search(path);
//			path.pop_back();
//		}
//	return ret;
//}

//days일째에 here번 마을에 숨어 있다고 가정하고,
//마지막 날에 q번 마을에 숨어 있을 조건부 확률을 반환한다.
double search2(int here, int days) {
	//기저 사례: d일이 지난 경우
	if (days == d)
		return (here == q ? 1.0 : 0.0);
	//메모이제이션
	double& ret = cache[here][days];
	if (ret > -0.5)return ret;
	ret = 0.0;
	for (int there = 0; there < n; ++there)
		if (connected[here][there])
			ret += search2(there, days + 1) / deg[here];
	return ret;
}

//탈옥 후 days일 째에 두니발 박사가 here번 마을에 숨어있을 확률
double search3(int here, int days) {
	//기저 사례: 0일째
	if (days == 0)
		return (here == p ? 1.0 : 0.0);
	//메모이제이션
	double& ret = cache[here][days];
	if (ret > -0.5/*ret!=-1.0*/)return ret;
	ret = 0.0;
	//거꾸로 확률을 계산한다. 즉 해당 마을부터 시작(정방향이라면 감옥부터 시작)
	for (int there = 0; there < n; ++there)
		if (connected[here][there])	//there와 인접해 있다면
			ret += search3(there, days - 1) / deg[there];	//∑(1/adjacent(there) * search(there, days-1));
	return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int c;
	cin >> c;
	while (c--) {
		//memset(cache, -1, sizeof(cache));
		memset(deg, 0, sizeof(deg));
		cin >> n >> d >> p;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				cin >> connected[i][j];
				if (connected[i][j])
					deg[i]++;
			}
		}

		for (int i = 0; i < 50; ++i) {
			for (int j = 0; j < 100; ++j)
				cache[i][j] = -1;
		}

		int t;
		cin >> t;
		vector<int> path(t, 0);
		for (int i = 0; i < t; ++i)
			cin >> path[i];

		for (int i = 0; i < t; ++i) {
			cout << fixed;
			cout.precision(8);
			cout << search3(path[i], d) << " ";
		}
		cout << "\n";
	}

	return 0;
}