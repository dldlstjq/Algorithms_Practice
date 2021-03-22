/*
그리디라고 하긴 하는데 dp랑 더 가까운거 같다.
3kg, 5kg 다 해서 최소인 값이 정답이다.
답이 없으면 INF가 저장되어 있다.
*/

#include <iostream>
#include <algorithm>

using namespace std;

const int MAX = 5000 + 1;
const int INF = 987654321;
int n;
int cache[MAX];

int solve(int num) {
    if (num == 0)
        return 0;

    int& ret = cache[num];
    if (ret != INF)return ret;

    //3kg 5kg 해서 작은 쪽이 정답
    if (num - 3 >= 0)
        ret = min(ret, 1 + solve(num - 3));

    if (num - 5 >= 0)
        ret = min(ret, 1 + solve(num - 5));
    return ret;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    for (int i = 0; i < MAX; ++i)
        cache[i] = INF;

    cin >> n;
    solve(n);

    //답이 없으면 INF가 저장되어있다
    if (cache[n] == INF)
        cout << -1;
    else
        cout << cache[n];
    return 0;
}