/*
비트마스크를 활용한 동적계획법 문제는 아직 어렵게 느껴진다.
답도 제대로 안나오는걸 봐서 좀 더 자세히 볼 필요가 있다.
*/
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

//실험 데이터 복구 문제를 해결하는 동적 계획법 알고리즘
const int MAX_N = 15;
int k;
string word[MAX_N];
int cache[MAX_N][1 << MAX_N];	//최대 자릿수 표현하기 위해 (1<<MAX)+1
int overlap[MAX_N][MAX_N];	//글자들이 얼마나 겹치는가(overlap)
//마지막에 출현한 조각 last와 지금까지 출현한 조각의 집합 used가 주어졌을 때
//나머지 조각을 추가해서 얻을 수 있는 overlaps()의 최대 합
int restore(int last, int used) {
	//기저 사례
	if (used == (1 << k) - 1)
		return 0;
	//메모이제이션
	int& ret = cache[last][used];
	if (ret != -1)
		return ret;
	ret = 0;
	for (int next = 0; next < k; ++next)
		if ((used & (1 << next)) == 0) {
			//used+(1<<next)->next 사용했다고 표시
			int cand = overlap[last][next] +
				restore(next, used + (1 << next));
			ret = max(ret, cand);
		}
	return ret;
}

//실험 데이터 복구 문제의 실제 답을 계산하는 알고리즘
//처음 호출 시 last는 recover()가 최댓값을 반환하는 시작 단어로,
//used는 1<<last로 둔다.
string reconstruct(int last, int used) {
	//기저 사례
	if (used == (1 << k) - 1)
		return"";
	//다음에 올 문자열 조각을 찾는다.
	for (int next = 0; next < k; ++next) {
		//next가 이미 사용되었으면 제외
		if (used & (1 << next))
			continue;
		//next를 사용했을 경우의 답이 최적해와 같다면 next를 사용한다
		int ifUsed = restore(next, used + (1 << next) +
			overlap[last][next]);
		if (restore(last, used) == ifUsed)
			return (word[next].substr(overlap[last][next]) +
				reconstruct(next, used + (1 << next)));	//used+(1<<next)->next 사용했다고 표시

	}
	//뭔가 잘못된 경우
	return "******oops*****";
}

//overlap 초기화
int getOverlap(const string& s1, const string& s2) {
	for (int length = min(s1.size(), s2.size()); length > 0; length--)
		if (s1.substr(s1.size() - length) == s2.substr(0, length))
			return length;
	return 0;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);


	int c;
	cin >> c;
	while (c--) {
		cin >> k;
		for (int i = 0; i < k; ++i)
			cin >> word[i];

		memset(cache, -1, sizeof(cache));
		while (1) {
			bool removed = false;
			for (int i = 0; i < k && !removed; ++i)
				for (int j = 0; j < k; ++j)
					//부분문자열이 겹친다면 삭제
					if (i != j && word[i].find(word[j]) != -1) {
						//heapSort 삭제와 비슷한 과정
						word[j] = word[k - 1];	//맨 끝에 있는 string과 위치 변경
						k--;
						removed = true;
					}
			if (!removed)
				break;
		}
		word[k] = "";
		//overlap 초기화
		for (int i = 0; i <= k; ++i)
			for (int j = 0; j <= k; ++j)
				overlap[i][j] = getOverlap(word[i], word[j]);
		cout << reconstruct(k, 0) << "\n";
	}

	return 0;
}