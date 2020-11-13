/*
처음에는 무작정 두 배 먼저 이동하고 그 다음 1칸 앞뒤로 움직이는 걸로 생각했다.
그렇게 하니 모든 경우를 다 따질 수 없어 찾아보니 bfs를 이용하면 쉽게 풀렸다.
현재 위치 부터 시작해서 모든 경우의 수를 큐에다 집어넣어서 하나씩 따져보면 쉽게 풀 수 있는 문제였다.

한번 도달한 지점은 visited 배열을 통해 도달여부를 파악해야한다.
방문한 지점을 다시 큐에 넣으면 메모리초과가 발생하고 실행시간도 길어져서 문제를 풀 수 없다는 것 주의
*/

#include <iostream>
#include <algorithm>
#include <utility>
#include <queue>

using namespace std;
#define MAX 100001
int n, k;
bool visited[MAX];

int hide_seek(int n, int k) {
    //현재 위치랑 시간 페어로 저장
    queue<pair<int, int>> q;
    q.push(make_pair(n, 0));
    visited[n] = true;
    while (!q.empty()) {
        int now = q.front().first;
        int time = q.front().second;
        q.pop();

        //현재 위치가 k랑 같으면 리턴
        if (now == k)
            return time;

        //+1,-1,*2씩 해서 방문 안했으면 큐에 넣음
        if (now + 1 < MAX && !visited[now + 1]) {
            q.push(make_pair(now + 1, time + 1));
            visited[now + 1] = true;
        }

        if (now - 1 >= 0 && !visited[now - 1]) {
            q.push(make_pair(now - 1, time + 1));
            visited[now - 1] = true;
        }

        if (now * 2 < MAX && !visited[now * 2]) {
            q.push(make_pair(now * 2, time + 1));
            visited[now * 2] = true;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> k;

    //bfs
    cout << hide_seek(n, k);

    return 0;
}