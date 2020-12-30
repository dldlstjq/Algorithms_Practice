/*
너비 우선 탐색의 양방향 탐색을 이용하는 문제.
배열 선언 자체도 비트마스크를 이용하고 양방향 탐색이라는
자체가 아직 잘 이해가 되지 않는다.
dfs, bfs 둘 다 심화된 개념이 생소하다 보니 이해하는데
시간이 걸릴 것 같다.
*/


#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>

using namespace std;

const int MAX_DISCS = 12;
int c[1 << (MAX_DISCS * 2)];

int get(int state, int index) {
    return (state >> (index * 2)) & 3;
}

int set(int state, int index, int value) {
    return (state & ~(3 << (index * 2))) | (value << (index * 2));
}

//x의 부호를 반환한다.
//뒤집힌 갯수의 부호를 반환해서 어느 방향에서 접근한 건지 구분
int sgn(int x) { if (!x)return 0; return x > 0 ? 1 : -1; }
//x의 절대값을 1 증가시킨다.
//방향에 맞게 1씩 증가
int incr(int x) { if (x < 0)return x - 1; return x + 1; }

//discs개의 원반이 있고, 각 원반의 시작위치와 목표위치가
//begin, end에 주어질 때 최소 움직임의 수를 계산한다.
/*가운데서 만난 경우:
here로부터 접근한 there가 방문한 기록이 있고(c[there] != 0),
c[there]의 부호와 c[here]의 부호가 다른 경우 이는 양방향에서 접근하던 두 진행이 만난 것을 의미한다.
따라서 이 두 경우를 더하는데, 처음 초기값을 0이 아닌 1 또는 -1로 했기 때문에
c[there]-1 과 c[here]의 합을 반환하는 것에 주의하자.
*/
int bidir(int discs, int begin, int end) {
    if (begin == end)return 0;
    queue<int> q;
    //초기화를 0으로 하는데 주의
    memset(c, 0, sizeof(c));
    //정방향 탐색은 양수로, 역방향 탐색은 음수로 표시한다.
    q.push(begin);
    c[begin] = 1;
    q.push(end);
    c[end] = -1;
    while (!q.empty()) {
        int here = q.front();
        q.pop();
        int top[4] = { -1,-1,-1,-1, };
        for (int i = discs - 1; i >= 0; i--)
            top[get(here, i)] = i;
        for (int i = 0; i < 4; ++i)
            if (top[i] != -1)
                for (int j = 0; j < 4; ++j)
                    if (i != j && (top[j] == -1 || top[j] > top[i])) {
                        int there = set(here, top[i], j);
                        //아직 방문하지 않은 정점인 경우
                        if (c[there] == 0) {
                            c[there] = incr(c[here]);
                            q.push(there);
                        }
                        //가운데서 만난 경우
                        else if (sgn(c[there]) != sgn(c[here]))
                            return abs(c[there]) + abs(c[here]) - 1;
                    }
    }

}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int c;
    cin >> c;
    while (c--) {
        int N;
        cin >> N;
        int num, n;
        int first = 0;
        int end = pow(2, 2 * N) - 1;
        for (int i = 0; i < 4; i++) {
            cin >> num;
            for (int j = 0; j < num; j++) {
                cin >> n;
                first = set(first, n - 1, i);
            }
        }
        cout << bidir(N, first, end) << endl;

    }

    return 0;
}