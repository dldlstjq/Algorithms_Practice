/*
최적을 구하는 것에서 틀렸다.
가장 적게 사용하는 걸 빼고 넣으면 되는줄 알았는데
가장 나중에 사용하거나 이후 안쓰일 코드를 빼야했다.
*/
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