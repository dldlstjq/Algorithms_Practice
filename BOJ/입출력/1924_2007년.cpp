//처음엔 switch-case 이용하여 날짜를 표현. 하지만 배열로 한번에 정리하는게 더 깔끔

#include <iostream>

using namespace std;

int main() {
	std::ios_base::sync_with_stdio(false);
	int x, y, sum = 0;
	int month[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	char* day[7]{ "SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT" };
	cin >> x >> y;

	for (int i = 1; i < x; i++) {
		sum += month[i - 1];
	}
	sum += y;

	cout << day[sum % 7] << '\n';
	return 0;
}