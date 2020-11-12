/*
에라토스테네스의 체로 소수인 수만 따로 모음.
소수인 수로 소인수분해
*/
#include <iostream>
#include <cstdio>
#include <cmath>
#include <string>
#include <vector>

using namespace std;


int arr[10000001];
int n;
vector <int> v;

void primeNumberSieve(int number) {

	for (int i = 2; i <= number; i++) {
		arr[i] = i;
	}
	for (int i = 2; i <= number; i++) {
		if (arr[i] == 0)continue;
		for (int j = i + i; j <= number; j += i) {
			arr[j] = 0;
		}
	}

	//2부터 돌면서 소수인거는 v에 넣음
	for (int i = 2; i <= number; i++) {
		if (arr[i] != 0)
			v.push_back(arr[i]);
	}

}


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;

	//n까지 소수인 것만 찾아서 v에 넣음
	primeNumberSieve(n);

	int i = 0;
	while (n != 1) {
		if (n % v[i] == 0) {
			cout << v[i] << '\n';
			n /= v[i];
		}
		else
			i++;
	}
	return 0;
}