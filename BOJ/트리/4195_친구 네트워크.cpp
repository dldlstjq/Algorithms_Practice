/*
유니온 파인드를 사용하면 되는데 string형으로 입력이 들어와서 int로 바꿔야 한다.
처음엔 map밖에 생각이 안났는데 unordered_map이라고 해시맵을 사용하면
map을 사용한 것 보다 시간이 반이상 줄어든다.

map에 저장하고 parent를 지정하는 것 까진 좋았는데
1. 같은 루트인지 먼저 확인해야 하는 것
2. 집합의 크기를 구하는 것
이 두가지에서 잘 풀어나가지 못했다.
집합의 크기는 크기가 큰 쪽에 작은 쪽을 더해주면 끝이었다.

마지막으로 런타임에러가 자꾸 떠서 의아했는데 배열 크기를 2배로 늘려주니 해결됐다.
찾아보니 관계수가 최대 10만이며 사람 수는 최대 20만이 나오기 때문이라고 한다.
*/

#include <iostream>
#include <unordered_map>
#include <algorithm>
using namespace std;

const int MAX = 200000 + 1;

int parent[MAX];
int setSize[MAX];

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
	else {
		if (setSize[u] > setSize[v])
			swap(u, v);
		parent[u] = v;
		setSize[v] += setSize[u];
		setSize[u] = 0;
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;
	while (t--) {
		int num;
		cin >> num;
		for (int i = 0; i < MAX; ++i) {
			parent[i] = i;
			setSize[i] = 1;
		}
		unordered_map<string, int> name;
		int order = 0;

		while (num--) {
			string s1, s2;
			cin >> s1 >> s2;
			if (!name.count(s1))
				name[s1] = order++;
			if (!name.count(s2))
				name[s2] = order++;

			//루트를 찾음
			int root1 = find(name[s1]);
			int root2 = find(name[s2]);

			if (root1 == root2)
				cout << max(setSize[root1], setSize[root2]) << "\n";
			else {
				merge(root1, root2);
				cout << max(setSize[root1], setSize[root2]) << "\n";
			}

		}
	}
	return 0;
}