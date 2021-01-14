/*
기하문제를 많이 접해보지 않은 상태여서 어려울 것 같았는데 진짜 어렵다.
일단 활꼴을 구하는 부분에서 아크탄젠트와 아크사인을 알아야한다.
여기까지는 알아냈다 쳐도 그걸 구현하는 과정에서 arctan, arcsin등의 함수를
알아야하고 구간으로 바꾼 후 다시 선분으로 변환해서 탐욕법을 적용해야 한다.
만약 시험에서 이런 문제를 접한다면 다른 문제에 시간을 더 활용하는게 좋을 거
같다는 생각이 든다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

const int INF = 987654231;
const double pi = 2.0 * acos(0);	//cos(π/2)=0 -> 따라서 아크코사인(0)=π/2
int n;
double y[100], x[100], r[100];	//y 좌표, x 좌표, 경계 반지름
pair<double, double> ranges[100]; //활꼴의 시작과 끝 지점. 각 원이 덮는 중심각의 구간

int solveLinear(double, double); //미리 선언


//초소 반경들을 미나스아노르의 구간(활꼴)으로 바꾸기
void convertToRange() {
	for (int i = 0; i < n; ++i) {
		//tan(loc)=y[i]/x[i] -> arctan(y[i]/x[i]) = loc
		double loc = fmod(2 * pi + atan2(y[i], x[i]), 2 * pi);
		//sin(θ)=(r[i]/2.0)/8.0 이므로 θ를 구하기 위해선 arcsin
		double range = 2.0 * asin(r[i] / 2.0 / 8.0);
		//loc-range, loc+range는 [0, 2π] 범위 초과할 수 있음
		ranges[i] = make_pair(loc - range, loc + range);
	}
	//각 구간을 시작 위치가 작은 것부터 오게끔 정렬한다.
	sort(ranges, ranges + n);
}

//ranges[i]의 범위가 [0, 2π] 범위 초과할 수 있으므로 다음 조건을 확인해야됨
//0을 덮는 구간이 하나만 포함된다면 최적해
//두개 이상 포함될 경우
//1. 두 구간의 중심 사이에 0이 있을 경우 어느 구간을 선택해도 됨
//2. 두 구간의 중심 사이에 0이 없을 경우 0과 더 가까운 쪽 선택
//0을 덮을 구간을 선택하고 나머지를 선형으로 푼다.
int solveCircular() {
	int ret = INF;
	//각 구간을 시작 위치의 오름차순으로 정렬한다.
	sort(ranges, ranges + n);
	//0을 덮을 구간을 선택하자.
	for (int i = 0; i < n; ++i)
		if (ranges[i].first <= 0 || ranges[i].second >= 2 * pi) {
			//이 구간이 덮는 부분을 뺴고 남는 중심각의 범위는 다음과 같다.
			double begin = fmod(ranges[i].second, 2 * pi);
			double end = fmod(ranges[i].first + 2 * pi, 2 * pi);
			//[begin,end]선분을 주어진 구간을 사용해서 덮는다.
			ret = min(ret, 1 + solveLinear(begin, end));
		}
	return ret;
}

//[begin,end] 구간을 덮기 위해 선택할 최소한의 구간 수를 반환한다.
//ranges는 시작 위치의 오름차순으로 정렬되어 있다고 가정하자.
int solveLinear(double begin, double end) {
	int used = 0, idx = 0;
	//덮지 못한 선분이 남아 있는 동안 계속한다.
	while (begin < end) {
		//begin보다 이전에 시작하는 구간 중 가장 늦게 끝나는 구간을 찾는다.
		double maxCover = -1;
		while (idx < n && ranges[idx].first <= begin) {
			maxCover = max(maxCover, ranges[idx].second);
			++idx;
		}
		//덮을 구간을 찾지 못한 경우
		if (maxCover <= begin)return INF;
		//선분의 덮인 부분을 잘라낸다.
		begin = maxCover;
		++used;
	}
	return used;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int c;
	cin >> c;
	while (c--) {
		cin >> n;
		for (int i = 0; i < n; ++i)
			cin >> y[i] >> x[i] >> r[i];
		convertToRange();	//초소 반경들을 변경
		cout.precision(8);
		if (solveCircular() != INF)
			cout << solveCircular() << "\n";
		else
			cout << "IMPOSSIBLE" << "\n";
	}

	return 0;
}