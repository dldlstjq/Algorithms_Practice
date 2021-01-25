/*
스택, 큐와는 다른 자료구조 deque.
C++에서 #include <deque> 제공.
큐와 다르게 앞뒤로 모두 push, pop 가능.
아직 써본적이 없어서 익숙하지 않은데 많이 쓰면 익숙해 질듯.
*/
#include <iostream>
#include <string>
#include <algorithm>
#include <deque>

using namespace std;


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	deque<int> dq;
	int n;
	string str;
	cin >> n;

	for (int i = 0; i < n; i++) {
		cin >> str;

		if (str == "push_front") {
			int num;
			cin >> num;
			dq.push_front(num);
		}

		else if (str == "push_back") {
			int num;
			cin >> num;
			dq.push_back(num);
		}

		else if (str == "pop_front") {
			if (dq.empty())
				cout << "-1" << '\n';
			else {
				cout << dq.front() << '\n';
				dq.pop_front();
			}
		}

		else if (str == "pop_back") {
			if (dq.empty())
				cout << "-1" << '\n';
			else {
				cout << dq.back() << '\n';
				dq.pop_back();
			}
		}

		else if (str == "size") {
			cout << dq.size() << '\n';
		}

		else if (str == "empty") {
			if (dq.empty())
				cout << "1" << '\n';
			else
				cout << "0" << '\n';
		}

		else if (str == "front") {
			if (dq.empty())
				cout << "-1" << '\n';
			else
				cout << dq.front() << '\n';
		}

		else if (str == "back") {
			if (dq.empty())
				cout << "-1" << '\n';
			else
				cout << dq.back() << '\n';
		}

	}
	return 0;
}