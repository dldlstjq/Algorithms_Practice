/*
총 세번의 시도끝에 풀 수 있었다.
분할 정복을 이용해서 풀면 되는데 종만북에서 봤던 울타리 잘라내기 알고리즘을 사용했다.
범위를 절반으로 나눠 왼쪽, 오른쪽, 가운데 걸친 부분 모두를 구해서
제일 큰 값을 찾으면 된다.

처음에 ret을 계산할 때 이때까지 계산한 것 중 큰 값을 저장해야 하는데
단순히 min_num*sum을 저장해 틀렸다.

두번째에서는 시간초과가 났는데 i에서 j까지의 합을 구할 때
calcul이라는 함수를 만들어 for문을 돌며 합을 계산했다.
여기서 시간초과가 났다. 해결 방법은 lo, hi의 합과 최솟값을 구해놓은 후
배열을 확장해 나가면서 해당 인덱스의 값을 더하고 미리 구한 최솟값과 해당 인덱스의 값 중
최솟값을 구하면 for문을 돌지 않고도 값을 구할 수 있었다.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX = 100000 + 1;
long long arr[MAX] = { 0 };

//long long calcul(int left, int right) {
//	int min_num = 987654321;
//	int sum = 0;
//	for (int i = left; i <= right; ++i) {
//		sum += arr[i];
//		min_num = min(min_num, arr[i]);
//	}
//	return sum * min_num;
//
//}

long long solve(int left, int right) {
	//기저 사례: 원소가 하나밖에 없는 경우
	if (left == right) {
		return arr[left] * arr[left];
	}
	//[left,mid], [mid+1,right] 두 구간으로 분할한다.
	int mid = (left + right) / 2;
	long long ret = max(solve(left, mid), solve(mid + 1, right));
	int lo = mid, hi = mid + 1;

	//[lo,hi]의 합과 최솟값을 구해 저장한다.
	long long min_num = min(arr[lo], arr[hi]);
	long long sum = arr[lo] + arr[hi];

	//[lo,hi]까지 계산. 이때까지 계산한 것 중 가장 큰 값을 ret에 저장
	ret = max(ret, min_num * sum);

	//배열 전체를 계산할때까지 확장.
	//lo-1, hi+1 중 더 큰수가 있는 쪽으로 확장해서 합과 최솟값을 구한 후 최종값을 구한다.
	//i에서 j까지 반복하지 않고도 원소 하나씩 더하고 최솟값을 비교하면서 값을 구한다.
	while (left < lo || hi < right) {
		if (hi < right && (arr[lo - 1] < arr[hi + 1] || lo == left)) {
			++hi;
			sum += arr[hi];
			min_num = min(min_num, arr[hi]);
		}
		else {
			--lo;
			sum += arr[lo];
			min_num = min(min_num, arr[lo]);
		}
		ret = max(ret, sum * min_num);
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