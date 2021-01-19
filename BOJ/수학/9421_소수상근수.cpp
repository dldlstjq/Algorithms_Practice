/*
상근수를 구할 때 해당 수가 이전에 나온 수라면 상근수가 될 수 없다.
이전에 나온 수인지 확인하는게 관건이었는데 일일이 벡터나 배열을 돌면서
확인하는건 시간이 오래 걸릴것 같았다.
처음엔 set이라는 stl함수를 사용했는데 find의 반환값이 iterator 형이어서 
이것을 정수나 bool값으로 만들기 어려웠다.

결국 구글링을 통해 map의 count를 쓰면 해당 원소가 있으면 1, 없으면 0을
반환한다는 것을 이용해서 visited배열에 나왔다고 표시하는 것으로 구현할 수 있었다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <map>

using namespace std;

const int MAX = 1000000 + 1;
int n;
bool isPrime[MAX];

void eratosthenes() {
	memset(isPrime, 1, sizeof(isPrime));
	isPrime[0] = isPrime[1] = false;
	int sqrtn = int(sqrt(MAX));
	for (int i = 2; i <= sqrtn; ++i) {
		if (isPrime[i])
			for (int j = i * i; j < MAX; j += i)
				isPrime[j] = false;
	}
}

bool solve(int k) {
	map<int, bool> visited;
	bool flag = true;
	int temp = k;
	while (1) {
		int ret = 0;
		while (temp) {
			ret += (temp % 10) * (temp % 10);
			temp /= 10;
		}
		//1이 나오면 소수상근수
		if (ret == 1)
			return true;
		//해당 숫자가 나오지 않았으면 표시
		if (!visited.count(ret))
			visited[ret] = true;
		//이미 나온 수라면 상근수 아님
		else
			return false;
		temp = ret;
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);


	eratosthenes();
	cin >> n;
	int sum = 0;
	vector<int> ret;

	//소수이면서 상근수이면 ret에 넣는다
	for (int i = 0; i <= n; ++i) {
		if (isPrime[i])
			if (solve(i))
				ret.push_back(i);
	}
	for (int i = 0; i < ret.size(); ++i)
		cout << ret[i] << "\n";

	return 0;
}