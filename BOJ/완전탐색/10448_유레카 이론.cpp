/*
처음엔 1부터 1000까지 모든 경우를 3중 for문으로 돌려 계산했다.
당연히 시간초과가 났고 최대 수가 1000이기 때문에 1000을 넘지 않는 삼각수를
미리 구한 다음 그 안에서 3중 for문으로 계산하면 답이 나온다.
*/



#include <iostream>
#include <vector>

using namespace std;


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;
	while (t--) {
		int num;
		cin >> num;
		int sum = 0;
		vector<int> v;

		//1000보다 작은 삼각수 계산
		int n = 1;
		while (n * (n + 1) / 2 < 1000) {
			v.push_back(n * (n + 1) / 2);
			n++;
		}

		bool flag = false;
		for (int i = 0; i < v.size(); ++i) {
			for (int j = 0; j < v.size(); ++j) {
				for (int k = 0; k < v.size(); ++k) {
					if (v[i] + v[j] + v[k] == num)
						flag = true;
				}
			}
		}
		if (flag)
			cout << 1 << "\n";
		else
			cout << 0 << "\n";
	}

	return 0;
}