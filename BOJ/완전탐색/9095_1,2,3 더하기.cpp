/*
처음엔 DP로 풀었는데 재귀로도 풀 수 있었다.
DP는 간단하게 4번째부터 점화식이 성립한다.
*/

// 2021.07.12 dp 탑다운
int solve(int num) {
    if (num == 0)
        return 1;

    if (num < 0)
        return 0;

    int& ret = cache[num];
    if (ret != -1)return ret;
    ret = 0;
    ret = solve(num - 1) + solve(num - 2) + solve(num - 3);
    return ret;
}

//DP 코드 바텀 업
#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    int dp[12];
    cin >> t;

    while (t--) {
        int n;
        cin >> n;
        dp[1] = 1;
        dp[2] = 2;
        dp[3] = 4;
        //점화식. 앞에 3개 더하면 됨
        for (int i = 4; i <= 11; i++) {
            dp[i] = dp[i - 3] + dp[i - 2] + dp[i - 1];
        }

        cout << dp[n] << "\n";

    }

    return 0;
}



/////////////////
//재귀 코드
#include <cstdio>
using namespace std;

int cnt = 0;

void add(int sum, int goal) {
    if (sum > goal) return;
    else if (sum == goal) {
        cnt++;
        return;
    }
    else {
        for (int i = 1; i <= 3; i++) {
            add(sum + i, goal);
        }
    }
}

int main() {
    int t, n;
    scanf("%d", &t);

    for (int i = 0; i < t; i++) {
        cnt = 0;
        scanf("%d", &n);
        add(0, n);
        printf("%d\n", cnt);
    }

    return 0;
}