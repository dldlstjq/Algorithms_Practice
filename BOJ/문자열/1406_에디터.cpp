/*
처음에는 문자열을 그대로 배열처럼 사용했는데 시간초과 남.
배열처럼 사용하면 삽입, 삭제 할 때마다 모든 요소에 변화가 생겨 비효율적이라고 함.
링크드리스트를 사용하면 시간초과 안나고 풀이 가능.
C++ STL에서 연결리스트도 제공한다는거 배움.
*/
#include <iostream>
#include <string>
#include <list>

using namespace std;


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string str;
    char order, ch;
    int n;

    cin >> str;
    cin >> n;

    list <char> li(str.begin(), str.end());
    list<char>::iterator iter;

    auto cursor = li.end();

    for (int i = 0; i < n; i++) {
        cin >> order;

        if (order == 'L') {
            if (cursor != li.begin())
                cursor--;
        }

        else if (order == 'D') {
            if (cursor != li.end())
                cursor++;
        }

        else if (order == 'B') {
            if (cursor != li.begin()) {
                cursor--;
                cursor = li.erase(cursor);
            }

        }

        else if (order == 'P') {
            cin >> ch;
            li.insert(cursor, ch);
        }

    }

    for (iter = li.begin(); iter != li.end(); iter++)
        cout << *iter;


    return 0;
}


////////////////////////////////////
//스택 풀이
#include <iostream>
#include <string>
#include <stack>
using namespace std;

stack<char> head, tail; //커서 왼쪽, 오른쪽

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    string s;
    cin >> s;

    for (int i = 0; i < s.length(); i++)
        head.push(s[i]);

    int N;
    cin >> N;

    for (int i = 0; i < N; i++)
    {
        char op;
        cin >> op;
        //커서 왼쪽
        if (op == 'L')
        {
            if (!head.empty())
            {
                tail.push(head.top());
                head.pop();
            }
        }

        //커서 오른쪽
        else if (op == 'D')
        {
            if (!tail.empty())
            {
                head.push(tail.top());
                tail.pop();
            }
        }

        //커서 왼쪽 문자 삭제
        else if (op == 'B')
        {
            if (!head.empty())
                head.pop();
        }

        //커서 왼쪽에 문자 추가
        else
        {
            char c;
            cin >> c;
            head.push(c);
        }
    }

    while (!head.empty())
    {
        tail.push(head.top());
        head.pop();
    }

    string result;
    while (!tail.empty())
    {
        result += tail.top();
        tail.pop();
    }
    cout << result << "\n";
    return 0;
}