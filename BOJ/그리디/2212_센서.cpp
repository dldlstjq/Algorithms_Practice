/*
문제 자체가 이해가 잘 안되는 문제였다.
질문 검색을 통해 문제를 이해했고 마땅한 풀이방법이 생각나지 않아
답을 찾아볼 수 밖에 없었다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, k;
int sensor[10001];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	cin >> k;
	for (int i = 0; i < n; ++i)
		cin >> sensor[i];

	//예외 처리
	if (k >= n) {
		cout << "0";
		return 0;
	}
	//센서 정렬
	sort(sensor, sensor + n);

	//각 거리의 차이를 구해 정렬한다.
	vector<int> diff(n - 1);
	for (int i = 0; i < n - 1; ++i)
		diff[i] = sensor[i + 1] - sensor[i];
	sort(diff.begin(), diff.end());

	//길이의 최소값을 구해야 하기때문에 가장 긴 거리를 지워야 한다.
	//k-1개 만큼 가장 긴 길이를 지울 수 있다고 보면 되기 때문에
	//지우고 남은 거리를 더하면 답이 된다.
	int ret = 0;
	for (int i = 0; i < n - k; ++i)
		ret += diff[i];

	cout << ret << "\n";
	return 0;
}