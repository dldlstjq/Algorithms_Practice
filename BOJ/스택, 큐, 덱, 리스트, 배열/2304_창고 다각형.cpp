/*
종만북의 울타리 자르기 문제를 스택을 이용한 풀이와 비슷하게 생각해
해당 코드를 변형시켜 풀어야 한다고 생각해 시간이 오래 걸렸다.

단순히 가장 큰 기둥을 찾고 그걸 기준으로 왼쪽, 오른쪽 높이를 더해가면 됐는데
너무 복잡하게 생각해 코드도 복잡해졌고 일관성이 없어 해결하지 못했다.

너무 책의 코드에 집착하지 않고 단순히 생각나는대로 해보는 것도 괜찮을 것 같다는 생각이 들었다.
*/

#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;

int n;
int first = 1001, last = 0;    //첫번째, 마지막 기둥 위치
int longest;    //가장 큰 기둥 위치
int h[1001];    //기둥 높이

int solveStack() {
	stack<int> st;
	int ret = 0;
	//시작부터 가장 큰 기둥 위치까지 넓이 계산
	for (int i = first; i <= longest; ++i) {
		if (h[i]) {
			if (st.empty())
				st.push(h[i]);
			else if (h[i] > st.top())
				st.push(h[i]);
		}
		ret += st.top();
	}
	while (!st.empty())
		st.pop();

	//끝부터 가장 큰 기둥 전까지 계산
	for (int i = last; i > longest; --i) {
		if (h[i]) {
			if (st.empty())
				st.push(h[i]);
			else if (h[i] > st.top())
				st.push(h[i]);
		}
		ret += st.top();
	}
	return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for (int i = 0; i < n; ++i) {
		int pos, height;
		cin >> pos >> height;
		h[pos] = height;
		first = min(first, pos);	//시작 기둥 위치
		last = max(last, pos);		//끝 기둥 위치
		if (height > h[longest])	//가장 큰 기둥 위치
			longest = pos;
	}

	cout << solveStack();
	return 0;
}