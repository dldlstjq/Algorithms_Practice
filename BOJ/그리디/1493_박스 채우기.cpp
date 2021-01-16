/*
분할정복을 사용하여 크기가 가장 큰것부터 시도한다는 건 알았지만
가로, 세로, 높이 크기를 어떻게 설정해야 하는지 잘 몰랐다.

셋 중 하나라도 0이 될 때까지 반복한 후 빠져나와서 카운트를 출력한다.
하나라도 0이 되기 전에 for문을 다 돌았을 때는 주어진 큐브를 다 써도
상자를 채우지 못한 것이므로 fail을 체크하고 -1을 출력한다.
*/

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
int L, W, H, N, a, b, cnt = 0, fail = 0;
int cube[20];
vector <pair<int, int>> v; //2의 a승과 그 개수를 저장
void divide(int l, int w, int h, int idx) {
	if (l == 0 || w == 0 || h == 0) return;
	for (int i = idx; i < v.size(); i++) {
		if (v[i].second != 0 && l >= v[i].first && w >= v[i].first && h >= v[i].first) {
			v[i].second--;
			cnt++;
			divide(l - v[i].first, w, h, i);
			divide(v[i].first, w - v[i].first, h, i);
			divide(v[i].first, v[i].first, h - v[i].first, i);
			return;
		}
	}
	fail = 1;
}
int main() {
	cin >> L >> W >> H >> N;
	for (int n = 0; n < N; n++) {
		cin >> a >> b;
		cube[a] += b;
	}
	for (int i = 19; i >= 0; i--) {
		if (cube[i] != 0) {
			v.push_back(make_pair(pow(2, i), cube[i]));
		}
	}
	divide(L, W, H, 0);
	if (fail) cout << -1;
	else cout << cnt << endl;
	return 0;
}