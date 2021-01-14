/*
해당 선수를 이길 수 없으면 가장 작은 레이팅과 바꿔주고
이길 수 있으면 이길 수 있는 레이팅 중 가장 작은 수를 배치하면 된다.

아이디어는 알았는데 구현에서 막혀 해결하지 못했다.
multiset이라는 중복이 허용되는 이진트리 stl함수를 알게 됐다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int order(const vector<int>& russian,
	const vector<int>& korean) {
	int n = russian.size(), wins = 0;
	//아직 남아있는 선수들의 레이팅
	multiset<int> ratings(korean.begin(), korean.end());
	for (int rus = 0; rus < n; ++rus) {
		//가장 레이팅이 높은 한국 선수가 이길 수 없는 경우
		//가장 레이팅이 낮은 선수와 경기시킨다.
		if (*ratings.rbegin() < russian[rus])
			ratings.erase(ratings.begin());
		//이 외의 경우 이길 수 있는 선수 중 가장 레이팅이 낮은 선수와 경기시킨다.
		else {
			ratings.erase(ratings.lower_bound(russian[rus]));
			++wins;
		}
	}
	return wins;
}


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);


	int c;
	cin >> c;
	while (c--) {
		int N;
		cin >> N;
		vector<int> russia;
		vector<int> korea;
		//러시아 점수
		for (int i = 0; i < N; ++i) {
			int score;
			cin >> score;
			russia.push_back(score);
		}
		//한국 점수
		for (int i = 0; i < N; ++i) {
			int score;
			cin >> score;
			korea.push_back(score);
		}
		cout << order(russia, korea) << "\n";
	}


	return 0;
}

//처음 풀이
//각 배열을 오름착순 정렬한 다음 가장 승리 레이팅 높은 순서대로
//비교하며 이길 수 없으면 최소값이랑 바꾸려고 했는데 잘 안 됐다.
int n;
int russia[101];
int korea[101];

bool cmp(int a, int b) {
	return a > b;
}

int solve() {
	//오름차순 정렬
	sort(russia, russia + n, cmp);
	sort(korea, korea + n, cmp);

	int ret = 0;
	int i = 0;
	int min = 0;
	while (i < n) {
		min = *min_element(korea, korea + n);
		if (russia[i] <= korea[i]) {
			ret++;
			i++;
		}
		else {
			swap(korea[i], min);
			i++;
		}

	}
	return 0;
}
