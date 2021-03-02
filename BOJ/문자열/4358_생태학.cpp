/*
트라이를 적용하려했는데 들어오는 문자가 공백, 특수문자를 모두 포함하기 때문에
배열 크기도 더 필요했고 숫자로의 변환도 쉽지 않았다.
종만북에 terminal이 불린 값이 아니라 다른 변수형이면 map으로도 트라이를 사용할 수 있다고 나왔다.
여기서도 해당 문자가 몇 번 나왔는지가 중요하기 때문에 map을 사용하면 쉽게 해결가능했다.
거기다 map 자체에서 정렬을 해주기 때문에 굳이 따로 정렬이 필요없었고 
iterator를 써서 처음부터 문자를 하나씩 출력하면서 비율을 출력하면 됐다.
*/

#include <iostream>
#include <map>
#include <string>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	string str;
	int n = 0;
	map<string, double> mp;
	//전체 문자의 개수와 나타나는 빈도를 저장
	while (getline(cin, str)) {
		n++;
		mp[str]++;
	}

	cout << fixed;
	cout.precision(4);
	//begin()부터 시작해서 문자와 비율을 출력한다.
	for (auto i = mp.begin(); i != mp.end(); i++) {
		cout << i->first << " ";
		cout << (i->second / n) * 100 << "\n";
	}
	return 0;
}