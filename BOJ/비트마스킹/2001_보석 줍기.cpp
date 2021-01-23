/*
몇시간을 고민했는데 결국 해결하지 못했다.
BFS로 접근하여 해당 섬에서 보석을 가져간 경우와 가져가지 않은 경우
총 두개를 큐에 넣고 실행했다.
하지만 다리 무게를 초과한 경우와 1번 섬으로 다시 돌아오는 경우를
제외하고는 큐에 계속 원소가 쌓여서 종료가 되지 않았다.

구글링을 통해 힌트를 얻어 보석을 한 번 가져간 섬은 다시 방문하지 않는 방법을 시도했는데
아예 보석을 가져가지 않은 경우는 계속 반복되서 큐에 들어가
마찬가지로 종료가 되지 않았다.

정답을 맞은 코드를 보니 DFS를 이용하여 가져간 보석은 표시해서 
보석을 가져가지 않은 섬만 가도록 구현했다.
*/

#include <iostream>
#include <vector>
using namespace std;

int n, m, K, answer = 0, jew[101] = { 0, };
bool memo[101][32768] = { false, };

struct MyPair { int vertex, capacity;	MyPair(int n, int c) : vertex(n), capacity(c) {} };
vector<MyPair> graph[101];

void DFS(int curr, int bit, int cnt)
{
	if (curr == 1 && answer < cnt) answer = cnt;
	memo[curr][bit] = true;

	for (auto& next : graph[curr])
	{
		if (next.capacity < cnt) continue;
		if (!memo[next.vertex][bit]) DFS(next.vertex, bit, cnt);


		if (jew[curr])
		{
			if (next.capacity < cnt + 1) continue;
			if (!memo[next.vertex][bit | (1 << jew[curr])]) DFS(next.vertex, bit | (1 << jew[curr]), cnt + 1);
		}
	}
}


int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	cin >> n >> m >> K;
	{
		int from, to, temp, jewCnt = 1;
		for (int i = 0; i < K; i++)
		{
			cin >> temp;
			jew[temp] = jewCnt++;
		}
		for (int i = 0; i < m; i++)
		{
			cin >> from >> to >> temp;
			graph[from].push_back({ to, temp });
			graph[to].push_back({ from, temp });
		}
		graph[1].push_back({ 1, 14 });
	}

	DFS(1, 0, 0);
	cout << answer << '\n';

	return 0;
}


///////////////////////
//처음 생각한 풀이
const int MAX = 101;
int n, m, k;
int island[MAX][MAX];

bool is_jewel[MAX];
//같은 보석을 들고 같은 섬을 다시 방문하는지 여부
bool visited[MAX][1 << 15];


int bitCount(int x) {
	if (x == 0)return 0;
	return x % 2 + bitCount(x / 2);
}

int solve() {
	queue<pair<int, int>> q;	//정점 번호, 보석 종류, 보석 챙긴 여부
	q.push({ 1,0 });
	int ret = 0;
	bool start = true;
	while (!q.empty()) {
		int now = q.front().first;	//정점 번호
		int jewel = q.front().second;	//보석 개수

		int weight = bitCount(jewel);
		q.pop();

		//현재 정점이 1일때 최대 무게를 ret에 저장
		if (now == 1) {
			ret = max(ret, weight);
			if (!start)
				continue;
		}
		start = false;

		for (int i = 1; i <= n; ++i) {
			//다리가 연결되어 있고 무게를 견딜 수 있을때
			if (island[now][i] != 0 && weight <= island[now][i]) {
				//보석이 있는 섬이고 해당 보석을 안 챙긴 경우
				if (is_jewel[i] && !visited[i][1 << i]) {
					int add = jewel | (1 << i);
					q.push({ i, add });	//보석을 챙긴다.
					visited[i][1 << i] = true;	//보석 챙긴거 확인
					q.push({ i,jewel });	//보석 안 챙김
					visited[i][jewel] = true;
				}
				//보석이 없을 때
				else {
					q.push({ i, jewel });
				}

			}
		}
	}
	return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	//memset(cache, -1, sizeof(cache));

	cin >> n >> m >> k;
	for (int i = 0; i < k; ++i) {
		int tmp;
		cin >> tmp;
		is_jewel[tmp] = true;
	}

	//해당 다리의 무게를 원소로 넣어줌
	//0이면 두 섬을 잇는 다리가 없다.
	for (int i = 0; i < m; ++i) {
		int a, b, c;
		cin >> a >> b >> c;
		island[a][b] = island[b][a] = c;
	}
	cout << solve();
	return 0;
}