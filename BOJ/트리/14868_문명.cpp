#include <cstdio>
#include <utility>
#include <algorithm>
#include <queue>
using namespace std;
typedef struct {
    int x;
    int y;
} cord;

int Parent[100002];
int n, k;
int map[2001][2001];
int dirx[] = { 1, -1, 0, 0 };
int diry[] = { 0, 0, 1, -1 };
queue<cord> q, q2;

int Find(int x) {
    if (Parent[x] == x) return x;
    return Parent[x] = Find(Parent[x]);
}

bool Merge(int x, int y) {
    x = Find(x);
    y = Find(y);

    if (x == y) return true; //이미 같은 문명이라면 true
    Parent[x] = y;
    return false;
    //다른 문명이므로 union 한 뒤 false를 리턴한다. -> 문명의 개수 1 감소.
}

void bfs() { //문명을 합치는 BFS
    while (!q.empty()) {
        int curx = q.front().x;
        int cury = q.front().y;
        q2.push({ curx, cury });
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nx = curx + dirx[i];
            int ny = cury + diry[i];

            if (1 <= nx && nx <= n && 1 <= ny && ny <= n) {
                if (map[nx][ny] > 0 && map[curx][cury] != map[nx][ny]) {
                    if (!Merge(map[nx][ny], map[curx][cury])) {
                        k--;
                    }
                }
            }
        }
    }
}

void bfs2() { //문명을 전파하는 BFS
    while (!q2.empty()) {
        int curx = q2.front().x;
        int cury = q2.front().y;
        q2.pop();

        for (int i = 0; i < 4; i++) {
            int nx = curx + dirx[i];
            int ny = cury + diry[i];

            if (1 <= nx && nx <= n && 1 <= ny && ny <= n) {
                if (map[nx][ny] == 0) {
                    map[nx][ny] = map[curx][cury];
                    q.push({ nx, ny });
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= k; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        map[x][y] = i;
        Parent[i] = i;
        q.push({ x, y });
    }

    int ans = 0;
    while (true) {
        bfs();
        if (k == 1) {
            printf("%d\n", ans);
            return 0;
        }
        bfs2();
        ans++;
    }
}