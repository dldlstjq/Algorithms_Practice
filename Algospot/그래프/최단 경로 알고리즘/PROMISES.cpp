/*
기존 플로이드 알고리즘을 적용한 후 새로운 간선이 의미 있는지
검사한다. 의미 여부를 확인하는 것 자체는 간단한데 
응용하기 위해서는 많은 문제를 풀어보며 익혀야 할 것 같다.

책에 있는 코드는 오답이 나오고 블로그에 있는 답은 정답이 나왔다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

const int INF = 1000000000;
const int MAX_V = 200 + 2;

//정점의 개수, 간선 개수
int V, M, N;

//그래프의 인접 행렬 표현.
//adj[u][v]=u에서 v로 가는 간선의 가중치. 간선이 없으면 아주 큰 값을 넣는다.
int adj[MAX_V][MAX_V];

void floyd() {
    for (int i = 0; i < V; ++i)
        adj[i][i] = 0;

    for (int k = 0; k < V; ++k)
        for (int i = 0; i < V; ++i)
            for (int j = 0; j < V; ++j)
                adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);

}

//간선 (a,b)를 추가했을 때 그래프의 최단 거리 배열 adj를
//적절히 갱신한다. 간선이 아무런 의미가 없을 경우 false를
//반환한다.
bool update(int a, int b, int c) {
    if (adj[a][b] <= c)
        return false;

    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            //i~j최단경로가 (a,b)를 이용하려면
            //i~a-b~j 혹은 i~b-a~j의 형태를 가져야 한다.
            adj[i][j] = min(adj[i][j],
                min(adj[i][a] + c + adj[b][j],
                    adj[i][b] + c + adj[a][j]));
        }
    }
    return true;
}



int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        cin >> V >> M >> N;

        //초기화
        for (int i = 0; i < V; ++i)
            for (int j = 0; j < V; ++j)
                adj[i][j] = INF;

        for (int i = 0; i < M; ++i) {
            int a, b, c;
            cin >> a >> b >> c;
            adj[a][b] = c;
            adj[b][a] = c;
        }
        floyd();
        int cnt = 0;
        for (int i = 0; i < N; ++i) {
            int a, b, c;
            cin >> a >> b >> c;
            if (!update(a, b, c))
                cnt++;
        }
        cout << cnt << "\n";
    }

    return 0;
}


/////////////////////////////////////////////
#include <iostream>
#include <vector>
using namespace std;

#define INF 100000000

int V, M, N;
int ans;
vector<vector<int>> adj;

void init()
{
    ans = 0;
    cin >> V >> N >> M;
    adj = vector<vector<int>>(V, vector<int>(V, INF));
    for (int i = 0; i < V; ++i)
        adj[i][i] = 0;
    int x, y, r;
    for (int i = 0; i < N; ++i)
    {
        cin >> x >> y >> r;
        if (adj[x][y] > r)
            adj[x][y] = adj[y][x] = r;
    }

    for (int k = 0; k < V; ++k)
        for (int i = 0; i < V; ++i)
            for (int j = 0; j < V; ++j)
                adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
}

void build()
{
    int x, y, r;
    cin >> x >> y >> r;
    if (adj[x][y] <= r)
    {
        ++ans;
        return;
    }
    for (int i = 0; i < V; ++i)
        for (int j = 0; j < V; ++j)
            adj[i][j] = min(adj[i][j], min(adj[i][x] + r + adj[y][j], adj[i][y] + r + adj[x][j]));
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    int C;
    cin >> C;
    for (int tn = 0; tn < C; ++tn)
    {
        init();
        for (int i = 0; i < M; ++i)
            build();
        cout << ans << "\n";
    }
}
