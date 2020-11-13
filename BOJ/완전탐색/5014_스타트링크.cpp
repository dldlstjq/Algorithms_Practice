/*
BFS를 이용하면 쉽게 풀 수 있었다. 
현재 위치랑 버튼 누르는 횟수를 페어로 큐에 넣어서 U,D층을 다 검사해서 G층에 도착할 때 버튼 횟수를 출력하면 된다.
*/
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>

using namespace std;
#define MAX 1000001
bool visited[MAX];
int f, s, g, u, d;  //변수

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> f >> s >> g >> u >> d;

    bool is_ans = false;    //정답 유무
    int ans = 0;            //최종 정답
    queue<pair<int, int>> q;
    q.push(make_pair(s, 0));
    visited[s] = true;

    while (!q.empty()) {
        int now = q.front().first;
        int button = q.front().second;
        q.pop();

        //현재 층이 G층이면 종료
        if (now == g) {
            is_ans = true;
            ans = button;
            break;
        }

        int nu = now + u;
        int nd = now - d;

        //범위안에있고 방문 안했으면 큐에 추가
        if (!visited[nu] && 0 < nu && nu <= f) {
            q.push(make_pair(nu, button + 1));
            visited[nu] = true;
        }

        if (!visited[nd] && 0 < nd && nd <= f) {
            q.push(make_pair(nd, button + 1));
            visited[nd] = true;
        }
    }

    //답이 있으면 ans, 없으면 계단이용
    if (is_ans)
        cout << ans;
    else
        cout << "use the stairs";
    return 0;
}