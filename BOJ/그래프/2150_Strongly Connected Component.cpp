/*
강한 결합 요소(SCC)를 구현하는 문제.
종만북에는 응용문제만 있어 백준에서 기본적인 문제를 익혔다.

처음 중간에 정답을 저장하는 ans 벡터를 전역으로 선언해 정답이 누적되는 것을
몰라 계속 오답이 나왔다.
다소 어려운 개념이어서 많은 공부가 필요한 것 같고 dfs의 이용이 이렇게 응용되는 줄
몰랐는데 이번에 알게 됐다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <stack>

using namespace std;


//그래프의 인접 리스트 표현
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
        vector<int> ans;
        //here를 루트로 하는 서브트리에 남아 있는 정점들을 전부 하나의 컴포넌트로 묶는다.
        while (true) {
            int t = st.top();
            st.pop();
            sccId[t] = sccCounter;
            ans.push_back(t);
            if (t == here)
                break;
        }
        ++sccCounter;
        //출력위해 정렬
        sort(ans.begin(), ans.end());
        result.push_back(ans);

    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int v, e;
    cin >> v >> e;
    //adj.resize(e);
    adj = vector<vector<int>>(e);
    for (int i = 0; i < e; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a - 1].push_back(b - 1);
    }
    //배열들을 전부 초기화
    sccId = discovered = vector<int>(adj.size(), -1);
    //카운터 초기화
    sccCounter = vertexCounter = 0;
    //모든 정점에 대해 scc() 호출
    for (int i = 0; i < v; ++i)
        if (discovered[i] == -1)
            scc(i);

    sort(result.begin(), result.end());
    cout << sccCounter << "\n";
    for (int i = 0; i < result.size(); ++i) {
        for (int j = 0; j < result[i].size(); ++j) {
            cout << result[i][j] + 1 << " ";
        }
        cout << -1 << "\n";
    }

    return 0;
}

