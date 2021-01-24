/*
큐를 활용한 문제
*/
#include <iostream>
#include <queue>

using namespace std;


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    queue <int> q;
    int n, k, temp;

    cin >> n >> k;

    for (int i = 1; i <= n; i++) {
        q.push(i);
    }

    cout << "<";
    while (1) {
        //k번째 수 추출을 위해 k-1번째까지 수를 빼서 큐 뒤로 넣어줌
        for (int i = 0; i < k - 1; i++) {
            temp = q.front();
            q.pop();
            q.push(temp);
        }

        //front값이 k번째 값임. 출력하고 빼줌
        cout << q.front();
        q.pop();
        if (q.empty())
            break;
        cout << ", ";

    }
    cout << ">";

    return 0;
}


///////////////////////////////////////
//리스트를 이용한 풀이
#include <iostream>
#include <list>
using namespace std;

int n, k;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	list<int> li;
	cin >> n >> k;

	for (int i = 1; i <= n; ++i)
		li.push_back(i);

	list<int>::iterator iter = li.begin();

	cout << "<";
	//리스트 iterator를 활용하여 k번째 수를 출력하고 리스트에서 하나씩 지운다.
	while (n > 0) {
		for (int i = 0; i < k - 1; ++i) {
			if (iter == li.end())
				iter = li.begin();
			iter++;
			if (iter == li.end())
				iter = li.begin();
		}
		if (n == 1)
			cout << *iter;
		else
			cout << *iter << ", ";
		iter = li.erase(iter);
		n--;
	}
	cout << ">";
	return 0;
}