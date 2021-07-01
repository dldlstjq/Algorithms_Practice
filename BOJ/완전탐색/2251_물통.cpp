/*
이 문제 역시 BFS를 사용하면 풀 수 있다.
check[a][b]는 a의 물의 양, b의 물의 양을 나타낸다. 한 번 체크했는지 안했는지 여부를 나타낸다.
물통을 옮기는 수가 총 6가지 이므로 모든 경우를 다 큐에 넣어서 A물통이 0이 될때 C 물통의 양을 따로 체크하면 된다.
1. A->B
2. A->C
3. B->C
4. B->A
5. C->A
6. C->B
*/

// 2021.07.01 물을 옮기는 경우의 수와 bfs를 이용해서 푸는 문제이다.
// 어떻게 완전탐색으로 해결할 수 있을지 생각이 잘 안났다. 전체 6가지 경우도 생각 못했고 bfs쓰는것도 생각하지 못했다.
// 완탐을 풀려면 dfs, bfs, 혹은 처음부터 끝까지 모든 걸 다 해보는 것으로 접근해야겠다.
#include <iostream>
#include <algorithm>
#include <utility>
#include <queue>

using namespace std;
#define MAX 201
bool check[MAX][MAX];
bool ans[MAX];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int A, B, C;

    cin >> A >> B >> C;

    //큐에는 A와 B에 들어있는 물 양만 체크
    queue<pair<int, int>> q;
    q.push(make_pair(0, 0));

    while (!q.empty()) {
        //A, B, C에 들어있는 물의 양
        int a = q.front().first;
        int b = q.front().second;
        int c = C - a - b;
        q.pop();

        //이미 한번 체크했으면 안함
        if (check[a][b])
            continue;

        check[a][b] = true;
        //a가 비어있으면 c 체크
        if (a == 0)
            ans[c] = true;

        //A->B 옮김
        //현재 A와 B에 남아있는 물의 합이 B통보다 크면
        //A에는 a+b-B만큼 들어가고 B는 꽉 차게 들어감
        //아니면 A는 비고 B에는 A와 B의 물 양만큼 들어감
        if (a + b > B) {
            q.push(make_pair((a + b) - B, B));
        }
        else {
            q.push(make_pair(0, a + b));
        }

        //A->C
        //C의 경우 위에서 C-a-b로 물 양 체크하기때문에
        //A와 B에 남아있는 물만 큐에 넣음
        if (a + c > C) {
            q.push(make_pair((a + c) - C, b));
        }
        else {
            q.push(make_pair(0, b));
        }

        //B->A
        if (b + a > A) {
            q.push(make_pair(A, (a + b) - A));
        }
        else {
            q.push(make_pair(a + b, 0));
        }

        //B->C
        if (b + c > C) {
            q.push(make_pair(a, (b + c) - C));
        }
        else {
            q.push(make_pair(a, 0));
        }

        //C->A
        if (c + a > A) {
            q.push(make_pair(A, b));
        }
        else {
            q.push(make_pair(c + a, b));
        }

        //C->B
        if (c + b > B) {
            q.push(make_pair(a, B));
        }
        else {
            q.push(make_pair(a, b + c));
        }

    }

    //값이 true인 인덱스 출력
    for (int i = 0; i <= C; i++)
        if (ans[i])
            cout << i << " ";

    return 0;
}