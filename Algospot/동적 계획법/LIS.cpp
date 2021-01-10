/*
처음 문제를 보고는 백준사이트에서 비슷한 문제를 풀어본 것 같았다.
찾아보니 똑같은 문제였고 그 때 풀이를 적용해서 정답을 맞았다.

책을 보니 2중FOR문으로 푼 문제를 재귀를 통해 구현했고 
O(nlgn)이 걸리는 더 빠른 해법도 존재했다.
*/

#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

int n;	//순열 길이
int arr[501];	//원래 주어진 순열
int cache[501];

//lis4를 위한 변수
int idx;	//최대 부분 수열의 길이
int C[501];

//최대 증가 부분 수열 문제 완전탐색 알고리즘
int lis(const vector<int>& A) {
	//기저 사례: A가 텅 비어 있을 때
	if (A.empty())
		return 0;
	int ret = 0;
	for (int i = 0; i < A.size(); ++i) {
		vector<int> B;
		for (int j = i + 1; j < A.size(); ++j)
			if (A[i] < A[j])
				B.push_back(A[j]);
		ret = max(ret, 1 + lis(B));
	}
	return ret;
}

//최대 증가 부분 수열 문제 동적 계획법 알고리즘1
int lis2(int start) {
	int& ret = cache[start];
	if (ret != -1)
		return ret;
	//항상 arr[start]는 있기 때문에 길이는 최하 1
	ret = 1;
	for (int next = start + 1; next < n; ++next)
		if (arr[start] < arr[next])
			ret = max(ret, lis2(next) + 1);
	return ret;
}

//최대 증가 부분 수열 문제 동적 계획법 알고리즘2
int lis3(int start) {
	int& ret = cache[start + 1];
	if (ret != -1)
		return ret;
	//항상 arr[start]는 있기 때문에 길이는 최하 1
	ret = 1;
	for (int next = start + 1; next < n; ++next)
		if (start == -1 || arr[start] < arr[next])
			ret = max(ret, lis3(next) + 1);
	return ret;
}


//동적 계획법 2를 재귀호출이 아닌 2중 for문으로 구현
/*cin >> n;
		for (int i = 0; i < n; ++i)
			cin >> arr[i];

		memset(cache, -1, sizeof(cache));
		int ret = -1;
		for (int i = 0; i < n; i++) {
			cache[i] = 1;

			for (int j = 0; j < i; j++) {
				if (arr[j] < arr[i]) {
					cache[i] = max(cache[i], cache[j] + 1);
				}
			}
			ret = max(ret, cache[i]);
		}

		cout << ret << "\n";*/

		//O(nlogn)에 lis를 찾을 수 있는 알고리즘
void lis4(int num) {
	//해당 숫자가 더 크거나 벡터가 비어있다면
	if (idx == 0 || (idx > 0 && C[idx - 1] <= num)) {
		C[idx++] = num;
		return;
	}
	//증가 부분 순열에 성립하지 않은 숫자라면 삽입할 위치를 찾는다.
	int front = 0;
	int rear = idx - 1;

	//이진 탐색
	while (front <= rear) {
		int mid = (front + rear) / 2;
		if (C[mid] < num)
			front = mid + 1;
		else
			rear = mid - 1;
	}
	C[rear + 1] = num;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;
	while (t--) {
		idx = 0;
		cin >> n;
		for (int i = 0; i < n; ++i)
			cin >> arr[i];

		memset(cache, -1, sizeof(cache));

		for (int i = 0; i < n; ++i)
			lis4(arr[i]);
		cout << idx << "\n";
		//cout << lis3(-1)-1 << "\n";
		/*cout << lis2(0) << "\n";*/

	}

	return 0;
}