﻿/*
SAT 문제 중 2-SAT라는 방법을 사용해야 하는 문제.
SAT라는 것 자체가 생소한데다 개념까지 어렵다 보니 
무슨 말인지 이해가 잘 안된다.
문제도 예제문제가 다 IMPOSSIBLE로 떠서 정답이 안나온다.
이것만 보기에는 너무 시간을 끌것 같아 일단은 넘어가고
다시 볼때 좀 더 공부해야겠다.
*/



#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

//그래프의 인접리스트 표현
vector<vector<int>> adj;

//각 정점의 컴포넌트 번호. 컴포넌트 번호는 0부터 시작하며,
//같은 강결합 컴포넌트에 속한 정점들의 컴포넌트 번호가 같다.
vector<int> sccId;
//각 정점의 발견 순서
vector<int> discovered;
//정점의 번호를 담는 스택
stack<int> st;

//결과 저장
vector<vector<int>> result;

int sccCounter, vertexCounter;
//here를 루트로 하는 서브트리에서 역방향 간선이나 교차 간선을
//통해 갈 수 있는 정점 중 최소 발견 순서를 반환한다.
//(이미 SCC로 묶인 정점으로 연결된 교차 간선은 무시한다.)
int scc(int here) {
    int ret = discovered[here] = vertexCounter++;
    //스택에 here를 넣는다. here의 후손들은 모두 스택에서 here 후에 들어간다.
    st.push(here);
    for (int i = 0; i < adj[here].size(); ++i) {
        int there = adj[here][i];
        //(here, there)가 트리 간선
        if (discovered[there] == -1)
            ret = min(ret, scc(there));
        //there가 무시해야 하는 교차 간선이 아니라면
        else if (sccId[there] == -1)
            ret = min(ret, discovered[there]);
    }
    //here에서 부모로 올라가는 간선을 끊어야 할 지 확인한다.
    if (ret == discovered[here]) {
        //here를 루트로 하는 서브트리에 남아 있는 정점들을 전부 하나의 컴포넌트로 묶는다.
        while (true) {
            int t = st.top();
            st.pop();
            sccId[t] = sccCounter;
            if (t == here)
                break;
        }
        ++sccCounter;
    }
    return ret;
}

//tarjan의 SCC 알고리즘
vector<int> tarjanSCC() {
    //배열들을 전부 초기화
    sccId = discovered = vector<int>(adj.size(), -1);
    //카운터 초기화
    sccCounter = vertexCounter = 0;
    //모든 정점에 대해 scc() 호출
    for (int i = 0; i < adj.size(); ++i)
        if (!discovered[i] == -1)
            scc(i);
    return sccId;
}

//두 구간 a와 b가 서로 겹치지 않는지를 확인한다.
bool disjoint(const pair<int, int>& a, const pair<int, int>& b) {
    return a.second <= b.first || b.second <= a.first;
}

//meetings[]가 각 팀이 하고 싶어하는 회의 시간의 목록일 때, 이를
//2-SAT 문제로 변환한 뒤 함의 그래프를 생성한다.
//i번 팀은 meetings[2*i] 혹은 meetings[2*i+1]중 하나 시간에 회의실을 써야 한다.
void makeGraph(const vector <pair<int, int>>& meetings) {
    int vars = meetings.size();
    //그래프는 각 변수마다 두 개의 정점을 갖는다.
    adj.clear(); adj.resize(vars * 2);
    for (int i = 0; i < vars; i += 2) {
        //각 팀은 i번 회의나 j번 회의 둘 중 하나는 해야 한다.
        //(i or j)절을 추가한다.
        int j = i + 1;
        adj[i * 2 + 1].push_back(j * 2); // ~i -> j
        adj[j * 2 + 1].push_back(i * 2); // ~j -> i
        //adj[i * 2].push_back(j * 2 + 1); // i -> ~j
        //adj[j * 2].push_back(i * 2 + 1); // j -> ~i
    }
    for (int i = 0; i < vars; ++i)
        for (int j = 0; j < i; ++j) {
            //i번 회의와 j번 회의가 서로 겹칠 경우
            if (!disjoint(meetings[i], meetings[j])) {
                //i번 회의가 열리지 않거나. j번 회의가 열리지 않아야 한다.
                //(~i or ~j)절을 추가한다.
                adj[i * 2].push_back(j * 2 + 1);    //i=>~j
                adj[j * 2].push_back(i * 2 + 1);    //j=>~i
            }
        }
}

//adj[]에 함의 그래프의 인접 리스트 표현이 주어질 때, 2-SAT 문제의 답을 반환한다.
vector<int> solve2SAT() {
    int n = adj.size() / 2; //변수의 수
    //함의 그래프의 정점들을 강결합 요소별로 묶는다.
    vector<int> label = tarjanSCC();
    //이 SAT 문제를 푸는 것이 불가능인지 확인한다. 한 변수를 나타내는 두 정점이
    //같은 강결합 요소에 속해 있을 경우 답이 없다.
    for (int i = 0; i < 2 * n; i += 2)
        if (label[i] == label[i + 1])
            return vector<int>();
    //SAT문제를 푸는 것이 가능하다. 답을 생성하자!
    vector<int> value(2 * n, -1);
    //Tarjan 알고리즘에서 SCC 번호는 위상 정렬의 역순으로 배정된다.
    //SCC 번호의 역순으로 각 정점을 정렬하면 위상 정렬 순서가 된다.
    vector<pair<int, int>> order;
    for (int i = 0; i < 2 * n; ++i)
        order.push_back(make_pair(-label[i], i));
    sort(order.begin(), order.end());
    //각 정점에 값을 배정한다.
    for (int i = 0; i < 2 * n; ++i) {
        int vertex = order[i].second;
        int variable = vertex / 2, isTrue = vertex % 2 == 0;
        if (value[variable] != -1)
            continue;
        //not A가 A보다 먼저 나왔으면 A는 참
        //A가 not A보다 먼저 나왔으면 A는 거짓
        value[variable] = !isTrue;
    }
    return value;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int c;
    cin >> c;
    while (c--) {
        int n;
        cin >> n;
        vector<pair<int, int> > meetings(2 * n);
        for (int i = 0; i < n; ++i) {
            int a, b, c, d;
            cin >> a >> b >> c >> d;
            meetings[2 * i] = make_pair(a, b);
            meetings[2 * i + 1] = make_pair(c, d);
        }
        makeGraph(meetings);
        vector<int> ret = solve2SAT();

        if (ret.empty())
        {
            cout << "IMPOSSIBLE" << "\n";
            continue;
        }
        cout << "POSSIBLE" << "\n";
        for (int i = 0; i < n * 2; ++i)
            if (ret[i])
                cout << meetings[i].first << " " << meetings[i].second << "\n";
    }

    return 0;
}

