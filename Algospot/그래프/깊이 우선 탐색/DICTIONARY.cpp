/*
단순한 dfs 문제일줄 알고 쉽게 생각했는데 위상정렬문제였다.
위상정렬을 구하는 방법에 dfs를 사용하는 것이었는데
위상정렬 자체가 생소해 문제 접근에 어려움을 겪었다.
생소한 개념이 나올때는 백준문제를 한두개씩 풀어보면서 감을 익히는 방향이 좋을 것 같다.
*/


#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

//알파벳의 각 글자에 대한 인접 행렬 표현
//간선 (i,j)는 알파벳 i가 j보다 앞에 와야 함을 나타낸다.
vector<vector<int>> adj;
//seen은 방문 여부를 확인, order는 위상정렬을 저장한다.
vector<int> seen, order;

//주어진 단어들로부터 알파벳 간의 선후관계 그래프를 생성한다.
void makeGraph(const vector<string>& words) {
    adj = vector<vector<int>>(26, vector<int>(26, 0));
    for (int j = 1; j < words.size(); j++) {
        int i = j - 1, len = min(words[i].size(), words[j].size());
        //word[i]가 word[j]앞에 오는 이유를 찾는다.
        for (int k = 0; k < len; ++k)
            if (words[i][k] != words[j][k]) {
                int a = words[i][k] - 'a';
                int b = words[j][k] - 'a';
                adj[a][b] = 1;
                break;
            }
    }
}

//깊이 우선 탐색을 구현한다.
void dfs(int here) {
    seen[here] = 1;
    //모든 인접 정점을 순회하면서
    for (int there = 0; there < adj[here].size(); ++there) {
        if (adj[here][there] && !seen[there])
            dfs(there);
    }
    order.push_back(here);
}

//adj에 주어진 그래프를 위상정렬한 결과를 반환한다.
//그래프가 DAG가 아니라면 빈 벡터를 반환한다.
vector<int> topologicalSort() {
    int m = adj.size();
    seen = vector<int>(m, 0);
    order.clear();
    for (int i = 0; i < m; ++i)
        if (!seen[i])
            dfs(i);
    reverse(order.begin(), order.end());
    //만약 그래프가 DAG가 아니라면 정렬 결과에 역방향 간선이 있다.
    for (int i = 0; i < m; ++i)
        for (int j = i + 1; j < m; ++j)
            if (adj[order[j]][order[i]])
                return vector<int>();
    //없는 경우라면 깊이 우선 탐색에서 얻은 순서를 반환한다.
    return order;
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int c;
    cin >> c;
    while (c--) {
        int n;
        cin >> n;
        vector<string> words;
        for (int i = 0; i < n; ++i) {
            string s;
            cin >> s;
            words.push_back(s);
        }
        makeGraph(words);
        vector<int> ret = topologicalSort();

        if (ret.empty())
            cout << "INVALID HYPOTHESIS";
        else
            for (int i = 0; i < ret.size(); ++i)
                cout << char(ret[i] + 'a');
        cout << "\n";
    }

    return 0;
}




//////////////////////////////////
//큐를 이용한 풀이인데 오답으로 나왔다. 나중에 다시 생각하기.
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

//알파벳의 각 글자에 대한 인접 행렬 표현
//간선 (i,j)는 알파벳 i가 j보다 앞에 와야 함을 나타낸다.
vector<vector<int>> adj;
//seen은 방문 여부를 확인, order는 위상정렬을 저장한다.
vector<int> seen, order;
//해당 정점에 들어오는 간선의 수
vector<int> indegree;

//주어진 단어들로부터 알파벳 간의 선후관계 그래프를 생성한다.
void makeGraph(const vector<string>& words) {
    adj = vector<vector<int>>(26, vector<int>(26, 0));
    indegree = vector<int>(26, 0);
    for (int j = 1; j < words.size(); j++) {
        int i = j - 1, len = min(words[i].size(), words[j].size());
        //word[i]가 word[j]앞에 오는 이유를 찾는다.
        for (int k = 0; k < len; ++k)
            if (words[i][k] != words[j][k]) {
                int a = words[i][k] - 'a';
                int b = words[j][k] - 'a';
                adj[a][b] = 1;
                //특정 정점에서 특정 정점으로의 간선은 하나만 존재가능.
                //중복을 막기위해 간선 개수가 0일때만 증가
                if (indegree[b] == 0)
                    indegree[b]++;
                break;
            }
    }
}

//깊이 우선 탐색을 구현한다.
void dfs(int here) {
    seen[here] = 1;
    //모든 인접 정점을 순회하면서
    for (int there = 0; there < adj[here].size(); ++there) {
        if (adj[here][there] && !seen[there])
            dfs(there);
    }
    order.push_back(here);
}

//adj에 주어진 그래프를 위상정렬한 결과를 반환한다.
//그래프가 DAG가 아니라면 빈 벡터를 반환한다.
vector<int> topologicalSort() {
    int m = adj.size();
    seen = vector<int>(m, 0);
    order.clear();
    for (int i = 0; i < m; ++i)
        if (!seen[i])
            dfs(i);
    reverse(order.begin(), order.end());
    //만약 그래프가 DAG가 아니라면 정렬 결과에 역방향 간선이 있다.
    for (int i = 0; i < m; ++i)
        for (int j = i + 1; j < m; ++j)
            if (adj[order[j]][order[i]])
                return vector<int>();
    //없는 경우라면 깊이 우선 탐색에서 얻은 순서를 반환한다.
    return order;
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int c;
    cin >> c;
    while (c--) {
        int n;
        cin >> n;
        vector<string> words;

        for (int i = 0; i < n; ++i) {
            string s;
            cin >> s;
            words.push_back(s);
        }
        makeGraph(words);

        //큐를 이용한 위상정렬
        queue<int> q;
        //정답 저장
        vector<int> ret;
        //사이클 여부
        bool cycle = false;

        for (int i = 0; i < 26; ++i) {
            if (indegree[i] == 0)
                q.push(i);
        }

        for (int i = 0; i < 26; ++i) {
            if (q.empty()) {
                cycle = true;
                break;

            }
            int cur = q.front();
            ret.push_back(cur);
            q.pop();
            //26개의 알파벳 모두를 고려해야하므로
            //next가 1이면 cur와 j가 연결된것을 의미하므로 j의 간선을 감소시킨다.
            for (int j = 0; j < adj[cur].size(); ++j) {
                int next = adj[cur][j];
                if (next == 0)
                    continue;
                indegree[j]--;
                if (indegree[j] == 0)
                    q.push(j);
            }
        }

        if (cycle)
            cout << "INVALID HYPOTHESIS";

        else
            for (int i = 0; i < ret.size(); ++i)
                cout << char(ret[i] + 'a');

        cout << "\n";
        /*vector<int> ret = topologicalSort();

        if (ret.empty())
            cout << "INVALID HYPOTHESIS";
        else
            for (int i = 0; i < ret.size(); ++i)
                cout << char(ret[i] + 'a');
        cout << "\n";*/
    }

    return 0;
}

