//스택 활용하면 쉽게 푸는 문제

#include <iostream>
#include <string>
#include <stack>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    int cnt = 0;
    int rest = 0;   //스택에 남아있는 괄호 크기 저장
    cin >> n;

    stack <char> s;
    string str;

    for (int i = 0; i < n; i++) {
        cin >> str;

        for (int j = 0; j < str.size(); j++) {
            if (str[j] == '(') {
                s.push(str[j]);
            }
            else if (str[j] == ')') {
                if (s.empty()) {
                    cnt++;
                    continue;
                }

                else
                    s.pop();
            }
        }

        if (s.empty() && cnt == 0)
            cout << "YES" << '\n';

        else
            cout << "NO" << '\n';

        //스택, cnt 초기화
        rest = s.size();
        cnt = 0;
        for (int j = 0; j < rest; j++)
            s.pop();
    }
    return 0;
}