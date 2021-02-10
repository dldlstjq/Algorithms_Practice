/*
루트인 1번부터 가도록 해야 했는데 반대로 2번 섬부터 시작해 n번 섬까지 거꾸로
올라가는 형식으로 구현했다가 틀렸다.
더군다나 늑대가 한번 양을 잡아 먹으면 다음엔 못잡아먹는데 무작정 잡아먹는 식으로 해서 틀린 것도 있다.
답의 자료형도 int를 벗어나는데 그것도 고려하지 못했다.

dfs를 써먹기 위해서 루트인 1번섬부터 순회하도록 해야 하며 늑대인 경우에는
마이너스를 붙여 양의 수를 빼도록 하면 된다.
풀이를 보니 생각보다 간단한건데 너무 어렵게 구현하여 풀지 못했다.
*/

#include <iostream>
#include <vector>
using namespace std;

const int MAX = 123456 + 2;

struct island {
	int cnt;
	vector<int> next;
};
island tree[MAX];
int n;

long long dfs(int cur) {
	long long res;
	res = tree[cur].cnt;
	for (int next : tree[cur].next) {
		res += dfs(next);
	}
	if (res < 0LL)res = 0LL;
	return res;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	char c;
	int a, p;
	for (int i = 2; i <= n; ++i) {
		cin >> c >> a >> p;
		tree[i].cnt = (c == 'W' ? -a : a);
		tree[p].next.push_back(i);
	}
	tree[1].cnt = 0;
	cout << dfs(1) << "\n";
	return 0;
}