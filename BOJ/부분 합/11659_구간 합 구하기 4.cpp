/*
배열을 사용해서 구간합을 구할 수도 있지만 종만북에 나온 
코드를 사용하기 위해 벡터로 계산하여 풀었다.
주의할 점은 인덱스가 0으로 시작하게 할건지 1로 시작하게 할건지를
잘 설정해서 배열의 크기를 넘어가지 않게 조심해야 할 것 같다.
*/

#include <iostream>
#include <vector>

using namespace std;

int n, m;

//주어진 벡터 a의 부분합을 계산한다.
vector<int> partialSum(const vector<int>& a) {
	vector<int> ret(a.size());
	ret[1] = a[1];
	for (int i = 2; i < a.size(); ++i)
		ret[i] = ret[i - 1] + a[i];
	return ret;
}

//어떤 벡터의 부분합 psum[]이 주어질 때 원래 벡터 a부터 b까지의 합을 구한다.
int rangeSum(const vector<int>& pSum, int a, int b) {
	if (a == 1)return pSum[b];
	return pSum[b] - pSum[a - 1];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m;

	vector<int> a(n + 1, 0);
	vector<int> psum(n + 1, 0);
	for (int i = 1; i <= n; ++i)
		cin >> a[i];

	psum = partialSum(a);

	for (int i = 0; i < m; ++i) {
		int c, d;
		cin >> c >> d;
		cout << rangeSum(psum, c, d) << "\n";
	}
	return 0;
}