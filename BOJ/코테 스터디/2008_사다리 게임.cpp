#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <set>
using namespace std;

const int MAX = 500 + 1;
int N, M;
int a, b, X, Y;

int cache[MAX][MAX];
int line[MAX];

bool is_in(int num) {
    return 0 <= num && num < N;
}

int solve(int start, int end) {
    int y = 0;
    int x = start;


}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M;

    cin >> a >> b >> X >> Y;
    a -= 1;
    b -= 1;
    for (int i = 0; i < M; ++i) {
        cin >> line[i];
        line[i] -= 1;
    }



    return 0;
}