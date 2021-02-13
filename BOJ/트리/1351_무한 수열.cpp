/*
map을 사용하여 10^12까지 모두 저장하는건 메모리 초과가 난다.
따라서 이미 있는 값이라면 그대로 출력하고 없으면 새로 만들어서 map에 넣으면 된다.
른
이걸 반복문으로 구현하려다 마땅히 생각이 나지 않았는데
재귀함수를 사용하면 너무 간단하게 구현할 수 있었다.

혹시나 반복문으로 푼 풀이가 있을까 싶어 찾아봤는데 찾을 수 없었다.
*/

#include <iostream>
#include <map>
using namespace std;

long long n, p, q;
map<long long, long long> mp;

long long solve(long long num) {
	if (mp.count(num))
		return mp[num];
	else
		return mp[num] = solve(num / p) + solve(num / q);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> p >> q;

	mp[0] = 1;
	cout << solve(n);
	return 0;
}