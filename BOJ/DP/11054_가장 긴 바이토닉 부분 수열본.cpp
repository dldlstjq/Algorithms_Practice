#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int dp[2][1001];

int maximum(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int a[1001] = { 0 };
    int n, max = 0;

    cin >> n;

    for (int i = 1; i <= n; i++)
        cin >> a[i];

    for (int i = 0; i < 2; i++)
        for (int j = 1; j <= n; j++)
            dp[i][j] = 1;

    //왼쪽에서 오른쪽으로 증가수열
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            if (a[i] > a[j]) {
                dp[0][i] = maximum(dp[0][j] + 1, dp[0][i]);
            }
        }

    }

    //오른쪽에서 왼쪽으로 증가수열
    for (int i = n; i >= 1; i--) {
        for (int j = n + 1; j > i; j--) {
            if (a[i] > a[j]) {
                dp[1][i] = maximum(dp[1][j] + 1, dp[1][i]);
            }
        }
    }

    //두 수열을 더해서 가장 큰 값이 가장 긴 바이토닉 수열
    for (int i = 1; i <= n; i++) {
        if (dp[0][i] + dp[1][i] > max) {
            max = dp[0][i] + dp[1][i];

        }
    }

    //수열을 계산 시 가장 큰 값이 두 번 겹치므로 1 빼줌
    cout << max - 1 << '\n';

    return 0;
}