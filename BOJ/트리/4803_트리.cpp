/*
첫 풀이는 dfs를 돌면서 사이클이 있는지 여부만 확인하였다.
그러더니 20%언저리에서 틀렸습니다를 받았다.

생각보다 많은 시간을 쓴 것 같아 다른 사람의 풀이를 보니
노드를 입력 받을때 간선을 양쪽 다 이어줘야 하고
트리의 성질인 정점이 n개면 간선이 n-1개라는 점을 이용해야 한다.
그리고 간선의 개수를 구할 때 양쪽 다 이어지게 했기 때문에 마지막에
2를 나눠줘야 정확한 간선의 개수가 나온다.

루트가 어딘지 언급이 안됐기 때문에 노드 양쪽을 간선으로 이어주는 것 같다.
*/

#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int MAX = 501;
bool visited[MAX];
bool passed[MAX]; //간선 지나갔는지 여부
vector<int> v[MAX];

//dfs를 통해 정점 개수 파악
int numOfVertex(int num) {
	int cnt = 1;
	visited[num] = true;
	for (int i = 0; i < v[num].size(); ++i) {
		int next = v[num][i];
		if (!visited[next])
			cnt += numOfVertex(next);
	}
	return cnt;
}

//dfs를 통해 간선 개수 파악
//정점 입력 시 두 번 입력하므로 여기서 구한 개수는 실제의 2배
int numOfEdge(int num) {
	int cnt = v[num].size();
	passed[num] = 1;

	for (int i = 0; i < v[num].size(); ++i) {
		int next = v[num][i];
		if (!passed[next])
			cnt += numOfEdge(next);
	}
	return cnt;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m;
	int flag = 1;
	while (cin >> n >> m) {
		if (n == 0 && m == 0)
			break;

		//초기화
		memset(visited, 0, sizeof(visited));
		memset(passed, 0, sizeof(passed));
		for (int i = 0; i < MAX; ++i)
			v[i].clear();

		for (int i = 0; i < m; ++i) {
			int a, b;
			cin >> a >> b;
			v[a].push_back(b);
			v[b].push_back(a);
		}

		int cnt = 0;
		for (int i = 1; i <= n; ++i) {
			if (!visited[i]) {
				int vertex = numOfVertex(i);
				int edge = numOfEdge(i);
				if (vertex - 1 == edge / 2)
					cnt++;
			}
		}

		cout << "Case " << flag++ << ": ";
		if (cnt == 1)
			cout << "There is one tree.\n";
		else if (cnt > 1)
			cout << "A forest of " << cnt << " trees.\n";
		else
			cout << "No trees.\n";
	}
	return 0;
}