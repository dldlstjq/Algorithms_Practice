/*
노드의 위치를 구하는게 어려웠다.
루트를 1로 생각했는데 1이 루트가 아닐 수도 있었다.

따라서 루트가 뭔지 따로 구해야 했고 중위순회 dfs로 노드의 위치를 구해서
값을 계산했다.

알고리즘
1. 트리를 입력 받을 때 pair<int, int>형 배열에 인덱스를 부모로 하고 자식들을 입력받습니다. 부모가 항상 1이 아니기 때문에 
입력받는 노드를 세서 한번만 입력되는 노드를 루트로 정합니다.
2. 중위 순회 DFS를 실행합니다. 이 때, 해당 높이에서 제일 좌측에 있는 노드와 제일 우측에 있는 노드를 업데이트합니다.
3. 각 레벨을 탐색하면서 제일 긴 길이를 구하고 해당 높이와 길이를 출력합니다.

주의할 점은, 1번에서도 언급했듯이 1번 노드가 항상 루트가 아니라는 점입니다!

*/

#include <iostream>
#include <algorithm>
using namespace std;

const int MAX = 10001;
const int INF = 987654321;

int n, nodeIdx;	//n과 노드의 위치
pair<int, int> tree[MAX];
int low[MAX];
int high[MAX];
int node[MAX];

//Inorder Traversal(중위 순회)
void DFS(int nodeNum, int cnt) {
	//left subtree
	if (tree[nodeNum].first > 0)
		DFS(tree[nodeNum].first, cnt + 1);

	//visit
	low[cnt] = min(low[cnt], nodeIdx);
	high[cnt] = max(high[cnt], nodeIdx++);

	//right subtree
	if (tree[nodeNum].second > 0)
		DFS(tree[nodeNum].second, cnt + 1);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;

	for (int i = 0; i < MAX; ++i)
		low[i] = INF;

	for (int i = 0; i < n; ++i) {
		int parent, child1, child2;
		cin >> parent >> child1 >> child2;
		//루트면 parent에서만 1 증가하고
		//루트가 아니면 자식인 경우도 있기 때문에 2가 된다.
		node[parent]++;

		if (child1 != -1)
			node[child1]++;
		tree[parent].first = child1;
		if (child2 != -1)
			node[child2]++;
		tree[parent].second = child2;

	}

	//루트 찾기
	int root = 0;
	for (int i = 1; i <= n; ++i)
		if (node[i] == 1)
			root = i;

	//DFS
	nodeIdx = 1;
	DFS(root, 1);

	//최대길이를 구한다
	int ret = high[1] - low[1] + 1;
	int level = 1;
	for (int i = 2; i <= n; ++i) {
		int temp = high[i] - low[i] + 1;
		if (temp > ret) {
			ret = temp;
			level = i;
		}
	}
	cout << level << " " << ret;
	return 0;
}