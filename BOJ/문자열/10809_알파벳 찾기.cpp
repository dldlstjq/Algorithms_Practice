#include <iostream>
#include <string>
#include <vector>

using namespace std;


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	vector<int> v(27, -1);
	int n;
	string str;

	cin >> str;

	for (int i = 0; i < str.size(); i++) {
		if (v[str[i] - 'a'] == -1)
			v[str[i] - 'a'] = i;
	}

	for (int i = 0; i < 26; i++) {
		cout << v[i] << " ";
	}
	return 0;
}