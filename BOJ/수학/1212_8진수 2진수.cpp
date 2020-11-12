/*
1313번과는 반대로 8진수를 2진수로 바꾸는 문제
처음에는 스택을 사용하여 문제를 품.
더 간단한 풀이가 있을거 같아 찾아보니 reverse 함수라는 걸 사용했다.
문자열이나 벡터에 있는 원소를 반대로 바꿔주는 함수인 것을 배웠다.
중간중간 0이 들어가야 하는 부분도 더 깔끔하게 처리됐다.
*/

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string change8to2(char c)
{
    string result = "";
    int num = c - '0';

    if (num == 0)           // 이걸 해주지 않으면 0이 입력일 때 빈 문자열이 반환된다.
        return "0";

    while (num != 0)
    {
        result += to_string(num % 2);
        num = num / 2;
    }
    reverse(result.begin(), result.end());

    return result;
}

int main() {
    string s;
    cin >> s;

    for (int i = 0; i < s.size(); i++)
    {
        if (i == 0)
            cout << change8to2(s[i]);
        else
        {
            string temp = change8to2(s[i]);
            while (temp.size() != 3)
                temp = '0' + temp;
            cout << temp;
        }
    }
}


//////////////////////////////////////
/*
처음에 푼 풀이. 스택을 사용
*/


#include <iostream>
#include <string>
#include <stack>

using namespace std;

stack <long long int> st;

void binary(int n) {
    while (n != 0) {
        st.push(n % 2);
        n /= 2;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string s;

    cin >> s;

    int n = s.size();

    //한 자리 숫자일때
    if (n == 1) {
        //0 하나일 경우
        if (s[0] - '0' == 0) {
            cout << 0;
            return 0;
        }

        //0이 아닌 한자리 수
        binary(s[0] - '0');
        int k = st.size();
        for (int i = 0; i < k; i++) {
            cout << st.top();
            st.pop();
        }
    }

    //두 자리 수 이상
    else {
        for (int i = n - 1; i >= 0; i--) {
            int tmp = s[i] - '0';

            //tmp가 4보다 작고 맨 윗자리가 아닌경우 = 맨 앞에 0이 와야 되는경우
            //000, 001, 010, 011
            if (tmp < 4 && i != 0) {
                //0이면 0 3개
                if (tmp == 0) {
                    for (int i = 0; i < 3; i++)
                        st.push(0);
                }
                else {
                    //1은 0 2개
                    if (tmp == 1) {
                        binary(tmp);
                        st.push(0);
                        st.push(0);
                    }
                    //나머지는 0 1개만
                    else {
                        binary(tmp);
                        st.push(0);
                    }
                }

            }
            else {
                binary(tmp);
            }

        }

        //출력
        int k = st.size();
        for (int i = 0; i < k; i++) {
            cout << st.top();
            st.pop();
        }
    }

    return 0;
}

