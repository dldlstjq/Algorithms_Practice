/*
모든 경우의 수를 고려해야 하기때문에 재귀함수를 이용했다.
더하기, 빼기, 곱하기, 나누기를 모두 인자로 넣어야 하고
인덱스는 0번째가 아니라 첫번째, 계산할 수는 제일 처음 원소를 넣어야 값이 맞게 나온다.
*/

#include <iostream>
#include <algorithm>

using namespace std;

const int MAX = 1000000000 + 1;
vector<int> ret;
int n;
int a[101];
int calc[4];
int min_num = MAX, max_num = -MAX;

void solve(int plus, int minus, int multply, int divide, int idx, int sum) {
    if (idx == n) {
        min_num = min(min_num, sum);
        max_num = max(max_num, sum);
        return;
    }

    if (plus > 0)
        solve(plus - 1, minus, multply, divide, idx + 1, sum + a[idx]);
    if (minus > 0)
        solve(plus, minus - 1, multply, divide, idx + 1, sum - a[idx]);
    if (multply > 0)
        solve(plus, minus, multply - 1, divide, idx + 1, sum * a[idx]);
    if (divide > 0)
        solve(plus, minus, multply, divide - 1, idx + 1, sum / a[idx]);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> a[i];

    for (int i = 0; i < 4; ++i)
        cin >> calc[i];

    solve(calc[0], calc[1], calc[2], calc[3], 1, a[0]);

    cout << max_num << "\n";
    cout << min_num;
    return 0;
}