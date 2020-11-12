//동빈나 유튜브 참고

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int dp[31];

int main() {
    int n;

    cin >> n;

    dp[0] = 1;
    dp[1] = 0;
    //길이가 2인 경우는 3가지 존재
    dp[2] = 3;


    //길이 4 부터는 새로운 모양 존재. 즉 짝수일 때마다 새로운 2개씩 발생
    for (int i = 4; i <= n; i++) {
        dp[i] = 3 * dp[i - 2];
        for (int j = 4; j <= i; j += 2) {
            dp[i] += 2 * dp[i - j];
        }

    }

    cout << dp[n];

    return 0;
}