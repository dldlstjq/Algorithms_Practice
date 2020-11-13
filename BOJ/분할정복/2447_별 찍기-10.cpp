/*
이 문제도 종이의 개수, 쿼드 트리랑 비슷한 문제여서 풀 수 있을 줄 알았으나 다소 헤맸다.
n의 크기를 3분의 1씩 줄여나가며 별을 찍으면 되는 문제이다.
n의 크기를 1까지 줄여 별을 출력하면 더 간단한데 다시 풀때는 n을 3까지만 줄여 규칙에 맞게 별을 출력했다.

2차원 배열의 경우 세로(열)가 y축, 가로(행)가 x축으로 생각해서 풀기 때문에 y가 먼저 나온다.
*/
#include <iostream>
#include <cstring>

using namespace std;
#define MAX 2187
//그래프에 저장
char graph[MAX][MAX];

void star(int y, int x, int n) {
    //n=1일때 별 찍기
    if (n == 1) {
        graph[y][x] = '*';
        return;
    }

    ////////////////////////////////////////////
    //다시 풀 때는 n=3까지만 줄여 규칙에 맞게 별을 찍었다.
    if (n == 3) {
        for (int i = y; i < y + n; i++) {
            for (int j = x; j < x + n; j++) {
                if (i != y + 1 || j != x + 1)
                    graph[i][j] = '*';
            }
        }
        return;
    }
    ///////////////////////////////////////////////

    //3이 아니면 3으로 나눠주면서 재귀실행. (1,1)인 경우는 제외
    int m = n / 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == 1 && j == 1) {
                continue;
            }
            star(y + i * m, x + j * m, m);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    //공백으로 초기화
    memset(graph, ' ', sizeof(graph));

    //별 찍기
    star(0, 0, n);

    //그래프 전체 출력
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << graph[i][j];
        }
        cout << "\n";
    }
    return 0;
}