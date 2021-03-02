/*
유니온 파인드 구조 연습문제이다.
단순히 합치거나 같은 집합인지만 확인하면 되어서 어렵지 않은 문제다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//트리를 이용해 상호 배제적 집합을 구한다.
struct OptimizedDisjointSet {
	vector<int> parent, rank;
	OptimizedDisjointSet(int n) :parent(n + 1), rank(n + 1, 1) {
		for (int i = 0; i <= n; ++i)
			parent[i] = i;
	}
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
		if (rank[u] > rank[v])swap(u, v);
		//이제 rank[v]가 항상 rank[u]이상이므로 u를 v의 자식으로 넣는다.
		parent[u] = v;
		if (rank[u] == rank[v])++rank[v];
	}
};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m;
	cin >> n >> m;
	OptimizedDisjointSet set(n);

	while (m--) {
		int flag, a, b;
		cin >> flag >> a >> b;
		if (flag != 1) {
			set.merge(a, b);
		}
		else {
			if (set.find(a) == set.find(b))
				cout << "YES\n";
			else
				cout << "NO\n";
		}
	}
	return 0;
}