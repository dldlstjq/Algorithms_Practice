/*
최대 증가 부분 수열을 실제로 계산하기
*/

#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

int n;
int cache[501], S[501], choices[501];

//S[start]에서 시작하는 증가 부분 수열 중 최대 길이를 반환한다.
int lis4(int start) {
	int& ret = cache[start + 1];
	if (ret != -1)return ret;
	//항상 S[start]는 있기 때문에 길이는 최하 1
	ret = 1;
	int bestNext = -1;
	for (int next = start + 1; next < n; ++next)
		if (start == -1 || S[start] < S[next]) {
			int cand = lis4(next) + 1;
			if (cand > ret) {
				ret = cand;
				bestNext = next;
			}
		}
	choices[start + 1] = bestNext;
	return ret;
}
//S[start]에서 시작하는 LIS를 seq에 저장한다.
void reconstruct(int start, vector<int>& seq) {
	if (start != -1)seq.push_back(S[start]);
	int next = choices[start + 1];
	if (next != -1)reconstruct(next, seq);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int c;
	cin >> c;
	while (c--) {
		memset(cache, -1, sizeof(cache));
		memset(choices, -1, sizeof(choices));
		cin >> n;
		for (int i = 0; i < n; ++i)
			cin >> S[i];

		cout << "최대 수열 길이: " << lis4(-1) - 1 << "\n";

		vector<int> seq;
		reconstruct(-1, seq);
		for (int i = 0; i < seq.size(); ++i)
			cout << seq[i] << " ";

		cout << "\n";
	}

	return 0;
}