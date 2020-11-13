/*
이분탐색의 개념은 알았는데 문제에 응용하는 걸 몰랐다.
구글링 통해서 풀었는데 이분탐색을 어떻게 응용하는지 감 잡음.
랜선 길이 중 최대값을 저장해서 1부터 max까지 이분탐색을 통해 만들 수 있는 최대 랜선의 길이를 찾으면 된다.

자르는 전선의 길이가 존재해야하기 때문에 low=1로 잡아야 문제가 풀린다.
처음에 low=0 으로 풀었는데 mid=0이 되서 런타엠 에러가 났다. 해결하는데 시간이 좀 걸렸다.
*/

#include <iostream>
#include <vector>

using namespace std;
long long n, k;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> k >> n;
    vector<long long> v(k);  //랜선 저장

    long long max = 0;

    for (int i = 0; i < k; i++) {
        cin >> v[i];
        if (v[i] > max)
            max = v[i];
    }

    //left는 0, right는 랜선의 최대 길이
    long long left = 1, right = max;
    long long mid = 0;
    long long ans = 0;

    //left와 right의 중간부분을 나누어 더한 값이 
    //n보다 작으면 right을 옮기고 크면 left를 옮긴다
    while (left <= right) {
        mid = (left + right) / 2;
        long long sum = 0;

        for (int i = 0; i < k; i++) {
            sum += v[i] / mid;
        }
        if (sum < n)
            right = mid - 1;
        else if (sum >= n) {
            left = mid + 1;
            if (mid > ans)
                ans = mid;
        }
    }
    cout << ans;

    return 0;
}