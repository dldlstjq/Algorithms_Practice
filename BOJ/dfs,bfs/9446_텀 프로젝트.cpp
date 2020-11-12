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

    if (visit[next] == 0) {
        dfs(start, next, dep + 1);
    }
    else if (visit[next] != 0 && start == cycle[next])
        return dep - visit[next] + 1;
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
