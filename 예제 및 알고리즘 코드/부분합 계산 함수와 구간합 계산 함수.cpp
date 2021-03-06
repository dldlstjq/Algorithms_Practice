//부분합을 계산하는 함수와 이를 이용해 구간합을 계산하는 함수의 구현
//주어진 벡터 a의 부분합을 계산한다.
vector<int> partialSum(const vector<int>& a) {
	vector<int> ret(a.size());
	ret[0] = a[0];
	for (int i = 1; i < a.size(); ++i)
		ret[i] = ret[i - 1] + a[i];
	return ret;
}

//어떤 벡터의 부분합 psum[]이 주어질 때 원래 벡터 a부터 b까지의 합을 구한다.
int rangeSum(const vector<int>& pSum, int a, int b) {
	if (a == 0)return pSum[b];
	return pSum[b] - pSum[a - 1];
}


//배열의 부분합과 제곱의 부분합을 입력받고 특정 구간의 분산을 계산하는 함수의 구현
//A[]의 제곱의 부분 합 벡터 spqSum, A[]의 부분 합 벡터 psum이 주어질 대
//A[a..b]의 분산을 반환한다.
double variacne(const vector<int>& pqsum, const vector<int>& psum,
	int a, int b) {
	//우선 해당 구간의 평균을 계산한다.
	double mean = rangeSum(psum, a, b) / dobule(b - a + 1);
	double ret = rangeSum(psum, a, b) - 2 * mean * mean * rangeSum(psum, a, b)
		+ (b - a + 1) * mean * mean;
	return ret / (b - a + 1);
}


//2차원 배열 psum 구하기
//(1,1)이 원점이라 생각하고 구한다.
//(0,0)인 경우 0행과 0열의 예외처리를 해줘야 한다.
void make_psum() {
	int psum[101][101] = { 0 };
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j) {
			int a;
			cin >> a;
			psum[i + 1][j + 1] = psum[i + 1][j] + psum[i][j + 1] - psum[i][j] + a;
		}
}
//(0,0)부터 시작할 경우
void make_psum() {
	psum[0][0] = a[0][0];
	for (int j = 1; j < n; ++j)
		psum[0][j] = psum[0][j - 1] + a[0][j];

	for (int i = 1; i < n; ++i)
		for (int j = 0; j < n; ++j) {
			if (j == 0)
				psum[i][j] = psum[i - 1][j] + a[i][j];
			else
				psum[i][j] = psum[i - 1][j] + psum[i][j - 1] - psum[i - 1][j - 1] + a[i][j];
		}
}


//부분 합을 이용해 2차원 배열의 구간 합을 구하는 함수의 구현
//A[y1,x1]과 A[y2,x2]를 양 끝으로 갖는 부분 배열의 합을 반환한다.
int gridSum(const vector<vector<int>>& psum, int y1, int x1,
	int y2, int x2) {
	int ret = psum[y2][x2];
	if (y1 > 0)ret -= psum[y1 - 1][x2];
	if (x1 > 0)ret -= psum[y2][x1 - 1];
	if (y1 > 0 && x1 > 0)ret += psum[y1 - 1][x1 - 1];
	return ret;
}