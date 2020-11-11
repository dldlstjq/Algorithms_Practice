#include <iostream>
#include <string>

using namespace std;

int main() {
	int cnt = 0;
	string str;
	while (cnt < 100) {
		getline(cin, str);

		cout << str << endl;
		cnt++;
	}
	return 0;
}
