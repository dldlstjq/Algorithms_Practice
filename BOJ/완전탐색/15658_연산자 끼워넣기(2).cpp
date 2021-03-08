/*
14888_연산자 끼워넣기랑 거의 비슷하다.
여기서는 연산자의 갯수가 딱 n-1개가 아닐수도 있다는 것이 다르다.
코드가 거의 똑같은데 solve에서 재귀함수 조건을 0이 아닐때로 설정하면 
모든 경우를 다 고려하기 때문에 쉽게 풀린다.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX = 1000000000 + 1;
int n;
int a[13];
int calc[4];
int max_num = -MAX;
int min_num = MAX;

void solve(int plus, int minus, int multiply, int divide, int idx, int sum) {
    if (idx == n) {
        min_num = min(min_num, sum);
        max_num = max(max_num, sum);
        return;
    }

    //갯수가 0이 아닌 경우 다 시도해보면 된다.
    if (plus != 0)
        solve(plus - 1, minus, multiply, divide, idx + 1, sum + a[idx]);
    if (minus != 0)
        solve(plus, minus - 1, multiply, divide, idx + 1, sum - a[idx]);
    if (multiply != 0)
        solve(plus, minus, multiply - 1, divide, idx + 1, sum * a[idx]);
    if (divide != 0)
        solve(plus, minus, multiply, divide - 1, idx + 1, sum / a[idx]);
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