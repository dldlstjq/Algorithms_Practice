/*
kmp 알고리즘 사용.

처음 풀 때 일치하는 부분이 생기면 거기서 답을 도출했다.
하지만 aabaa aaaba 경우 aa가 일치하지만 그 뒤의 aba aab와 일치하지 않기 때문에 이걸 고려해야 한다.
따라서 원래 문자열인 original을 두 배 해서 kmp로 일치하는 부분을 찾으면 된다.

시계방향, 반시계방향 고려하는 것도 이해하기 쉽지 않았다.
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

//원래 문자열을 두 번 이어붙인 것에서 target을 찾는다.
//그러면 target에서 original에 일치하고 남은 부분들은 두번째 문자열의 시작부분과 일치해야 하므로
//이 검색에서 얻은 결과 위치는 항상 필요한 시프트 개수가 된다.
int shifts(const string& original, const string& target) {
    return kmp(original + original, target)[0];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int c;
    cin >> c;
    while (c--) {
        cin >> N;
        vector<string> dial(N + 1);
        for (int i = 0; i <= N; ++i)
            cin >> dial[i];

        int ret = 0;
        //하나씩 비교해서 나오는 횟수를 더해준다.
        for (int i = 0; i < N; ++i) {
            int clockwise = i % 2;

            //a를 시계방향 돌려 b를 만드는 것과 b를 반시계 방향 돌려 a 만드는 것 같다.
            if (clockwise)
                ret += shifts(dial[i], dial[i + 1]); //시계 방향
            else
                ret += shifts(dial[i + 1], dial[i]); //반시계 방향

        }
        cout << ret << "\n";
    }
    return 0;
}