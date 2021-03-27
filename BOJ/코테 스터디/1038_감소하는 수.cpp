/*
재귀를 활용하면 쉽게 풀린다.
최대 감소하는 수가 9876543210이기 때문에 그 이상 넘어간는 자리수는 없다.
그리고 제일 마지막 수보다 작으면 그걸 하나씩 붙여가면서 구한다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 1000000 + 1;
vector<long long> v;
int N;

//최대 9876543210 10자리
void solve(long long idx, int cnt) {
    if (cnt > 10)
        return;

    v.push_back(idx);
    for (int i = 0; i < 10; ++i) {
        if (idx % 10 > i)
            solve(idx * 10 + i, cnt + 1);
    }
    return;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;

    for (int i = 0; i < 10; ++i)
        solve(i, 0);

    sort(v.begin(), v.end());

    long long ret = 0;

    //v 갯수보다 N이 크거나 같으면 -1
    if (v.size() <= N)
        cout << -1;
    else
        cout << v[N];

    return 0;
}