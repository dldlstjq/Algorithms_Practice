#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	string str;

	for (int j = 0; j < 100; j++) {
		getline(cin, str);

		if (str.length() == 0)
			break;
		int small = 0, big = 0, num = 0, space = 0;

		for (int i = 0; i < str.length(); i++) {
			if (str[i] >= 'a' && str[i] <= 'z')
				small++;
			else if (str[i] >= 'A' && str[i] <= 'Z')
				big++;
			else if (str[i] >= '0' && str[i] <= '9')
				num++;
			else if (str[i] == ' ')
				space++; ' ';
		}
		cout << small << " " << big << " " << num << " " << space << '\n';
	}
	return 0;
}