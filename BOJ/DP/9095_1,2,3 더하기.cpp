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