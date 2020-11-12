//2156_포도주 시식 문제랑 비슷함

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

long long dp[301];

int maximum(int a, int b) {
    return a > b ? a : b;
}

int main() {
    long long a[301] = { 0 };
    int n, max = 0;
    int x;

    cin >> n;

    for (int i = 1; i <= n; i++)
        cin >> a[i];

    dp[0] = 0;

    //dp[1]은 한 칸만 밟을 경우
    dp[1] = a[1];

    //dp[2]는 두 칸 연속으로 밟거나 두 칸 바로 오는 것 중에 최대값
    dp[2] = maximum(dp[1] + a[2], a[2]);

    //마지막 계단은 무조건 밟아야 되므로 a[i]는 무조건 더해주고 그 전 계단을 밟느냐 밟지 않느냐를 비교
    //a[i] + dp[i - 2] ->바로 전 계단을 밟지않고 두 칸 뛴 경우
    //a[i] + a[i - 1] + dp[i - 3] -> 바로 전 계단을 밟은 경우
    for (int i = 3; i <= n; i++) {
        dp[i] = maximum(dp[i - 3] + a[i - 1] + a[i], dp[i - 2] + a[i]);
    }

    cout << dp[n] << '\n';

    return 0;
}