//dp[n][k]= k개 더해서 n을 만들 수 있는 경우의 수

#include <iostream>

using namespace std;

int dp[201][201];
#define MOD 1000000000;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, k;

    cin >> n >> k;

    for (int i = 1; i <= n; i++)
        dp[i][1] = 1;

    for (int i = 2; i <= k; i++) {
        dp[1][i] = i;
    }


    for (int i = 2; i <= n; i++) {
        for (int j = 2; j <= k; j++) {
            dp[i][j] = (dp[i][j - 1] + dp[i - 1][j]) % MOD;
        }
    }

    cout << dp[n][k];

    return 0;
}