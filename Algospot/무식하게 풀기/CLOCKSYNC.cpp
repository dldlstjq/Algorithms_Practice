/*
생각보다 코드가 간단해서 놀랐다.
앞선 문제들과 같이 시계 연결 상태를 하나의 linked 배열에다가 표현했다.
연결된 시계는 x로 표시해서 접근하게 했다.

문제는 재귀함수 표현인데 문제를 여러 조각으로 쪼갠 뒤 하나를 수행하고
나머지는 재귀로 표현한다는데 문제를 쪼갠다는 것 자체가 감이 잘 안온다.

처음에는 0번 시계에서부터 접근하는 걸로 생각했는데
코드는 연결된 스위치로 접근을 해서 문제를 해결했다.

많은 문제를 풀어보면서 감을 익히는 수 밖에 없을 것 같다.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 9999, SWITCHES = 10, CLOCKS = 16;
//linked[i][j]='x': i번 스위치와 j번 시계가 연결되어 있다.
//linked[i][j]='.': i번 스위치와 j번 시계가 연결되어 있지 않다.
const char linked[SWITCHES][CLOCKS + 1] = {
	//0123456789012345
	"xxx.............",
	"...x...x.x.x....",
	"....x.....x...xx",
	"x...xxxx........",
	"......xxx.x.x...",
	"x.x...........xx",
	"...x..........xx",
	"....xx.x......xx",
	".xxxxx..........",
	"...xxx...x...x.."
};
//모든 시계가 12시를 가리키고 있는지 확인한다.
bool areAligned(const vector<int>& clocks) {
	for (int i = 0; i < CLOCKS; ++i)
		if (clocks[i] != 12)
			return false;
	return true;
}

//swtch번 스위치를 누른다.
void push(vector<int>& clocks, int swtch) {
	for (int clock = 0; clock < CLOCKS; ++clock)
		if (linked[swtch][clock] == 'x') {
			clocks[clock] += 3;
			if (clocks[clock] == 15)
				clocks[clock] = 3;
		}
}

//clocks: 현재 시계들의 상태
//swtch: 이번에 누를 스위치의 번호
//가 주어질 때, 남은 스위치들을 눌러서 clocks를 12시로 맞출 수 있는 최소 횟수를 반환한다.
//만약 불가능하다면 INF이상의 큰 수를 반환한다.
int solve(vector<int>& clocks, int swtch) {
	if (swtch == SWITCHES)
		return areAligned(clocks) ? 0 : INF;
	//이 스위치를 0번 누르는 경우부터 세 번 누르는 경우까지를 모두 시도한다.
	int ret = INF;
	for (int cnt = 0; cnt < 4; ++cnt) {
		ret = min(ret, cnt + solve(clocks, swtch + 1));
		push(clocks, swtch);
	}
	//push(clocks, swtch)가 네 번 호출되었으니 clocks는 원래와 같은 상태가 된다.
	return ret;
}


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;
	while (t--) {
		vector<int> clock;
		for (int i = 0; i < CLOCKS; ++i) {
			int tmp;
			cin >> tmp;
			clock.push_back(tmp);
		}
		int ret = solve(clock, 0);
		if (ret == INF)
			cout << -1 << "\n";
		else
			cout << ret << "\n";
	}
	return 0;
}