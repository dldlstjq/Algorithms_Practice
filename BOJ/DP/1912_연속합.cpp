#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector <int> dp;

int maximum(int a, int b) {
    return a > b ? a : b;
}

int main() {
    vector<int> a;
    int n, max = -500500;
    int x;

    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> x;
        a.push_back(x);
    }

    dp.push_back(a.front());

    for (int i = 1; i < a.size(); i++) {
        dp.push_back(maximum(a[i], dp[i - 1] + a[i]));
    }

    for (int i = 0; i < dp.size(); i++) {
        if (dp[i] > max)
            max = dp[i];
    }

    cout << max << '\n';



    return 0;
}