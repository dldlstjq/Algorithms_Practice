/*
1654 랜선자르기와 거의 비슷한 문제.
이분 탐색으로 해결하면 쉽게 풀린다.

1. 잘린 나무의 합이 M보다 작을 경우
현재 높이보다 낮은 높이로 시도해 보아야 한다. 왼쪽 구간으로 변경

2. 잘린 나무의 합이 M보다 작거나 클 경우
현재 높이보다 높은 높이로 시도해 볼 수 있다. 오른쪽 구간으로 변경
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define MAX 1000001

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector<long long> v(n);
    long long max = 0;
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        if (v[i] > max)
            max = v[i];
    }

    long long left = 0, right = max;
    long long ans = 0;
    while (left <= right) {
        long long mid = (left + right) / 2;
        long long sum = 0;

        for (int i = 0; i < n; i++) {
            if (v[i] >= mid)
                sum += v[i] - mid;
        }

        if (sum >= m) {
            left = mid + 1;
            if (ans < mid)
                ans = mid;
        }
        else
            right = mid - 1;
    }

    cout << ans;
    return 0;
}