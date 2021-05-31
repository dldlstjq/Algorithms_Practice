/*
dfs 사용하면 쉽게 풀릴 것 같았는데 사이클과 함께 고려한다는 부분에서 어려웠다.
다른 사람 블로그의 코드인데 핵심은 방문 여부와 함께 사이클인지도 고려해야 하는 것인듯.

-풀이방법-
함수는 시작점과, 현재 방문지점, 지금까지 몇개나 거쳐왔는지의 정보를 알고 있어야 한다.
이유는 다음과 같다.
노드의 상태는 방문한 적이 있거나, 방문한 기록이 없거나 양자택일이다.
방문한 적이 없다면 필요한 사항을 기록하고 간선을 따라 이동하면 될것이다.

방문한 적이 있다면 이유는 두가지중 하나다.
현재의 노드가 속한 사이클이 돌고 돌아서 다시 자기 자신에게 돌아왔거나,
아니면 현재 노드가 속하지 않은 사이클이 기록되고 이미 끝나버렸는데,
구질구질하게 현재의 노드는 그 사이클에 속하고 싶어하기 때문이다.

이 두가지를 구분하기 위해 시작점을 알아야 한다.
노드에 시작점을 기록했다면(사이클의 시작인 셈) 같은 사이클인지, 아닌지 구분할 수 있다.
같은 사이클이라면 현재의 깊이와 과거 기록되었던 깊이의 차이를 구하면, 사이클의 노드 수를 알 수 있다.
*/

#include <stdio.h>
#include <string.h>
using namespace std;

int t, n, ans;
int arr[100001], visit[100001], cycle[100001];

int dfs(int start, int cur, int dep) {
    visit[cur] = dep;
    cycle[cur] = start;

    int next = arr[cur];

	// 방문하지 않았으면 dfs 실행
    if (visit[next] == 0) {
        dfs(start, next, dep + 1);
    }
	// 방문했고 start와 cycle[next]가 같으면 사이클 처음으로 돌아왔다.
	// 깊이 차이로 팀 수 카운트
    else if (visit[next] != 0 && start == cycle[next])
        return dep - visit[next] + 1;
	// 시작점이 다르면 사이클이 안된다.
    else if (visit[next] != 0 && start != cycle[next])
        return 0;
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);

        memset(visit, 0, sizeof(visit));
        ans = 0;

        for (int i = 1; i <= n; ++i)
            scanf("%d", &arr[i]);

        for (int i = 1; i <= n; ++i) {
            if (visit[i] != 0)
                continue;
            if (visit[arr[i]] == 0)
                ans += dfs(i, i, 1);
        }
        printf("%d\n", n - ans);
    }
    return 0;
}



//////////////////////////////////////////////////////
/*
다른 풀이.
방문여부와 완료여부 배열을 두 개 두고 dfs를 실행한다.
방문하지 않은 학생은 dfs를 돌고 방문한 학생으로 돌아오면
다시 사이클을 돌면서 학생 수를 카운트한다.
카운트가 다 끝나면 완료됐다는 의미로 finished를 true로 만들어준다.
최종 답은 전체 n에서 팀이 된 학생수를 빼면 된다.
*/
#include <iostream>
#include <cstring>
using namespace std;

int arr[100002];
//방문 여부
bool visited[100002];
//사이클이 끝났는지 확인.
bool finished[100002];
int cnt;	//사이클에 속하는 정점 개수

//깊이 우선 탐색을 구현한다.
void dfs(int here) {
	visited[here] = true;
	int next = arr[here];
	//방문했는데 끝나지 않았으면 사이클을 돌면서 학생 수를 센다.
	if (visited[next]) {
		if (!finished[next]) {
			for (int i = next; i != here; i = arr[i])
				cnt++;
			cnt++;	//자기 자신
		}
	}
	//방문하지 않았으면 dfs 실행
	else
		dfs(next);
	//다 끝났으면 finished를 true로 만든다.
	finished[here] = true;
}


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		memset(visited, false, sizeof(visited));
		memset(finished, false, sizeof(finished));

		for (int i = 1; i <= n; ++i)
			cin >> arr[i];
		cnt = 0;
		for (int i = 1; i <= n; ++i) {
			if (!visited[i])
				dfs(i);
		}
		cout << n - cnt << "\n";
	}
	return 0;
}