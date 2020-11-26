/*
kmp 알고리즘을 사용하는 문제.
알고스팟에서 익혀 풀어봤다.
*/


#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int N; //금고 맞춰야 하는 상태 수

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

vector<int> kmp(const string& s, const string& p) {
    int n = (int)s.size(), m = (int)p.size();
    vector<int> ret;
    vector<int> pi = getPi(p);
    //현재 대응된 글자의 수
    int j = 0;
    for (int i = 0; i < n; ++i) {
        //j번 글자와 짚더미의 해당 글자가 불일치할 경우,
        //현재 대응된 글자의 수를 pi[j-1]로 줄인다.
        while (j > 0 && s[i] != p[j])
            j = pi[j - 1];
        if (s[i] == p[j]) {
            j++;
            //글자가 대응될 경우
            if (j == m) {
                ret.push_back(i - m + 1);
                j = pi[j - 1];
            }
        }

    }
    return ret;
}



int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string T, P;

    getline(cin, T);
    getline(cin, P);

    vector<int>ret = kmp(T, P);

    cout << ret.size() << "\n";

    for (int i = 0; i < ret.size(); ++i)
        cout << ret[i] + 1 << " ";

    return 0;
}