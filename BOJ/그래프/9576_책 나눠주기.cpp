/*
축사배정문제와 크게 다를 것 없다 해서 처음엔 종만북의
이분매칭 코드로 풀었다.
오답이 나와서 a이상 b이하인 책을 고른다고 해서 그 부분을 수정했는데
50%에서 오답이 나왔다.

다른 사람 블로그를 보고 그 방식대로 이분매칭을 구현하니까 정답이 나왔다.
이 코드가 왜 내가 푼 코드와 다르게 정답이 나오는지는 아직 연구가 필요하다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX_N = 1000 + 2;
const int MAX_M = 1000 + 2;
//A와 B의 정점의 개수
int n, m;
//adj[i][j]=Ai와 Bj가 연결되어 있는가?
int adj[MAX_N][MAX_N];
//각 정점에 매칭된 상대 정점의 번호를 저장한다.
int aMatch[MAX_N];
int bMatch[MAX_N];
//dfs()의 방문 여부
int visited[MAX_N];
int visitCnt = 1;

//A의 정점인 a에서 B의 매칭되지 않은 정점으로 가는 경로를 찾는다.
bool dfs(int a) {
    if (visited[a] == visitCnt)
        return false;
    visited[a] = visitCnt;
    for (int i = 1; i <= n; ++i) {
        if (adj[a][i]) {
            int b = adj[a][i];
            //b가 이미 매칭되어 있다면 bMatch[b]에서부터 시작해 증가 경로를 찾는다.
            if (bMatch[b] == -1 || dfs(bMatch[b])) {
                //증가 경로 발견!! a와 b를 매치시킨다.
                aMatch[a] = b;
                bMatch[b] = a;
                return true;
            }
        }
    }

    return false;
}

//aMatch,bMatch 배열을 계산하고 최대 매칭의 크기를 반환한다.
int bipartiteMatch() {
    //처음에는 어떤 정점도 연결되어 있지 않다.
    memset(aMatch, -1, sizeof(aMatch));
    memset(bMatch, -1, sizeof(bMatch));

    int size = 0;
    for (int start = 1; start <= m; ++start) {
        visitCnt++;
        //깊이 우선 탐색을 이용헤 start에서 시작하는 증가 경로를 찾는다.
        if (dfs(start))
            ++size;
    }
    return size;
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        cin >> n >> m;
        memset(adj, 0, sizeof(adj));
        for (int i = 1; i <= m; ++i) {
            int a, b;
            cin >> a >> b;
            for (int j = a; j <= b; ++j)
                adj[i][j] = j;
        }

        cout << bipartiteMatch() << "\n";
    }

    return 0;
}