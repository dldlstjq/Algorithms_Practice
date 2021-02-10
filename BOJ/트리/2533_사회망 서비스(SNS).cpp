/*
1949_우수마을 문제를 먼저 접해서 이 문제를 그나마 쉽게 해결할 수 있었다.
우수마을에서는 최대값을 구하는 거지만 여기서는 최소값을 구하는 것이었다.
자신이 sns를 안하면 연결된 사람은 무조건 해야되고 하는 경우
연결된 사람이 하거나 안한거나 둘 중 최소가 되게 하면 된다.

종만북의 dp를 따라하려면 단방향 그래프로 바꾼 후 적용하면 되는 것 같다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 1000002;
int n;
vector<int> tree[MAX];
bool visited[MAX];
int cache[MAX][2];

//cache[i][0]은 sns 안할때, cache[i][1]은 할때 최소 수
void solve(int root) {
	for (int i = 0; i < tree[root].size(); ++i) {
		int next = tree[root][i];
		if (visited[next])
			continue;
		visited[next] = true;
		solve(next);
		//sns를 안하면 연결된 친구가 sns 해야됨
		cache[root][0] += cache[next][1];
		//sns를 하면 연결된 친구 중 하는애, 안하는 애 중 최소
		cache[root][1] += min(cache[next][1], cache[next][0]);
	}
	//현재 노드가 sns를 한다면 1 추가
	cache[root][1] += 1;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for (int i = 0; i < n - 1; ++i) {
		int a, b;
		cin >> a >> b;
		tree[a].push_back(b);
		tree[b].push_back(a);
	}
	//루트는 어디든 상관없음
	visited[1] = true;
	solve(1);
	cout << min(cache[1][0], cache[1][1]);
	return 0;
}


///////////////////////////////////////
//다른 풀이
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring> //memset;
using namespace std;

const int MAX = 1000000 + 1;

int N;
vector<int> friends[MAX]; //처음 입력하는 친구 관계
vector<int> dirNode[MAX]; //단방향 그래프 저장
bool visited[MAX];
int cache[MAX][2]; //노드, earlyAdaptor?

//단방향 그래프로 바꾼다

void DFS(int nodeNum)
{
    visited[nodeNum] = true;

    for (int i = 0; i < friends[nodeNum].size(); i++)
    {
        int next = friends[nodeNum][i];

        if (!visited[next])
        {
            dirNode[nodeNum].push_back(next);
            DFS(next);
        }
    }
}


int getEarlyAdaptor(int nodeNum, bool early)
{
    int& result = cache[nodeNum][early];
    if (result != -1)
        return result;

    //본인이 얼리어댑터이면 자식은 어떻든 상관없다
    if (early)
    {
        result = 1; //얼리어댑터이므로
        for (int i = 0; i < dirNode[nodeNum].size(); i++)
        {
            int next = dirNode[nodeNum][i];
            result += min(getEarlyAdaptor(next, true), getEarlyAdaptor(next, false));
        }
    }

    //본인이 얼리어댑터가 아니면 자식은 무조건 얼리어댑터여야한다
    else
    {
        result = 0; //얼리어댑터가 아니므로
        for (int i = 0; i < dirNode[nodeNum].size(); i++)
        {
            int next = dirNode[nodeNum][i];
            result += getEarlyAdaptor(next, true);
        }
    }
    return result;
}


int main(void)
{
    cin >> N;

    for (int i = 0; i < N - 1; i++)
    {
        int node1, node2;
        cin >> node1 >> node2;

        friends[node1].push_back(node2);
        friends[node2].push_back(node1);
    }
    memset(cache, -1, sizeof(cache));

    DFS(1); //1이 루트

    //루트가 얼리어댑터일 수도 아닐 수도 있으므로
    cout << min(getEarlyAdaptor(1, false), getEarlyAdaptor(1, true)) << endl;
    return 0;
}