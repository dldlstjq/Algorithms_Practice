//처음에는 1차원 배열로 생각해서 dp[n]=dp[n-1]*2-1로 생각함.
//하지만 규칙적으로 증가하지 않아서 인터넷 보고 해결
//2차원 DP 사용. DP[a][b]=길이가 a일 때 마지막 수가 b일 계단의 수 의미


#include <iostream>

using namespace std;
#define MOD 1000000000
int N;
int dp[101][11];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    //DP[a][b] == 길이가 a 일때 마지막 수가 b일 경우의 계단의 수

    //1자리 수는 9개. 0으로 끝나는 한자리 수는 없음
    for (int i = 1; i < 10; ++i)
        dp[1][i] = 1;
    dp[1][0] = 0;

    //두 자리수부터 점화식 따라 계산
    for (int i = 2; i <= N; i++) {
        for (int j = 0; j < 10; j++) {
            if (j == 0)
                dp[i][j] = dp[i - 1][j + 1] % MOD;
            else if (j == 9)
                dp[i][j] = dp[i - 1][j - 1] % MOD;
            else
                dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j + 1]) % MOD;

        }
    }

    long long ans = 0;
    for (int i = 0; i < 10; i++) {
        ans += dp[N][i];
    }
    cout << ans % MOD;

    return 0;
}