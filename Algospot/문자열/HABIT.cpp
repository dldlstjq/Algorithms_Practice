/*
접미사 배열(suffix array)를 이용해서 푸는 문제.
접미사 배열을 구하고 다른 부분 문자열을 구하는 알고리즘과 합쳐서 풀어야 한다.

kmp 알고리즘도 마찬가지였지만 문자열 파트는 4~5번 봐야 이해가 될 듯 하다.
나만 어려운 줄 알았는데 구글랭 해보니 다들 어려워하는 파트였다.
*/


#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int t;  //단어의 위치를 보는 변수
vector<int> group;  //그룹 번호 저장

bool cmp(int a, int b) {
    //그룹 번호가 다르면 이들을 이용해 비교.
    if (group[a] != group[b])
        return group[a] < group[b];
    //아니라면 S[a+t..]와 S[b+t..]의 첫 t글자 비교한다.
    return group[a + t] < group[b + t];
}

vector<int> getSuffixArray(const string& s) {
    int n = s.size();
    //group[i]=접미사들을 첫 t글자 기준으로 정렬했을때
    //          S[i..]가 들어가는 그룹 번호.
    //t=1일때는 정렬할 것 없이 S[i..]의 첫 글자로 그룹 번호를
    //정 해줘도 같은 효과가 있다.
    t = 1;
    group.resize(n + 1);
    //vector<int> group(n + 1);
    for (int i = 0; i < n; ++i)
        group[i] = s[i];
    group[n] = -1;
    //결과적으로 접미사 배열이 될 반환 값. 이 배열을 lg(n)번 정렬한다.
    vector<int> perm(n);
    for (int i = 0; i < n; ++i)
        perm[i] = i;
    while (t < n) {
        //group[]은 첫 t글자를 기준으로 계산해 뒀다.
        //첫 2t글자를 기준으로 perm을 다시 정렬한다.
        sort(perm.begin(), perm.end(), cmp);

        //2t글자를 기준으로 한 그룹 정보를 만든다.
        vector<int> newGroup(n + 1);
        newGroup[n] = -1;
        newGroup[perm[0]] = 0;
        for (int i = 1; i < n; ++i) {
            //그룹이 다를 경우 다음 그룹 번호 할당
            if (cmp(perm[i - 1], perm[i]))
                newGroup[perm[i]] = newGroup[perm[i - 1]] + 1;
            //그룹이 같을 경우 같은 그룹 번호 할당
            else
                newGroup[perm[i]] = newGroup[perm[i - 1]];
        }
        //새로운 그룹 할당
        group = newGroup;

        //2t 글자가 n을 넘으면 접미사 배열 완성
        t *= 2;
    }
    return perm;
}

//s[i..]와 s[j..]의 공통 접두사의 최대 길이를 계산한다.
int commonPrefix(const string& s, int i, int j) {
    int k = 0;
    while (i < s.size() && j < s.size() && s[i] == s[j]) {
        ++i; ++j; ++k;
    }
    return k;
}

//k번 이상 출현하는 s의 부분 문자열 중 최대길이를 찾는다.
int longestFrequent(int k, const string& s) {
    vector<int> a = getSuffixArray(s);
    int ret = 0;
    for (int i = 0; i + k <= s.size(); ++i) {
        ret = max(ret, commonPrefix(s, a[i], a[i + k - 1]));
    }
    return ret;
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int c;
    cin >> c;
    while (c--) {
        int k;
        string s;
        cin >> k >> s;
        cout << countSubstrings(k, s) << "\n";
    }

    return 0;
}