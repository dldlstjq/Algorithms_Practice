/*
트리와 관련있긴 하지만 사실상 dp문제인 것 같다.
dp를 며칠 안했다고 함수가 잘 생각나지 않았다.
종만북에 있는 dp 풀이에 너무 얽매여서 그런 것도 있는 것 같다.
단순히 ret을 이용하지 않아도 간단히 dp계산을 한 후 답을 구할 수 있었다.

1. dfs를 이용해서 하나의 정점을 잡고 쭉 파고 들어간다.(굳이 트리를 만들 필요 없다.)
2. 이때 계속해서 자식 노드의 값을 발견하고 이를 이용해서 점화식으로 dp에 저장해나간다.
3. dp[i][0](i번째 노드를 포함시켰을 때의 값): 자식 노드들의 dp[i][1]의 합 + w[i]
4. dp[i][1](i번쨰 노드를 포함시키지 않았을 때의 값) : 자식 노드들의 dp[i][0] dp[i][1] 중 큰 값의 합
5. 결과적으로 1번 노드 dp에 저장된 값들 중에 큰 값이 정답이다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 10001;
int n;
int people[MAX];
vector<int> tree[MAX];
int cache[MAX][2];
bool visited[MAX];

void solve(int root) {
	for (int i = 0; i < tree[root].size(); ++i) {
		int next = tree[root][i];
		if (visited[next])
			continue;
		visited[next] = true;
		solve(next);
		cache[root][0] += cache[next][1];
		cache[root][1] += max(cache[next][0], cache[next][1]);
	}
	cache[root][0] += people[root];
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for (int i = 1; i <= n; ++i)
		cin >> people[i];

	for (int i = 0; i < n - 1; ++i) {
		int a, b;
		cin >> a >> b;
		tree[a].push_back(b);
		tree[b].push_back(a);
	}

	visited[1] = true;
	solve(1);
	cout << max(cache[1][0], cache[1][1]);
	return 0;
}



///////////////////////////////////////////////
//다른 풀이. 종만북의 dp계산을 이용하려면 그래프를 단방향 그래프로 바꿔준 후
//적용해야 문제를 풀 수 있었다.
#include <iostream> 
#include <vector>
#include <algorithm> 
#include <cstring> 
using namespace std; 
const int MAX = 1e4 + 1; 
const int ROOT = 1; 

int N; 
int citizensOfVillage[MAX]; 
vector<int> villages[MAX]; 
vector<int> tree[MAX]; 
int cache[MAX][2];
bool visited[MAX]; 

int func(int idx, bool isExcellent) { 
	int &result = cache[idx][isExcellent]; 
	if (result != -1) 
		return result; 
	
	result = 0;
	
	for (int i = 0; i < tree[idx].size(); i++) { 
		int nextIdx = tree[idx][i]; 
		int firstCandidate = func(nextIdx, false);
		int secondCandidate = -1; 

		if (isExcellent == false) { 
			secondCandidate = func(nextIdx, true); 
		} 
		
		result += max(firstCandidate, secondCandidate);
	} 
	if (isExcellent) { 
		result += citizensOfVillage[idx]; 
	}
	return result;
} 

void createTree(int idx) {
	for (int i = 0; i < villages[idx].size(); i++) { 
		int nextIdx = villages[idx][i]; 
		if (visited[nextIdx] == false) {
			tree[idx].push_back(nextIdx); 
			visited[nextIdx] = true; 
			createTree(nextIdx); 
		} 
	} 
} 

int main(void) { 
	ios_base::sync_with_stdio(0); 
	cin.tie(0); 
	
	cin >> N; 
	for (int i = 1; i <= N; i++) 
		cin >> citizensOfVillage[i]; 
	
	
	for (int i = 0; i < N - 1; i++) {
		int a, b; 
		cin >> a >> b;
		villages[a].push_back(b);
		villages[b].push_back(a); 
	} 
	visited[ROOT] = true; 
	createTree(ROOT); 
	memset(cache, -1, sizeof(cache)); 
	int result = max(func(1, false), func(1, true)); 
	cout << result << "\n"; 
	return 0; 
}

