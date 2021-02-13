/*
두 개의 힙을 써야한다는 힌트를 보고 이리저리 해봤는데 딱 맞게 떨어지게 정답이 나오지 않았다.
두시간 고민하다 못 풀어서 다른사람의 풀이를 봤다.

알고리즘
max heap에는 중앙값 이하의 값들이 들어간다.
min heap은 중앙값보다 큰 값이 들어간다.

(초기상태) max heap와 min heap가 모두 비었다면, max heap에 수를 넣어줍니다.

-heap 사이즈 다를 때
1. 새로운 값을 입력 시 2개의 heap의 사이즈가 다를 시 max heap의 top()의 값과 새로운 값을 비교
2. 만약 새로운 값이 더 클 경우 min heap에 넣어준다.
3. 작을 경우 max heap의 top()값을 넣고 min heap으로 옮겨주고 새로운 값은 min_heap으로 넣는다.

-heap 사이즈 같을 때
1. 새로운 값을 입력 시 2개의 heap 사이즈가 같을 시 min heap의 top()값과 새로운 값을 비교
2. 만약 새로운 값이 더 작을 경우 max heap에 넣어준다.
3. 작을 경우 min heap의 top()값을 max heap으로 옮겨주고 새로운 값은 max_heap으로 넣는다.

즉, 새로운 값을 넣고 난 후의 두 heap 사이즈가 다를 시 max heap의 top()값이 중앙값이 된다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int m;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;
	while (t--) {
		cin >> m;

		//k번째 수보다 큰 건 min_heap, 작은 건 max_heap에 넣는다.
		priority_queue<int, vector<int>, greater<int>> min_heap;
		priority_queue<int, vector<int>, less<int>> max_heap;

		//개수 출력
		cout << (m / 2) + 1 << "\n";

		int c = 0;	//한 줄에 10개씩 출력하기 위해
		for (int i = 1; i <= m; ++i) {
			int num;
			cin >> num;
			if (max_heap.size() == min_heap.size()) {
				if (min_heap.empty())
					max_heap.push(num);
				else {
					if (min_heap.top() <= num) {
						int top = min_heap.top();
						min_heap.pop();
						min_heap.push(num);
						num = top;
					}
					max_heap.push(num);
				}
			}

			else {
				if (max_heap.top() > num) {
					int top = max_heap.top();
					max_heap.pop();
					max_heap.push(num);
					num = top;
				}
				min_heap.push(num);
			}

			if (i % 2 == 1) {
				cout << max_heap.top() << " ";
				c++;
				if (c % 10 == 0)cout << "\n";
			}
		}
		cout << "\n";
	}
	return 0;
}