/*
X나 Y를 재귀호출로 치환하는 것까진 알아냈는데
문자열의 길이를 구하는 부분에서 잘 몰랐다.

점화식을 통해 문자열 길이 계산을 미리 해놓고
skip번째 문자를 하나씩 출력한다.
*/

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

//초기 문자열 seed를 generation세대 진화한 결과를 출력
//void curve(const string& seed, int generations) {
//	//기저 사례
//	if (generations == 0) {
//		cout << seed;
//		return;
//	}
//
//	for (int i = 0; i < seed.size(); ++i) {
//		if (seed[i] == 'X') {
//			curve("X+YF", generations - 1);
//		}
//		else if (seed[i] == 'Y') {
//			curve("FX-Y", generations - 1);
//		}
//		else
//			cout << seed[i];
//	}
//}

const int MAX = 1000000000 + 1;
//length[i]=X나 Y를 i번 치환한 후의 길이
int length[51];
void precalc() {
	length[0] = 1;
	for (int i = 1; i <= 50; ++i)
		length[i] = min(MAX, 2 * length[i - 1] + 2);
}
const string EXPAND_X = "X+YF";
const string EXPAND_Y = "FX-Y";
//dragonCurve를 generations 진화시킨 결과에서 skip번째 문자를 반환한다.
char expand(const string& dragonCurve, int generations,
	int skip) {
	//기저 사례
	if (generations == 0) {
		//더 이상 확장되지 않는데 문자열 크기보다 skip이 더 큰 경우 프로그램 종료
		if (skip > dragonCurve.size())
			exit(-1);
		//assert(skip < dragonCurve.size());
		return dragonCurve[skip];
	}
	for (int i = 0; i < dragonCurve.size(); ++i)
		//문자열이 확장되는 경우
		if (dragonCurve[i] == 'X' || dragonCurve[i] == 'Y') {
			if (skip >= length[generations])
				skip -= length[generations];
			else if (dragonCurve[i] == 'X')
				return expand(EXPAND_X, generations - 1, skip);
			else
				return expand(EXPAND_Y, generations - 1, skip);
		}
	//확장되진 않지만 건너뛰어야 할 경우
		else if (skip > 0)
			--skip;
	//답을 찾은 경우
		else
			return dragonCurve[i];

}
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int c;
	cin >> c;
	while (c--) {
		int generation, skip, range;
		cin >> generation >> skip >> range;
		if (generation < 0 || generation>50 || skip < 1 || skip>1000000000 || range < 1 || range>50)
			exit(-1);

		precalc();
		for (int j = 0; j < range; j++) //skip번째 문자부터 range만큼 글자 출력
			cout << expand("FX", generation, skip + j - 1);

		cout << "\n";
	}

	return 0;
}