/*
KMP알고리즘을 이용한 접두사/접미사 문제이다.
KMP알고리즘을 이해해야 풀이가 가능한데 완전히 익힐 때 까지 연습이 많이 필요할 것 같다.
책의 코드보다 인터넷에 있는 코드가 개인적으로는 이해가 더 잘된다.
*/

#include <iostream>
#include <vector>
#include <algorithm>

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
vector<int> kmp(string s) {
    vector<int> ans;
    vector<int>pi = getPi(s);
    int n = (int)s.size();

    while (n > 0) {
        //s[..n-1]은 답이다.
        ans.push_back(n);
        //s[..n-1]의 접미사도 되고 접두사도 되는 문자열도 답이다.
        n = pi[n - 1];
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string dad, mom;
    cin >> dad;
    cin >> mom;

    string name = dad + mom;

    vector<int> ret = kmp(name);
    sort(ret.begin(), ret.end());
    for (int i = 0; i < ret.size(); ++i)
        cout << ret[i] << " ";
    return 0;
}