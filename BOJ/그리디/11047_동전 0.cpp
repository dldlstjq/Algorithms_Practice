/*
전형적인 그리디 문제인것 같다.
제일 가치가 큰 동전부터 시작해서 갯수가 최소가 되도록 만들면 된다.
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, cnt = 0;
    long long k;

    cin >> n >> k;

    vector<int> coin(n);

    for (int i = 0; i < n; i++)
        cin >> coin[i];

    for (int i = coin.size() - 1; i >= 0; i--) {
        //동전으로 나누어 지면 추가
        if (k == 0)
            break;
        if (k / coin[i]) {
            cnt += k / coin[i];
            k %= coin[i];
        }
    }
    cout << cnt;
    return 0;
}