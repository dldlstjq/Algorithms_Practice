/*
코드와 책을 통해 이해했다. 보면 볼수록 이런 코드를 생각해내는게 신기하다.
*/

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX = 2000000000 + 1;	//오버플로우 방지
int n;
int cacheLen[501], cacheCnt[501], S[501];
//Ss[start]에서 시작하는 증가 부분 수열 중 최대 길이를 반환한다.
int lis3(int start) {
	//메모이제이션
	int& ret = cacheLen[start + 1];
	if (ret != -1)return ret;
	//항상 S[start]는 있기 때문에 길이는 최하 1
	ret = 1;
	for (int next = start + 1; next < n; ++next)
		if (start == -1 || S[start] < S[next])
			ret = max(ret, lis3(next) + 1);
	return ret;
}
//S[start]에서 시작하는 최대 증가 부분 수열의 수를 반환한다.
int count(int start) {
	//기저 사례: LIS의 길이가 1인 경우
	if (lis3(start) == 1)return 1;
	//메모이제이션
	int& ret = cacheCnt[start + 1];
	if (ret != -1)return ret;
	ret = 0;
	for (int next = start + 1; next < n; ++next) {
		//처음이거나 증가부분 수열을 만족하고 next가 start 다음에 오는 숫자이니 증가부분 수열의 길이는 start에서
		//시작하는 쪽이 next에서 시작하는 쪽보다 1 길어야 한다.
		if ((start == -1 || S[start] < S[next]) &&
			lis3(start) == lis3(next) + 1)
			//오버플로우 방지 위해 임의로 64비트 숫자
			ret = min<long long>(MAX, (long long)ret + count(next));
	}
	return ret;
}

//K번째 LIS 구하기
//S[start]에서 시작하는 LIS 중 사전순으로 skip개 건너띈 수열을
//lis에 저장한다.
void reconstruct(int start, int skip, vector<int>& lis) {
	//1.S[start]는 항상 LIS에 포함된다.
	if (start != -1)
		lis.push_back(S[start]);
	//2. 뒤에 올 수 있는 숫자들과 위치의 목록을 만든다.
	//(숫자, 숫자의 위치)의 목록이 된다.
	vector<pair<int, int>> followers;
	for (int next = start + 1; next < n; ++next)
		//처음이거나 증가부분 수열을 만족하고 next가 start 다음에 오는 숫자이니 증가부분 수열의 길이는 start에서
		//시작하는 쪽이 next에서 시작하는 쪽보다 1 길어야 한다.
		if ((start == -1 || S[start] < S[next]) &&
			lis3(start) == lis3(next) + 1)
			followers.push_back(make_pair(S[next], next));
	sort(followers.begin(), followers.end());
	//3. k번째 LIS의 다음 숫자를 찾는다.
	for (int i = 0; i < followers.size(); ++i) {
		//이 숫자를 뒤에 이어서 만들 수 있는 LIS의 개수를 본다.
		int idx = followers[i].second;
		int cnt = count(idx);
		//이 숫자를 뒤에 이어서 만들 수 있는 LIS의 개수가 skip보다 작다면 skip을 줄이고 건너띈다
		if (cnt <= skip)
			skip -= cnt;
		else {
			//다음 숫자는 S[idx]임을 알았다.
			//4. 재귀 호출을 통해
			reconstruct(idx, skip, lis);
			break;
		}
	}
}
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int c;
	cin >> c;
	while (c--) {
		memset(cacheLen, -1, sizeof(cacheLen));
		memset(cacheCnt, -1, sizeof(cacheCnt));
		int K;
		cin >> n >> K;
		for (int i = 0; i < n; ++i)
			cin >> S[i];
		cout << lis3(-1) << "\n";
		vector<int> ret;
		reconstruct(-1, K - 1, ret);
		for (int i = 0; i < ret.size(); ++i)
			cout << ret[i] << " ";
		cout << "\n";

	}

	return 0;
}