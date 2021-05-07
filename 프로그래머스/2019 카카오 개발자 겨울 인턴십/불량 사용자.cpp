/*
69분

접근방법
1. banned_id에 매핑되는 후보들을 2차원 벡터에 저장한다.
2. dfs를 수행하며 각 후보에 해당하는 아이디를 string 벡터에 넣고
banned_id 개수만큼 차면 map에 집어넣는다. map은 중복이 안되고 간단해서 사용했다.

후보군을 뽑는 것은 쉽게 됐는데 중복여부를 확인하는 것이 어려웠다.
중복을 일일이 확인하는 건 시간이 많이 걸리기 때문에 중복을 허용하지 않는 map, set을 써야겠다는 생각을 했고
key, value를 잘 저장하는 map을 선택했다.
하나의 아이디가 성공하면 그 다음 후보 아이디를 찾아야 하기 때문에 dfs를 사용했고 다행히 그 아이디어가 맞은 것 같다.

풀이를 보다보니 그냥 완전탐색으로 접근해서 풀면 되는 거였다.
특별한 알고리즘이 있을 줄 알았는데 아니었다.
항상 완탐으로 먼저 생각해보고 최적화방법이있는지 봐야겠다.
풀고 나니 충분히 짧은 시간안에 풀 수도 있었겠다는 생각이 들었다.

다른 사람의 풀이도 참고.
*/

//내 풀이
#include <string>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

vector<vector<string>> v;   //불량 후보 아이디
map<vector<string>, int> m; //불량후보들을 map형태로 저장
int N;  //후보 아이디의 크기


bool same(string s1, string s2) {
    //길이가 다르면 아예 다른 문자열
    if (s1.length() != s2.length())
        return false;

    //같은 문자이거나 s1이 *이면 ok
    int i = 0;
    while (i != s1.length()) {
        if (s1[i] == s2[i] || s1[i] == '*')
            i++;
        else
            return false;
    }
    return true;
}

void dfs(int idx, vector<string> s) {
    //아이디가 꽉차면 중복 여부 확인해서 카운트
    if (s.size() == N) {
        //정렬하면 알파벳순으로 정렬되어 순서가 똑같아진다.
        //중복을 쉽게 알 수 있다.
        sort(s.begin(), s.end());
        if (!m.count(s))
            m[s] += 1;
        return;
    }

    //재귀함수를 돌면서 아이디가 있는지 확인해서 없으면 s에 넣고 확인한다.
    //검사가 끝나면 맨 뒤에 값을 제거한다.
    for (int j = 0; j < v[idx].size(); ++j) {
        if (find(s.begin(), s.end(), v[idx][j]) == s.end()) {
            s.push_back(v[idx][j]);
            dfs(idx + 1, s);
            s.pop_back();
        }
    }
}


int solution(vector<string> user_id, vector<string> banned_id) {
    int answer = 0;

    N = banned_id.size();

    //banned_id에 매핑되는 후보들을 v에 저장한다.
    for (int i = 0; i < banned_id.size(); ++i) {
        vector<string> tmp;
        for (int j = 0; j < user_id.size(); ++j) {
            //user_id와 banned_id가 매핑되면 v에 저장
            if (same(banned_id[i], user_id[j])) {
                tmp.push_back(user_id[j]);
            }

        }
        v.push_back(tmp);
    }

    vector<string> cand;
    dfs(0, cand);

    //m의 크기가 전체 경우의 수
    answer = m.size();

    return answer;
}




//다른 사람 풀이
/*
후보군을 굳이 뽑지 않아도 된다.
used배열을 선언한 후 일치하는 아이디는 true로 만들어준다.
바로 dfs를 실행해서 일치하는 아이디를 
*/
#include <bits/stdc++.h>
using namespace std;
bool used[10];
int ret = 0;
set<string> S;

//후보에 맞는 아이디인지 비교
bool possi(string a, string b) {
    if (a.length() != b.length())
        return false;
    for (int i = 0; i < a.length(); i++)
        if (a[i] != b[i] && b[i] != '*')
            return false;
    return true;
}

void dfs(int p, vector<string> user_id, vector<string> banned_id) {
    //사이즈가 같다면
    if (p == banned_id.size()) {
        string tmp;
        //used[i]=true인 인덱스를 tmp에 저장
        //단어를 저장하지 않아도 된다.
        for (int i = 0; i < user_id.size(); i++)
            if (used[i]) tmp += i + '0';
        //S에 있으면 리턴, 없으면 추가
        if (S.find(tmp) != S.end())
            return;
        S.insert(tmp);
        ret++;
        return;
    }
    //방문하지 않았고 일치하는 아이디이면 백트래킹
    for (int i = 0; i < user_id.size(); i++)
        if (!used[i] && possi(user_id[i], banned_id[p]))
            used[i] = true, dfs(p + 1, user_id, banned_id), used[i] = false;
}

int solution(vector<string> user_id, vector<string> banned_id) {
    dfs(0, user_id, banned_id);
    return ret;
}