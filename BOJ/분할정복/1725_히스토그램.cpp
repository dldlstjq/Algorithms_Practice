/*
종만북에 있는 울타리 잘라내기와 같은 문제.
분할 정복으로 푸는 O(nlgn) 방식이 있고
스택을 이용한 O(n) 방식이 있다.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX = 100000 + 1;
long long arr[MAX] = { 0 };

long long solve(int left, int right) {
	//기저 사례: 원소가 하나밖에 없는 경우
	if (left == right) {
		return arr[left];
	}
	//[left,mid], [mid+1,right] 두 구간으로 분할한다.
	int mid = (left + right) / 2;
	long long ret = max(solve(left, mid), solve(mid + 1, right));

	//부분 문제3: 두 부분에 모두 걸치는 사각형 중 가장 큰 것을 찾는다.
	int lo = mid, hi = mid + 1;
	long long height = min(arr[lo], arr[hi]);
	//[lo,hi]만 고려하는 너비 2인 사각형 고려
	ret = max(ret, height * 2);

	//배열 전체를 계산할때까지 확장
	while (left < lo || hi < right) {
		//항상 높이가 더 높은 쪽으로 확장
		if (hi < right && (arr[lo - 1] < arr[hi + 1] || lo == left)) {
			++hi;
			height = min(height, arr[hi]);
		}
		else {
			--lo;
			height = min(height, arr[lo]);
		}
		ret = max(ret, (long long)(hi - lo + 1) * height);
	}
	return ret;

}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;
	for (int i = 1; i <= n; ++i)
		cin >> arr[i];

	cout << solve(1, n);

	return 0;
}