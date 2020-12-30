/*
얼핏 봤을 때 그래프랑 아무 상관없는 문제처럼 보이고
출력또한 특정 숫자로만 구성되야 하기 때문에 어렵게 느껴진다.
자세한 풀이는 책을 참고하면서 보고 이런 문제를 풀려면 
어느정도의 연습과 실력이 필요할까 생각하게 된다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

//현재 정점 번호가 here이라면, 간선 번호 edge를
//따라갔을 때 나오는 정점의 번호는?
int append(int here, int edge, int mod) {
    int there = here * 10 + edge;
    if (there >= mod)
        return mod + there % mod;
    return there % mod;
}

//digits에 속한 숫자들만으로 구성되고,
//C mod n == m인 최소의 C를 찾는다.
string gifts(string digits, int n, int m) {
    //간선의 번호를 오름차순으로 정렬해 두면 사전순으로 가장 앞에
    //있는 경로를 찾을 수 있다.
    sort(digits.begin(), digits.end());
    //흰색 정점 i는 0~n-1, 회색 정점 i는 n~2n-1로 표현한다.
    //parent[i]=BFS 스패닝 트리에서 정점 i의 부모
    //choice[i]=parent[i]에서 i로 연결된 간선의 번호
    vector<int> parent(2 * n, -1), choice(2 * n, -1);
    queue<int> q;
    //흰색 0번을 큐에 추가
    parent[0] = 0;
    q.push(0);
    while (!q.empty()) {
        int here = q.front();
        q.pop();
        for (int i = 0; i < digits.size(); ++i) {
            //간선 digits[i]-'0'을 따라가 본다.
            int there = append(here, digits[i] - '0', n);
            if (parent[there] == -1) {
                parent[there] = here;
                choice[there] = digits[i] - '0';
                q.push(there);
            }
        }
    }
    //회색 m번에 도달하지 못했으면 실패!
    if (parent[n + m] == -1)
        return "IMPOSIBBLE";
    //부모로 가는 연결을 따라가면서 C를 계산한다.
    string ret;
    int here = n + m;
    while (parent[here] != here) {
        ret += char('0' + choice[here]);
        here = parent[here];
    }
    reverse(ret.begin(), ret.end());
    return ret;
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int c;
    cin >> c;
    while (c--) {
        string d;
        int n, m;
        cin >> d >> n >> m;
        cout << gifts(d, n, m) << "\n";
    }

    return 0;
}