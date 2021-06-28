/*
처음 문제 이해를 잘못해서 틀렸고, priority_queue 사용을 잘 몰라 구현에 어려움을 겪었다.
회의실 배정과는 다르게 강의실을 얼마나 최소로 사용하는 가가 문제인데
회의실 배정과 똑같이 생각했다가 틀렸다.
강의를 최대한 많이 하는것이 아니라 강의 시간이 겹칠때만 강의실이 늘어나고
그 외에는 하나의 강의실만 사용해도 된다.

이것을 간과해서 처음에 헤맸다. 문제 이해를 하고 난 후에는 우선순위 큐를 사용하여
페어로 저장해 문제를 풀려고 했었다.
하지만 priority_queue 자체에서 pair로 저장하니 내부문제가 생겼고
오름차순, 내림차순을 하기 위해서는 직접 비교함수를 만들어야 했다.
결국 구글링을 통해 정답을 알 수 있었다.
*/

// 2021.06.28 회의실 배정이랑 비슷하게 생각하다 틀렸다. 오랜만에 푸니 그리디가 익숙치 않은데 계속 풀면서 감을 잡아나가야 겠다.

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
int n;
pair<int, int> p[200001];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	priority_queue<int, vector<int>, greater<int>> pq;

	cin >> n;
	for (int i = 0; i < n; ++i)
		cin >> p[i].first >> p[i].second;

	sort(p, p + n);
	//정렬을 했으니까, 맨 처음끝나는 시간을 넣는다.
	pq.push(p[0].second);

	int start, end;
	//두번째 강의부터 비교해 나간다.
	for (int i = 1; i < n; ++i) {
		start = p[i].first;
		end = p[i].second;
		//수업중인 강의실의 끝나는 시간 > 다음 수업 시작시간 => 강의실 추가
		if (pq.top() > start)
			pq.push(end);

		else {
			// 아니면 나가고 다음꺼 수행
			pq.pop();
			pq.push(end);
		}

	}
	cout << pq.size();

	return 0;
}



////////////////////////////////////
//첫풀이
/*
priority_queue 에 pair 사용하는게 잘 안맞았고 답도 틀렸다.
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int n;
int start[200001], finish[200001];
struct ascendingOrderByEndTime {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
        if (a.second == b.second) {
            return a.first > b.first;
        }
        return a.second > b.second;
    }
};

int schedule() {
    //일찍 끝나는 순서대로 정렬한다.
    priority_queue<pair<int, int>, vector<pair<int, int>>, ascendingOrderByEndTime> pq;
    for (int i = 0; i < n; ++i)
        pq.push(make_pair(start[i], finish[i]));

    //earliest: 다음 강의가 시작할 수 있는 가장 빠른 시간
    //selected: 지금까지 선택한 강의실 수. 최소 하나는 사용해야 함.
    int earliest = 0, selected = 1;
    while (!pq.empty()) {
        int meetingBegin = pq.top().first, meetingEnd = pq.top().second;
        pq.pop();
        if (earliest <= meetingBegin) {
            //earliest를 마지막 강의가 끝난 시간 이후로 갱신한다.
            earliest = meetingEnd;
        }
        else {
            //현재 강의가 끝나기 전 다른 강의가 있으면 강의실 추가
            selected++;
            //현재 강의 종료시간이 이전 강의 종료시간보다 작으면 갱신
            if (meetingEnd < earliest)
                earliest = meetingEnd;
        }
    }

    return selected;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> start[i] >> finish[i];
    cout << schedule();

    return 0;
}