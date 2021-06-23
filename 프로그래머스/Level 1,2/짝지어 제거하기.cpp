/*
처음 생각난 풀이는 문자열을 돌면서 2개붙어있는 건 삭제하고 다시 처음부터 시작하는 것이다.
하지만 답은 맞았는데 효율성에서 시간초과가 나면서 어떻게 해결해야 하나 싶었다.
문자를 삭제한 후 다시 처음부터 돌아가기때문에 O(N^2) 시간이 걸린다.

검색해보니 스택을 사용하면 복잡하게 하지 않고 스택이 비었나 안비었나로 쉽게 확인가능했다.
스택은 한번만 순회하면 되기 때문에 O(N)만 걸리는 것 같다.
*/

// 스택 풀이. 시간도 더 적게 걸린다.
#include <iostream>
#include <string>
#include <stack>
using namespace std;

int solution(string s)
{
    int answer = 0;

    stack<char> st;

    for (int i = 0; i < s.length(); ++i) {
        // 스택이 비었거나 탑이랑 다른 문자면 스택에 푸시
        if (st.empty() || st.top() != s[i]) {
            st.push(s[i]);
            continue;
        }
        //탑이랑 문자가 같으면 pop
        else if (st.top() == s[i])
            st.pop();
    }

    if (st.empty())
        answer = 1;
    else
        answer = 0;


    return answer;
}



//첫 풀이. 문자열 자체를 삭제
#include <iostream>
#include<string>
using namespace std;

int solution(string s)
{
    int answer = 1;

    int i = 0;
    while (s.length() != 0) {
        // 문자열 길이가 1일때는 없앨 수가 없다.
        if (s.length() == 1) {
            answer = 0;
            break;
        }

        // 문자열 길이가 1일때는 에러가 난다.
        else if (s[i] == s[i + 1]) {
            s.erase(i, 2);
            i = 0;
            continue;
        }
        else {
            i++;
            // 끝까지 갔다는 건 없앨 수 있는 문자가 없다.
            if (i >= s.length() - 1) {
                answer = 0;
                break;
            }

        }

    }

    return answer;
}