/*
재귀호출을 이용한 이항 계수의 계산 vs 메모이제이션을 이용한 이항 계수의 계산
*/

#include <iostream>
#include <chrono>

using namespace std;

const int MAX = 30;
//-1로 초기화
int cache[MAX][MAX];

//재귀
int bino(int n, int r) {
	//기저사례: n=r(모든 원소를 다 고르는 경우) 혹은 r=0(고를 원소가 없는 경우)
	if (r == 0 || n == r)
		return 1;
	return bino(n - 1, r - 1) + bino(n - 1, r);
}

//메모이제이션
int bino2(int n, int r) {
	//기저사례
	if (r == 0 || n == r)
		return 1;
	//-1이 아니라면 한 번 계산했던 값이니 곧장 반환
	if (cache[n][r] != -1)
		return cache[n][r];
	//직접 계산한 뒤 배열에 저장
	return cache[n][r] = bino2(n - 1, r - 1) + bino2(n - 1, r);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	using namespace std::chrono;

	int n, r;
	high_resolution_clock::time_point t1, t2;
	duration<double> time_span;

	cout << "n과 r 입력: ";
	cin >> n >> r;

	//initialize();
	//memset()을 이용해 cache 배열을 초기화한다.
	memset(cache, -1, sizeof(cache));
	cout << "재귀호출을 이용한 이항 계수 계산" << "\n";
	t1 = high_resolution_clock::now();
	cout << bino(n, r) << "\n";
	t2 = high_resolution_clock::now();
	time_span = duration_cast<duration<double>>(t2 - t1);
	cout << "경과 시간: " << time_span.count() << "초" << "\n" << "\n";

	cout << "메모이제이션을 이용한 이항 계수 계산" << "\n";
	t1 = high_resolution_clock::now();
	cout << bino2(n, r) << "\n";
	t2 = high_resolution_clock::now();
	time_span = duration_cast<duration<double>>(t2 - t1);
	cout << "경과 시간: " << time_span.count() << "초" << "\n" << "\n";

	return 0;
}