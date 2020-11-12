//9번째 부터 점화식 발생

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

long long int dp[31];

int main() {
    int t;
    int n, min = 9999;

    cin >> t;

    for (int i = 0; i < t; i++) {
        cin >> n;

        dp[1] = 1;
        dp[2] = 1;
        dp[3] = 1;
        dp[4] = 2;
        dp[5] = 2;
        dp[6] = 3;
        dp[7] = 4;
        dp[8] = 5;
        for (int j = 9; j <= n; j++) {
            dp[j] = dp[j - 5] + dp[j - 1];
        }
        cout << dp[n] << '\n';
    }
    return 0;
}