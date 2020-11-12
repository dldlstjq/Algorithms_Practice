//처음으로 벡터와 STL 정렬함수 사용해봄.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector <int> dp;

int main() {
    int n;
    int b;

    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> b;
        dp.push_back(b);
    }

    sort(dp.begin(), dp.end());

    for (int i = 0; i < n; i++)
        cout << dp[i] << " ";

    return 0;
}