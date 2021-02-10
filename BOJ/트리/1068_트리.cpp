/*
2차원 벡터에 트리를 저장한다.
그 다음 dfs를 돌면서 삭제할 노드를 찾은 후 해당 노드를 삭제한다.
리프노드를 구할 때 역시 dfs를 사용해 해당 인덱스의 벡터가 비었으면 리프노드인 것으로 해서 구했다.

다른사람들의 풀이를 보니 dfs를 한번만 활용하여 리프노드를 구했다.
*/

//내 풀이
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAX = 50;
vector<int> tree[MAX];
bool visited[MAX];
int cnt;
bool go = true;

void findNode(int num, int goal) {
	visited[num] = true;

	//삭제했다면 더 진행하지 않아도 된다.
	if (go) {
		for (int i = 0; i < tree[num].size(); ++i) {
			int next = tree[num][i];
			//next에 해당하는 노드가 삭제할 노드라면 삭제한다.
			if (next == goal) {
				tree[num].erase(tree[num].begin() + i, tree[num].begin() + (i + 1));
				go = false;
			}
			else
				findNode(next, goal);
		}
	}

}

//리프노드 갯수를 구한다.
void dfs(int num) {
	visited[num] = true;

	if (tree[num].size() == 0)
		cnt++;
	else {
		for (int i = 0; i < tree[num].size(); ++i) {
			int next = tree[num][i];
			if (!visited[next])
				dfs(next);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, root = 0;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		int node;
		cin >> node;
		if (node == -1)
			root = i;
		else
			tree[node].push_back(i);
	}

	for (int i = 0; i < MAX; ++i)
		sort(tree[i].begin(), tree[i].end());

	int remove = 0;
	cin >> remove;

	//삭제할 노드가 루트면 리프노드가 없다.
	if (root == remove) {
		cout << 0;
		return 0;
	}
	else
		findNode(root, remove);

	//findNode에서 visited가 사용되기 때문에 dfs사용을 위해 초기화
	memset(visited, false, sizeof(visited));
	dfs(root);
	cout << cnt;

	return 0;
}


//다른 사람 풀이
#include <iostream>
#include <algorithm>
#include <vector>
#pragma warning(disable:4996)
using namespace std;
#define MAX 50 + 1
// global
vector<vector<int>> child_vec;
int answer = 0, del_node;

// 자식 노드를 dfs를 이용하여 센다.
// 자식 노드가 1개 있으면, 해당 노드가 삭제할 노드인지 확인한다.
void how_many_leaf(int now_node) {
	if (del_node == now_node) return;
	int ch_size = child_vec[now_node].size();
	switch (ch_size) {
	case 0:
		answer++; return;
		break;
	case 1:
		if (child_vec[now_node][0] == del_node) {
			answer++; break;
		}
	default:
		for (int ch_idx = 0; ch_idx < ch_size; ch_idx++)
			how_many_leaf(child_vec[now_node][ch_idx]);
		break;
	}
}

int main() {
	// input 받아서 루트, 부모, 자식 처리하기 
	int N, root; scanf("%d", &N);
	child_vec.resize(N);

	for (int in_idx = 0; in_idx < N; in_idx++) {
		int parent; scanf("%d", &parent);
		if (parent != -1) child_vec[parent].push_back(in_idx);
		else root = in_idx;
	}

	scanf("%d", &del_node);
	how_many_leaf(root);
	printf("%d", answer);
	return 0;
}
