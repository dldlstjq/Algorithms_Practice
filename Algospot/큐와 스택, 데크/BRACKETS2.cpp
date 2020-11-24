/*
한 괄호쌍이 다른 괄호쌍과 교차해 있으면 안된다는 조건을 보지 못했다.
또한 스택에 열린 괄호가 남아있는 경우를 확인하지 못해 오답을 받았다.

문제를 잘 읽어보고 예외처리도 확실하게 생각해야겠다.
*/

#include <iostream>
#include <string>
#include <stack>

using namespace std;


//내 풀이
bool wellMatched(string s) {
    int n = s.length();
    stack<char> st;

    for (int i = 0; i < n; ++i) {
        //여는 괄호면 스택에 푸시
        if (s[i] == '(' || s[i] == '{' || s[i] == '[')
            st.push(s[i]);

        else {
            //닫는 괄호일 때 스택이 비어있으면 쌍이 안맞음
            if (st.empty())
                return false;

            //스택의 탑과 s[i]의 짝이 맞으면 pop. 짝이 다르면 false
            char tmp = st.top();
            if (tmp == '(' && s[i] == ')')
                st.pop();
            else if (tmp == '{' && s[i] == '}')
                st.pop();
            else if (tmp == '[' && s[i] == ']')
                st.pop();
            else
                return false;
        }
    }
    //스택에 열린 괄호가 남아 있는 경우 확인
    if (st.empty())
        return true;
    else
        return false;
}


//책 풀이
bool wellMatched(const string& formula) {
    //여는 괄호문자들과 닫는 괄호 문자들
    const string opening("({["), closing(")}]");
    //이미 열린 괄호들을 순서대로 담는 스택
    stack<char> openStack;

    for (int i = 0; i < formula.size(); ++i) {
        //여는 괄호인지 닫는 괄호인지 확인
        if (opening.find(formula[i]) != -1)
            //여는 괄호라면 무조건 스택에 집어넣는다.
            openStack.push(formula[i]);
        else {
            //이 외의 경우 스택 맨 위의 문자와 맞춰보자.
            //스택이 비어있는 경우 실패
            if (openStakc.empty())
                return false;
            //서로 짝이 맞지 않아도 실패
            if (opening.find(openStack.top()) != closing.find(formula [[i]] ))
                return false;

            //짝을 맞춘 괄호는 스택에서 뺀다.
            openStack.pop();
        }
    }

    //닫히지 않은 괄호가 없어야 성공
    return openStack.empty();

}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int c;
    cin >> c;

    while (c--) {
        string str;
        cin >> str;

        if (wellMatched(str))
            cout << "YES" << "\n";
        else
            cout << "NO" << "\n";

    }

    return 0;
}