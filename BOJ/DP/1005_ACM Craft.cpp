/*
건물 짓는 순서가 정해져 있어 처음에는 위상정렬을 해서 구해야 하는걸로 생각했다.
하지만 특정 건물을 짓는데 필요한 시간을 구해야 해서 위상정렬을 사용하는게
힘들어 보였고 이래저래 생각해봤는데 딱히 생각이 나지 않았다.
못풀겠어서 검색해보니 코드가 생각보다 간단했다.
건물 짓는 조건을 하나씩 다 탐색하면서 제일 시간이 오래 걸리는 것을
선택해서 건설 시간과 더해 값을 구하면 되는 거였다.
*/

// 2021.06.02 dp와 위상정렬 관련 문제인 것 같은데 풀이가 딱히 생각나지 않았다.
// 오래 안풀다 풀려고 하니 생각이 잘 안난다.

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int N, K;	//건물 수, 건설순서규칙
int time[1001];	//건물 건설 시간
int X, Y;	//건설 순서 (X다음 Y건설 가능)
int W;	//건설해야할 건물 번호
int order[1001][1001];	//건물 짓는 조건
int cache[1001];

//k는 건물번호, t는 건설시간
int solve(int dest) {
	int& ret = cache[dest];
	if (ret != -1)return ret;
	int t = 0;
	//건물 조건을 탐색한다.
	for (int i = 1; i <= N; ++i)
		if (order[i][dest])
			//dest를 만들기 전 동시에 만들 건물 중 제일 시간 오래 걸리는 건물
			t = max(t, solve(i));
	ret = t + time[dest];
	return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int c;
	cin >> c;
	while (c--) {
		memset(cache, -1, sizeof(cache));
		memset(order, 0, sizeof(order));
		cin >> N >> K;
		for (int i = 1; i <= N; ++i)
			cin >> time[i];

		for (int i = 0; i < K; ++i) {
			int a, b;
			cin >> a >> b;
			order[a][b] = 1;

		}
		cin >> W;
		cout << solve(W) << "\n";
	}

	return 0;
}


///////////////////////////////////////
/*
위상 정렬 풀이.
1516-게임 개발 문제와 거의 비슷하다.
핵심은 더 오래 걸리는 건물 시간을 더해 답을 구하면 된다.
처음엔 ret 변수 하나로 계산하려 했는데 이전 건물 시간을 가져올 방법이 없었다.
그래서 ret 배열을 선언해 DP처럼 풀이를 했다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;

const int MAX = 1001;
vector<int> adj[MAX];
int time[MAX];
int indegree[MAX];
int ret[MAX];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        //초기화
        for (int i = 0; i < MAX; ++i)
            adj[i].clear();
        memset(time, 0, sizeof(time));
        memset(indegree, 0, sizeof(indegree));
        memset(ret, 0, sizeof(ret));

        int n, k;
        cin >> n >> k;
        for (int i = 1; i <= n; ++i) {
            int d;
            cin >> d;
            time[i] = d;
        }

        for (int i = 0; i < k; ++i) {
            int x, y;
            cin >> x >> y;
            adj[x].push_back(y);
            indegree[y]++;
        }
        int goal;
        cin >> goal;

        queue<int> q;
        //indegree가 0인 정점을 큐에 넣고 
        //해당 정점의 건물을 짓는 시간을 인덱스에 맞게 ret에 저장한다.
        for (int i = 1; i <= n; ++i) {
            if (indegree[i] == 0) {
                q.push(i);
                ret[i] = time[i];
            }
        }

        while (!q.empty()) {
            int cur = q.front();

            q.pop();

            for (int i = 0; i < adj[cur].size(); ++i) {
                int next = adj[cur][i];
                //목표건물을 짓기위해 두 가지이상 건물을 지어야 하면
                //그 중 건설시간이 오래 걸리는 건물의 시간을 더해야 한다.
                ret[next] = max(ret[next], ret[cur] + time[next]);
                indegree[next]--;
                if (indegree[next] == 0)
                    q.push(next);
            }
            //현재 정점이 goal이면 종료
            if (cur == goal)
                break;
        }
        //최종 목표 인덱스의 원소가 답
        cout << ret[goal] << "\n";
    }
    return 0;
}