/*
이분그래프란?
인접한 정점끼리는 서로 다른 색으로 칠해져야 함.
자세한건 블로그 참고

처음엔 빨강 그 다음은 파랑 넣어서 인접한 것 끼리 색깔이 다르면 이분그래프, 같으면 이분 그래프 아님
*/

#include <iostream>
#include <vector>

using namespace std;

vector<int> G[20001];
int color[20001];      //1일때는 빨강, 2일때는 파랑, 0일때는 접근X

void DFS(int node, int c) {
    color[node] = c;
    for (int i = 0; i < G[node].size(); i++) {
        int next = G[node][i];
        if (color[next] == 0) {
            DFS(next, 3 - c); //빨강 다음에는 파랑이여야하고 파랑 다음은 빨강이여야 함.
                            //따락서 3-1 = 2, 3-2 = 1
        }
    }
}
int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        //초기화
        for (int i = 1; i <= n; i++) {
            G[i].clear();
            color[i] = 0;
        }

        //데이터 입력
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            G[u].push_back(v);
            G[v].push_back(u);
        }

        //모든 정점 돌면서 방문 안했으면 dfs 실행.
        for (int i = 1; i <= n; i++) {
            if (color[i] == 0) {
                DFS(i, 1);
            }
        }

        //그래프 돌면서 인접한것끼리 같은 색이면 이분그래프 아님
        bool isBin = true;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < G[i].size(); j++) {
                int k = G[i][j];
                if (color[i] == color[k])
                    isBin = false;
            }
        }
        if (isBin)
            cout << "YES" << "\n";
        else
            cout << "NO" << "\n";
    }
    return 0;
}