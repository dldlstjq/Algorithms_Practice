/*
접근은 똑같이 했는데 처음 n을 0번째 부터 시작해서 n-1번까지 오는 식으로 
코드를 짰다. for문을 돌면서 색깔이 이전에 칠했던 것과 일치하지 않는 것 중
최소값을 택해서 진행하는 식으로 했는데 틀렸다.

다른 사람의 코드에서 n을 거꾸로 감소하는 식으로 고쳤고
어차피 색깔이 3개밖에 없기 때문에 하나를 칠했으면 둘 중 가격이 작은 쪽을
선택하면 더 간단하게 구현이 가능했다.
*/

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int INF = 987654321;
int n;
int price[1002][3];
int cache[1002][3];

//num번째 집의 색깔이 color 일때 최소 비용
int solve(int num, int color) {
	//기저사례: num이 0이면 해당 비용 반환
	if (num == 0)
		return price[num][color];
	int& ret = cache[num][color];
	if (ret != -1)return ret;

	//color에 따라 겹치지 않는 것 중 최소 값에 해당 비용을 더한다.
	if (color == 0)
		ret = min(solve(num - 1, 1), solve(num - 1, 2)) + price[num][0];
	else if (color == 1)
		ret = min(solve(num - 1, 0), solve(num - 1, 2)) + price[num][1];
	else if (color == 2)
		ret = min(solve(num - 1, 0), solve(num - 1, 1)) + price[num][2];

	return ret;
}


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);


	memset(cache, -1, sizeof(cache));
	cin >> n;

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < 3; ++j)
			cin >> price[i][j];

	int ans = INF;
	//0번째부터 저장했기 때문에 n-1을 인자로 넣는다.
	for (int i = 0; i < 3; ++i)
		ans = min(ans, solve(n - 1, i));

	cout << ans;

	return 0;
}


//처음 구현한 틀린 코드
//num번째 집의 색깔이 color 일때 최소 비용
int solve(int num, int color) {
	//기저사례: num이 n이면 범위 벗어나서 0
	if (num == n)
		return 0
		int& ret = cache[num][color];
	if (ret != INF)return ret;

	//첫번째 행은 color를 0으로 넘겨줌
	if (num == 0)
		ret = min(ret, solve(num + 1, 0) + price[num][color]);

	//두번째 행부터는 이전에 칠했던 color와 겹치지 않으면서
	//최소 가격인 color를 선택해 idx에 저장
	else {
		int idx = -1;
		int tmp = INF;
		for (int i = 0; i < 3; ++i) {
			//이전에 칠했던 color와 겹치지 않으면서
			//가격이 최소인 color를 선택
			if (i != color) {
				if (tmp > price[num][i]) {
					tmp = price[num][i];
					idx = i;
				}
			}
		}
		//해당 idx를 color로 해서 재귀함수를 진행한다.
		ret = min(ret, solve(num + 1, idx) + price[num][idx]);
	}

	return ret;
}