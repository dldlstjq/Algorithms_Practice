/*
코딩테스트를 처음 볼 때 이런 비슷한 유형의 문제를 봤었는데
어떤 알고리즘을 써야 하는지 전혀 몰랐다.
이 문제를 통해 분할정복으로 해결이 가능하다는 것을 알았고
스택을 이용해서도 선형 시간안에 해결이 가능한 것을 알았으니
알고리즘을 잘 알아둬서 언제든지 비슷한 유형이 나오면 변형해서
사용할 수 있도록 연습해놔야겠다.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//울타리 잘라내기 문제의 O(n^2) 알고리즘
//판자의 높이를 담은 배열 h[]가 주어질 때 사각형의 최대 너비를 반환한다.
int bruteForce(const vector<int>& h) {
	int ret = 0;
	int N = h.size();
	//가능한 모든 left, right 조합을 순회한다.
	for (int left = 0; left < N; ++left) {
		int minHeight = h[left];
		for (int right = left; right < N; ++right) {
			minHeight = min(minHeight, h[right]);
			ret = max(ret, (right - left + 1) * minHeight);
		}
	}
	return ret;
}

//울타리 잘라내기 분할 정복 알고리즘. O(nlgn)
//각 판자의 높이를 저장하는 배열
vector<int> h;
//h[left..right]구간에서 찾아낼 수 있는 가장 큰 사각형의 넓이를 반환한다.
int solve(int left, int right) {
	//기저 사례: 판자가 하나밖에 없는 경우
	if (left == right)
		return h[left];
	//[left, mid], [mid+1, right]의 두 구간으로 문제를 분할한다.
	int mid = (left + right) / 2;
	int ret = max(solve(left, mid), solve(mid + 1, right));
	//부분 문제3: 두 부분에 모두 걸치는 사각형 중 가장 큰 것을 찾는다.
	int lo = mid, hi = mid + 1;
	int height = min(h[lo], h[hi]);
	//[mid, mid+1]만 포함하는 너비 2인 사각형을 고려한다.
	ret = max(ret, height * 2);
	//사각형이 입력 전체를 덮을 때까지 확장을 나간다.
	while (left < lo || hi < right) {
		//항상 높이가 더 높은 쪽으로 확장한다.
		if (hi < right && (lo == left || h[lo - 1] < h[hi + 1])) {
			++hi;
			height = min(height, h[hi]);
		}
		else {
			--lo;
			height = min(height, h[lo]);
		}
		//확장한 후 사각형의 넓이
		ret = max(ret, height * (hi - lo + 1));
	}
	return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		h.resize(n, 0);
		for (int i = 0; i < n; ++i)
			cin >> h[i];
		cout << solve(0, n - 1) << "\n";
	}
	return 0;
}