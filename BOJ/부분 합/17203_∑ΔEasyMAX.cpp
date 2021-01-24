/*
변화량 차의 합을 계산해야 하기 때문에 변화량의 차이를 먼저 계산하고
그 후 변화량 차이의 부분합을 계산한다.
차이를 적을때는 end-start를 해야 정답이 나온다.
*/

#include <iostream>
#include <cmath>

using namespace std;

int n, q;
int song[1001];	//노래 길이
int diff[1001];	//인접한 노래 변화량 차이
int psum[1001];	//diff의 부분합

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> q;

	for (int i = 1; i <= n; ++i) {
		cin >> song[i];
		if (i == 1) {
			diff[i] = 0;
			psum[i] = 0;
		}
		//노래 변화량을 diff에 계산하고
		//diff의 부분합을 psum에 저장
		else {
			diff[i] = abs(song[i] - song[i - 1]);
			psum[i] = psum[i - 1] + diff[i];
		}

	}
	//변화량 합 계산 시 인덱스에 start-1을 해주는 게 아니라 start로 해줘야 한다.
	for (int i = 0; i < q; ++i) {
		int start, end;
		cin >> start >> end;
		cout << psum[end] - psum[start] << "\n";
	}
	return 0;
}