/*
이진트리의 stl인 set을 이용하는 문제이다.
아무래도 익숙하지 않다보니 간단한건데도 코드가 많이 길어지거나 복잡해졌다.

처음에는 배열 두개와 set 두개를 선언해서 각각 저장한 후
해당 집합에 같은 원소가 있는지 확인하기 위해 find를 사용했다.
find사용을 위해 iterator 도 하나 선언하였고 같은 원소는 하나씩 지워나갔다.

문제는 A에서 B와 중복된 걸 지우면 B를 계산할 때 A를 다시 선언해야한다는 것이었다.
이렇게까지 할 필요는 없을 것 같아 다른 코드를 찾아보니 set 하나만 설정해
A의 원소를 다 넣고 B 원소를 넣을때 같은 것이 있으면 삭제, 없으면 삽입하는게 끝이었다.

그리고 같은 원소가 있는지 확인할 때 count를 사용했다.
count 자체가 원소의 개수를 반환하는데 set에서는 중복원소를 허용하지 않기 때문에
있으면 1, 없으면 0을 반환해서 간단했다.

*/

#include <iostream>
#include <set>
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int a, b;
	cin >> a >> b;

	set<int> s;

	for (int i = 0; i < a; ++i) {
		int tmp;
		cin >> tmp;
		s.insert(tmp);
	}
	for (int i = 0; i < b; ++i) {
		int tmp;
		cin >> tmp;
		if (s.count(tmp))
			s.erase(tmp);
		else
			s.insert(tmp);
	}
	cout << s.size();
	return 0;
}