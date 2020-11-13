/*
1780 종이의 개수와 비슷한 문제이다.
n의 크기를 2분의 1씩 줄여나가며 재귀함수를 이용하면 풀 수 있다.
*/
#include <iostream>
#include <string>

using namespace std;
#define MAX 64
string tree[MAX];

//같은 0인지 1인지 검사
bool same(int x, int y, int n) {
    for (int i = x; i < x + n; i++) {
        for (int j = y; j < y + n; j++) {
            if (tree[i][j] - '0' != tree[x][y] - '0')
                return false;
        }
    }
    return true;
}

void quad_tree(int x, int y, int n) {
    if (same(x, y, n)) {
        if (tree[x][y] - '0' == 1)
            cout << 1;
        else
            cout << 0;
        return;
    }
    cout << "(";

    //같지 않으면 1/2씩 줄어듬
    int m = n / 2;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            quad_tree(x + i * m, y + j * m, m);
        }
    }
    cout << ")";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> tree[i];

    quad_tree(0, 0, n);

    return 0;
}