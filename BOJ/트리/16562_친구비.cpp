/*
간단한 유니온 파인드 문제인 줄 알았는데 생각보다 헤맸다.
처음엔 친구관계를 먼저 파악한 후 합쳐서 비용을 계산하는 방식으로 생각했다.
그리고 비용이 초과하면 그만두는 방식으로 했는데 안되는 부분이 있었다.
결국 다른 사람의 풀이를 참고하여 해결할 수 있었다.

우선 친구관계를 다 만들어 주고 나서 루트가 본인인 경우만 비용을 계산하면 되었다.
또한 더 작은 비용인 친구를 루트로 만들어 줘야 하는데 그 또한 merge 함수 안에서 해결하면 됐다. 
상황에 따라 함수를 적절히 변형해야 하는데 그게 아직 잘 안되는 것 같다.
*/

#include <iostream>
#include <algorithm>
using namespace std;

int parent[10001];
int money[10001];

//u가 속한 트리의 루트의 번호를 반환한다.
int find(int u) {
	if (u == parent[u])return u;
	//u의 부모를 찾을 때 parent[u]에 부모를 저장해둬 다시 찾을 때도 재귀를 하지 않게 한다.
	return parent[u] = find(parent[u]);
}
//u가 속한 트리와 v가 속한 트리를 합친다.
void merge(int u, int v) {
	u = find(u); v = find(v);
	//u와 v가 이미 같은 집합에 속하는 경우를 걸러낸다.
	if (u == v)return;
	//친구비가 더 작은 쪽이 루트가 되도록 한다.
	if (money[u] > money[v])parent[u] = v;
	else parent[v] = u;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	for (int i = 1; i <= 10001; ++i)
		parent[i] = i;

	int n, m, k;
	cin >> n >> m >> k;

	for (int i = 1; i <= n; ++i)
		cin >> money[i];

	for (int i = 1; i <= m; ++i) {
		int v, w;
		cin >> v >> w;
		merge(v, w);
	}

	//루트가 자기자신인 비용만 계산한다.
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		if (parent[i] == i)
			ans += money[i];
	}
	if (k < ans)
		cout << "Oh no";
	else
		cout << ans;
	return 0;
}