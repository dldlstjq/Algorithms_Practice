//처음에는 1차원 배열로 생각해서 dp[n]=dp[n-1]*2-1로 생각함.
//하지만 규칙적으로 증가하지 않아서 인터넷 보고 해결
//2차원 DP 사용. DP[a][b]=길이가 a일 때 마지막 수가 b일 계단의 수 의미

// 2021.06.12 오랜만에 보니까 dp도 잘 못풀겠다. 탑다운, 바텀업 둘 다 풀이 가능한데 익숙한 탑다운 방식으로 푸는게 낫겠다.
// 끝이 0,9는 예외처리하고 나머지는 -1,+1 하면 쉽게 답을 구할 수 있다.
#include <iostream>

using namespace std;
#define MOD 1000000000
int N;
int dp[101][11];

//탑다운 재귀함수 풀이
//자리수가 num이고 끝이 digit인 계단수
int solve(int num, int digit) {
    if (num == 1)
        return digit == 0 ? 0 : 1;
    int& ret = cache[num][digit];
    if (ret != -1)return ret;

    //0인 계단수는 1만 가능
    if (digit == 0)
        ret = solve(num - 1, 1) % MOD;
    //9인 계단수는 8만 가능
    else if (digit == 9)
        ret = solve(num - 1, 8) % MOD;
    //그 외에는 +1,-1 가능
    else
        ret = (solve(num - 1, digit + 1) + solve(num - 1, digit - 1)) % MOD;

    return ret;
}


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

    // 바텀업
    long long ans = 0;
    for (int i = 0; i < 10; i++) {
        ans += dp[N][i];
    }
    cout << ans % MOD;

    //탑다운
    int ans = 0;
    for (int i = 0; i <= 9; ++i)
        ans = (ans + solve(n, i)) % MOD;
    cout << ans;

    return 0;
}