/*
최적을 구하는 것에서 틀렸다.
가장 적게 사용하는 걸 빼고 넣으면 되는줄 알았는데
가장 나중에 사용하거나 이후 안쓰일 코드를 빼야했다.
*/


// 2021.06.14 풀이
/* 
1. 비어있으면 꽂는다.
2. 이미 꽂혀있으면 패스
3. 꽂을 구멍이 없으면 탭에 있는 것 중 안쓰일 제품이나 가장 나중에 사용되는 제품을 뺀다.
-> 단순히 빈도 수로 계산하면 답이 안나옴.
*/

#include <iostream> 
#include <vector> 
#include <algorithm>
using namespace std;

int N, K;
vector<int> v;

bool cmp(pair<int, int>a, pair<int, int>b) {
	return a.second > b.second;
}

int main(int argc, char** argv) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> N >> K;
	vector<pair<int, int>> tab;
	tab.resize(N);

	for (int i = 0; i < K; ++i) {
		int elec;
		cin >> elec;
		v.push_back(elec);
	}

	int ret = 0;
	for (int i = 0; i < K; ++i) {
		int cnt = 0;
		for (int j = 0; j < N; ++j) {
			// 비었으면 탭에 꽂는다.
			if (!tab[j].first) {
				tab[j].first = v[i];
				break;
			}
			// 이미 탭에 있으면 ok
			else if (tab[j].first == v[i])
				break;
			// 탭에 없으면 cnt 증가
			else if (tab[j].first != v[i])
				cnt++;
		}

		// 멀티탭이 다 사용중이다.
		// 남은 것들 중 다시 사용되는게 있는지 검사하는게 필요할듯.
		// 운체에 최적 알고리즘이랑 비슷한데 미래에 어떤게 가장 시간이 적은지 찾는게 어려워 잘 안쓰인다고 했다.
		if (cnt == N) {
			// tab의 second는 101로 초기화 한다. K가 최대 100이기 때문에 101로 만듬.
			for (int a = 0; a < N; ++a)
				tab[a].second = 101;

			// i+1부터 K까지 돌면서 이미 멀티탭에 있는 제품 중 가장 먼저 나오는 인덱스를 저장한다.
			for (int b = i + 1; b < K; ++b) {
				for (int c = 0; c < N; ++c) {
					if (tab[c].second == 101 && v[b] == tab[c].first) {
						tab[c].second = b;
						break;
					}

				}
			}

			// second 기준으로 내림차순 정렬
			// 내림차순 정렬하면 이미 꽂힌 제품 중 가장 나중에 사용되는 제품이 맨 앞에 온다.
			// 안쓰일 제품이라면 101이므로 가장 앞에 올 수 있음. 최대 사용횟수는 100
			// 그걸 뽑고 새로 꽂으면 최소횟수로 사용 가능
			sort(tab.begin(), tab.end(), cmp);
			tab[0].first = v[i];
			tab[0].second = 0;
			ret++;

		}
	}

	cout << ret;

	return 0;
}


//정답 코드
#include <iostream>

using namespace std;

int N, K;
int order[101];
int hole[101];
int result;

int main()
{
	cin.tie(0);
	ios::sync_with_stdio(false);

	cin >> N >> K;

	for (int i = 1; i <= K; i++)
	{
		cin >> order[i];
	}

	for (int i = 1; i <= K; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			// 구멍이 비어 있는 경우
			if (!hole[j])
			{
				hole[j] = order[i];
				break;
			}
			else
			{
				// 이미 사용중이면 넘어간다
				if (order[i] == hole[j])
				{
					break;
				}
				// 다음 구멍을 검사한다
				if (j != N) continue;

				// 멀티탭에 꽃혀 있는 것 중에서 가장 나중에 사용하거나
				// 사용되지 않는 기기 찾는다.
				int change, val = -1;
				for (int k = 1; k <= N; k++)
				{
					int term = 0;
					for (int l = i + 1; l <= K && order[l] != hole[k]; l++) term++;
					if (term > val)
					{
						val = term;
						change = k;
					}
				}
				// 가장 나중에 사용하는 것을 뽑는다.
				hole[change] = order[i];
				result++;
			}
		}
	}

	cout << result;

	return 0;
}



/*
처음 접근했던 풀이.
코드를 뽑을때 빈도수가 가장 낮은 것을 먼저 뽑아야 최소가 될것이라 생각했다.
빈도수와 코드번호를 페어로 입력받아 
1. 탭이 아예 비었을때 2. 이미 꽂혀있을때 3. 탭이 한 두개 비어있고 꽂을 수 있을때 4. 뽑아야 할때
총 4가지 경우로 나눠서 계산했다.
하지만 이후 한번도 쓰지 않을 기기를 빼거나 제일 마지막에 쓰일 기기를 빼는 것이
최적이었다.
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int n, k;
int plug[101];

int solve() {
	int ret = 0;
	int freq[101] = { 0 };

	//플러그 빈도 저장
	//얼마나 자주 사용하는지
	for (int i = 1; i <= k; ++i)
		freq[plug[i]]++;

	//멀티탭에 하나씩 꽂는다.
	//(빈도, 멀티탭 이름)순으로 pair를 만든다.
	//빈도가 많은 순이 앞에 오도록 하기 위해 부호를 -로 하여 정렬한다.
	vector<pair<int, int>> mult;
	for (int i = 1; i <= k; ++i) {
		//멀티탭에 빈 경우 무조건 하나 꽂는다.
		if (mult.empty()) {
			mult.push_back({ -freq[plug[i]],plug[i] });
			//한 번 꽂았기 때문에 빈도수 감소.
			//-로 부호를 바꿨기 때문에 1을 더해야 한다.
			mult.back().first++;
			continue;
		}
		//같은 플러그가 꽂혀있는지 확인
		bool same_plug = false;

		//현재 플러그가 이미 꽂혀 있다면 빈도수만 감소
		for (int j = 0; j < mult.size(); ++j) {
			if (mult[j].second == plug[i]) {
				mult[j].first++;
				same_plug = true;
				break;
			}
		}

		if (!same_plug) {
			//같은 플러그가 없고 멀티탭이 비어있으면 맨 뒤에 꽂는다.
			if (mult.size() < n) {
				mult.push_back({ -freq[plug[i]],plug[i] });
				mult.back().first++;
			}
			else {
				//멀티탭이 꽉 차서 새로 플러그를 꽂을 경우
				//제일 뒤에 있는 멀티탭의 빈도가 가장 낮기 때문에 제일 뒤에 플러그를 뺀다.
				//새로운 플러그를 꽂고 ret++;
				mult.pop_back();
				mult.push_back({ -freq[plug[i]],plug[i] });
				mult.back().first++;
				ret++;
			}
		}
		sort(mult.begin(), mult.end());
	}

	return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> k;
	for (int i = 1; i <= k; ++i)
		cin >> plug[i];
	cout << solve();

	return 0;
}