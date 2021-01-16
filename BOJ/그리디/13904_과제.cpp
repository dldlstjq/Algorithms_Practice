/*
점수를 최대로 하는 아이디어가 잘 생각나지 않았다.
블로그의 글을 보고 힌트를 얻어 점수가 제일 큰것 부터 시작해
최대한 마감일에 가깝게 과제를 수행하도록 하면 점수가 최대가 된다.

배열을 따로 하나 선언해 거기다 점수를 저장하면 되는데
원래 있던 배열을 사용하여 swap하는 식으로 하려다 하지 못했다.
답을 보고 나니 너무 어렵게 생각했는거 아닌가 싶었다.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
vector<pair<int, int>> order;

int solve() {
	int ret = 0;

	//가장 점수가 큰 수부터 마감일에 가깝게 넣어준다.
	//들어갈 곳이 없으면 넘어가고 이를 반복해서
	//들어간 값들을 전부 더해주면 정답
	int arr[1001] = { 0 };
	int end = 0;
	for (int i = 0; i < n; ++i) {
		end = order[i].second;
		while (end >= 1) {
			if (arr[end] == 0) {
				arr[end] = order[i].first;
				break;
			}
			else
				--end;
		}
	}
	for (int i = 1; i <= 1000; ++i)
		ret += arr[i];
	return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for (int i = 0; i < n; ++i) {
		int day, score;
		cin >> day >> score;
		order.push_back({ score,day });
	}

	sort(order.begin(), order.end(), greater<pair<int, int>>());

	cout << solve();
	return 0;
}