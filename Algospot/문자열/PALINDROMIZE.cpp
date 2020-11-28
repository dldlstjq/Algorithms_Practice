/*
1. 주어진 문자열을 입력 받은 다음 뒤집은 문자열을 만듭니다.
2. 두 문자열을 합쳤을 때 접두사와 접미사가 최대로 겹치는 길이를 KMP 알고리즘을 통해 구합니다.
3. "주어진 문자열의 길이(문자열 + 뒤집은 문자열) * 2 - 2번에서 구한 길이" 가 정답입니다.

위 방식대로 풀면 풀린다. 처음에는 겹치는 부분의 i를 반환하는 식으로 쉽게 접근했는데 틀렸다.
책의 코드가 어려워 인터넷 코드로 풀었다.

- 책에서 kmp 알고리즘 다른 구현 방식으로 인터넷과 똑같은 코드가 있었다.
책에서도 처음 소개한 코드가 이해하기 까다롭다고 한다.
*/


#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

//부분 일치 테이블 생성. 책의 코드보다 이게 더 잘 이해됨.
vector <int> getPi(string p) {
    int m = (int)p.size(), j = 0;
    vector<int> pi(m, 0);

    for (int i = 1; i < m; ++i) {
        while (j > 0 && p[i] != p[j])
            j = pi[j - 1];
        if (p[i] == p[j])
            pi[i] = ++j;
    }
    return pi;
}

//s의 접두사도 되고 접미사도 되는 문자열들의 길이를 반환한다.
int kmp(string s, string p) {
    vector<int> ans;
    vector<int>pi = getPi(p);
    int n = (int)s.size(), m = (int)p.size(), j = 0;

    for (int i = 0; i < n; ++i) {
        while (j > 0 && s[i] != p[j])
            j = pi[j - 1];

        //서로 해당하는 글자가 같다면 j증가. i가 n의 끝이면 j 반환
        if (s[i] == p[j]) {
            j++;
            if (i == n - 1)
                return j;

        }
        else
            ++j;
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int c;
    cin >> c;
    while (c--) {
        string s, s_reverse;
        cin >> s;
        s_reverse = s;
        reverse(s_reverse.begin(), s_reverse.end());

        //원래 문자열과 뒤집은 문자열을 합친 뒤 Suffix와 Prefix끼리 겹치는 만큼 빼면 가장 짧은 문자열
        int ret = s.length() * 2 - kmp(s, s_reverse);
        cout << ret << "\n";
    }

    return 0;
}