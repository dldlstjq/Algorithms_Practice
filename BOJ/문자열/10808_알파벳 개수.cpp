//string 사용하면 쉽게 풀리는 문제.

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	vector<int> v(27, 0);
	int n;
	string str;

	cin >> str;

	for (int i = 0; i < str.size(); i++) {
		v[str[i] - 'a']++;
	}

	for (int i = 0; i < 26; i++) {
		cout << v[i] << " ";
	}

	return 0;
}