/*
dfs를 이용하여 간단히 구현
원하는 번호와 같은 숫자면 ret 갱신
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
int p1, p2;
int m;
vector<int> v[101];
bool visited[101];  //각 번호 방문 여부
int ret = -1;    //기본은 -1

void solve(int start, int cnt) {
    //방문 표시
    visited[start] = true;
    //원하는 번호와 같으면 ret에 cnt 저장후 종료
    if (start == p2) {
        ret = max(ret, cnt);
        return;
    }

    for (int i = 0; i < v[start].size(); ++i) {
        //방문하지 않았으면 방문.
        if (!visited[v[start][i]]) {
            solve(v[start][i], cnt + 1);
        }

    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    cin >> p1 >> p2;
    cin >> m;

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        v[a].push_back(b);
        v[b].push_back(a);
    }

    solve(p1, 0);

    cout << ret;
    return 0;
}