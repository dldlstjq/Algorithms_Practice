/*
풀이에 1시간 가까이 걸린 것 같다. 
문제 해석에 어려움을 겪었는데 튜플이 하나인 것이 가장 먼저 나오고
그 다음 크기순으로 하나씩 연결하면 정답이 나왔다.

1. s에 저장된 집합을 분리해서 2차원 배열에 저장한다.
ex) 2
    2 1
    2 1 3 
    2 1 3 4

2. 각 배열의 크기와 인덱스를 페어로 저장한다.
3. 배열의 크기가 작은 순으로 정렬한다.
4. 각 원소가 answer에 있는지 검사해서 없으면 하나씩 넣는다.

총 4가지 단계를 거쳐 코드를 구현했다.
1번 과정에서 시간이 많이 걸렸다. {}와 , 를 어떻게 처리할 것인지가 관건이었다.
그 뒤로는 그나마 쉽게 해결했다.
다른 사람은 어떻게 풀었는가 봤는데 신세계였다...
*/

//내 풀이
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

//이 부분을 넣으면 sort 하나로 다 해결가능하다.
//굳이 배열 크기랑 인덱스를 따로 구할 필요가 없다.
bool comp(vector<int> a, vector<int> b) {
    return a.size() < b.size();
}
//answer에 들어갈 숫자 확인
#define MAXN 100001
bool visited[MAXN];

vector<int> solution(string s) {
    vector<int> answer;

    stack<char> st;
    vector<vector<int>> v;


    vector<int> num;
    string tmp = "";

    //수열을 감싸고 있는 {}를 제외하고 시작한다.
    for (int i = 1; i < s.length() - 1; ++i) {
        //여는 괄호면 스택에 푸시
        if (s[i] == '{') {
            st.push(s[i]);
            continue;
        }

        //쉼표인 경우 스택에 {이 있으면 숫자를 num에 넣고, 없으면 다음 수열을 확인한다.
        else if (s[i] == ',') {
            if (st.empty())
                continue;
            else {
                num.push_back(stoi(tmp));
                tmp = "";
            }

        }
        //닫는 괄호이면 tmp에 있는 숫자를 num에 넣고 최종 수열인 num을 다시 v에 넣고 초기화해준다.
        else if (s[i] == '}') {
            num.push_back(stoi(tmp));
            v.push_back(num);
            num.clear();
            tmp = "";
            st.pop();
        }
        //숫자이면 tmp에 저장한다.
        else {
            tmp += s[i];
        }
    }

    //이렇게 하면 밑의 과정을 안거치고 한방에 정렬 가능.
    sort(v.begin(), v.end(), comp);


    //집합의 크기와 인덱스를 페어로 저장한다.
    vector<pair<int, int>> tuple_size;
    for (int i = 0; i < v.size(); ++i) {
        tuple_size.push_back({ v[i].size(), i });
    }
    //집합의 크기가 작은 순으로 오름차순으로 정렬. 그러면 집합의 크기순으로 인덱스 정렬된다.
    sort(tuple_size.begin(), tuple_size.end());


    //집합의 크기가 작은 인덱스 순서로 idx에 저장
    //idx에는 집합의 크기가 작은 순서인 인덱스가 저장되어 있다.
    vector<int> idx;
    for (int i = 0; i < tuple_size.size(); ++i)
        idx.push_back(tuple_size[i].second);


    //answer 검사 부분인데 find를 쓰지 않고 visited 배열을 선언해서
    //flase인 숫자를 answer에 넣으면 더 쉽게 구현이 가능하다.
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < nvum[i].size(); j++) {
            if (!visited[v[i][j]]) {
                visited[v[i][j]] = true;
                answer.push_back(v[i][j]);
            }
        }
    }

    //원래 내 풀이
    for (int i = 0; i < idx.size(); ++i) {
        //숫자 하나 있는게 제일 앞에 나온다.
        //그 다음 크기 순으로 검사해서 없는 숫자를 answer에 넣으면 튜플 완성
        int k = idx[i];
        for (int j = 0; j < v[k].size(); ++j) {
            if (find(answer.begin(), answer.end(), v[k][j]) == answer.end())
                answer.push_back(v[k][j]);
        }

    }


    return answer;
}


//다른 사람 풀이
/*
각 집합마다 가장 많이 나온 숫자 순으로 answer에 넣으면 정답이 나온다.
*/
#include <bits/stdc++.h>
using namespace std;

vector<int> solution(string s) {
    //튜플의 원소는  1 이상 100,000 이하인 자연수
    int st[101010] = {};
    vector<int> answer;
    string tmp;
    for (char i : s) {
        if (i - '0' >= 0 && i - '0' <= 9) {
            tmp += i;
        }
        else {
            //해당하는 수를 카운트
            if (tmp.length())
                st[stoi(tmp)]++, tmp.clear();
        }
    }
    //카운트된 수와 인덱스 페어로 저장
    vector<pair<int, int>> v;
    for (int i = 0; i < 101010; i++)
        if (st[i])
            v.push_back({ st[i], i });
    //정렬해서 뒤집으면 v의 second가 튜플이 완성된다.
    sort(v.begin(), v.end());
    reverse(v.begin(), v.end());
    for (auto it : v) answer.push_back(it.second);
    return answer;
}
