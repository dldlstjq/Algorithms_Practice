/*
2447번이랑 비슷한 문제 인줄 알았는데 고려해야할 게 더 많았다.
일정한 비율로 줄어들면서 재귀를 쓸 수가 없어 다른 블로그를 참고해서 풀 수 있었다.
핵심은 삼각형 높이가 3이 될때까지 위, 왼쪽, 오른쪽으로 나눠서 재귀함수를 쓰면 된다.
*/

#include <iostream>
#include <cstring>

using namespace std;
#define MAX 3072
char graph[MAX][MAX * 2];

void star(int y, int x, int n) {
    //높이가 3이면 삼각형 그림
    if (n == 3) {
        graph[y][x] = '*';

        graph[y + 1][x + 1] = '*';
        graph[y + 1][x - 1] = '*';

        graph[y + 2][x - 2] = '*';
        graph[y + 2][x - 1] = '*';
        graph[y + 2][x] = '*';
        graph[y + 2][x + 1] = '*';
        graph[y + 2][x + 2] = '*';
        return;
    }

    //맨 위 삼각형, 왼쪽 삼각형, 오른쪽 삼각형
    int m = n / 2;
    star(y, x, m);
    star(y + m, x - m, m);
    star(y + m, x + m, m);

}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int N;
    cin >> N;

    memset(graph, ' ', sizeof(graph));
    //맨위 꼭짓점 y,x 좌표, 삼각형 높이
    star(0, N - 1, N);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 2 * N; j++) {
            cout << graph[i][j];
        }
        cout << "\n";
    }

    return 0;
}