#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int dp[1001];

int maximum(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int a[1001] = { 0 };
    int n, max = 0;
    int i, j;
    cin >> n;

    for (int i = 1; i <= n; i++)
        cin >> a[i];

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {

            //10 20 10 30 의 경우 10+20+30이 10+30보다 크기 때문에
            //maximum으로 비교해줌
            if (a[i] > a[j]) {
                dp[i] = maximum(a[i] + dp[j], dp[i]);
            }
        }
        if (dp[i] > max)
            max = dp[i];
    }

    cout << max << '\n';

    return 0;
}