/*
처음 for문을 이용하여 해결하려 했는데 테이프로 막을 수 있는 곳을
제외하는게 힘들어서 큐로 구현했다.
구글링 해보니 2중 for문으로 구현할 수 있었다.
*/

//내 풀이
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

int N, L;
int pipe[101];
int solve() {
	int ret = 0;
	//큐에 물 샌 곳 저장
	queue<int> q;
	for (int i = 0; i < N; ++i)
		q.push(pipe[i]);

	//큐가 빌 때까지 반복
	while (!q.empty()) {
		int leak = q.front();

		//start는 현재 물 샌곳에서 테이프를 처음 붙이는 곳
		//block은 테이프로 막을 수 있는 범위
		double start = leak - 0.5;
		double block = start + L;

		//큐가 비어있지 않고 테이프로 막을 수 있는 범위 안에 들어오면
		//원소를 하나씩 뺀다.
		while (!q.empty() && q.front() <= block)
			q.pop();
		//더 이상 원소를 뺄 수 없는 경우 테이프로 막을 수 없기 때문에
		//갯수 증가하고 새로운 테이프로 시도한다.
		ret++;
	}
	return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> L;
	for (int i = 0; i < N; ++i)
		cin >> pipe[i];
	//정렬
	sort(pipe, pipe + N);
	cout << solve();

	return 0;
}


//2중for문 코드
/*
1. 상태가 나쁜 파이프의 위치를 입력받고 오름차순 정렬을 합니다.
2. 만약 i 번째 파이프가 상태가 나쁘다면 i부터 min(i 번째 파이프 위치 + 테이프의 길이 - 1, MAX)까지를 고쳤다고 표시를 합니다.
->min을 쓴 이유는 범위 초과에 따른 런타임 에러 방지 위해
->(i 번째 파이프 위치 + 테이프의 길이 -1)인 이유는 전후로 0.5 간격이 필요하기 때문에
3. i 번째 파이프가 고쳐졌다고 표시되어있으면 다음 파이프로 넘어갑니다.
4. 마지막 파이프까지 2번과 3번을 반복합니다.

그리디 알고리즘으로 분류된 이유는 오름차순으로 정렬된 파이프 위치가 주어졌을 때 
앞에 있는 파이프부터 차례차례 테이프를 붙이면 최소한으로 테이프를 사용할 수 있다고 접근했기 때문입니다.

*/

#include <iostream>
#include <algorithm>
using namespace std;

const int MAX = 1000 + 1;
int N, L;
int pipe[MAX];
bool taped[MAX];

int main(void)
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); //cin 실행속도 향상

	cin >> N >> L;

	int result = 0;
	for (int i = 0; i < N; i++)
		cin >> pipe[i];

	//품질 나쁜 파이프 오름차순 정렬
	sort(pipe, pipe + N);

	for (int i = 0; i < N; i++)
		if (!taped[pipe[i]])
		{
			//j<=pos+L이 아닌 이유는 0.5씩 간격줘야하므로
			for (int j = pipe[i]; j < min(pipe[i] + L, MAX); j++)
			taped[j] = true;
			result++;
		}
	cout << result << "\n";
	return 0;
}
