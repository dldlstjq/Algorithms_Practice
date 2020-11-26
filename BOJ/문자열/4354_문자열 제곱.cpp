/*
kmp 알고리즘에서 실패함수-pi를 활용한 문제.
kmp 알고리즘에 익숙하지 않으니 간단한 응용문제도 잘 못풀겠다.
예외처리를 해주지 않아서 처음에 틀렸다.
자세한 풀이는 코드 참고.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

vector<int> getPi(const string& s) {
    int n = (int)s.size(), j = 0;
    vector<int> pi(n, 0);
    for (int i = 1; i < n; ++i) {
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j])
            pi[i] = ++j;
    }
    return pi;
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    while (1) {
        string s;
        cin >> s;

        if (s == ".")
            break;

        //getPi를 통해 접두사이면서 접미사인 문자열의 길이를 구한다. 
        vector<int>pi = getPi(s);
        int k = s.length();

        /*ex) S = "ababab"의 실패 함수 마지막 값은 pi[S.length() - 1] = 4 입니다.
            여기서, S.length() - pi[S.length() - 1] = 6 - 4 = 2 입니다.← 반복되는 문자열 크기
            최종적으로 S.length() / (반복되는 문자열 크기) = 6 / 2 = 3 ← 답*/

            /*"abcabcab", "abababa", "ababa" 등과 같이 문자열 제곱수로 표현할 수 없지만,
               접두사와 접미사가 모두 될 수 있는 부분문자열이 있는 경우
               실패 함수 마지막 값 pi[S.length() - 1] > 1 임에도 반복되는 문자열로 나눠지지 않는 Case가 있습니다.*/

        if (k % (k - pi[k - 1]) != 0)
            cout << 1 << "\n";
        else
            cout << k / (k - pi[k - 1]) << "\n";
    }

    return 0;
}