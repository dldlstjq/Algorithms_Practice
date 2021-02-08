/*
2차원 배열에 트리 저장.
DFS로 순회하며 각 노드의 부모를 구함.
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define MAX 100001
vector<int> tree[MAX];
bool visited[MAX];
int parent[MAX];    //부모노드 저장

void dfs(int num) {
    visited[num] = true;

    for (int i = 0; i < tree[num].size(); i++) {
        int next = tree[num][i];
        if (!visited[next]) {
            //next가 방문 안한곳이면 num이 next의 부모임
            parent[next] = num;
            dfs(next);
        }

    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    int v1, v2;

    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        cin >> v1 >> v2;
        tree[v1].push_back(v2);
        tree[v2].push_back(v1);
    }

    for (int i = 0; i <= n; i++) {
        sort(tree[i].begin(), tree[i].end());
    }

    //루트는 1
    dfs(1);

    for (int i = 2; i <= n; i++)
        cout << parent[i] << "\n";

    return 0;
}