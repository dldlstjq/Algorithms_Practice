#include <iostream>
#include <cstring>
using namespace std;

// 0~40 까지 수에서 0과 1이 사용되는 수 저장
int cache[41][2];

int main(int argc, char** argv) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;

    memset(cache, -1, sizeof(cache));

    // 0: 0은 1번, 1은 0번
    // 1: 0은 0번, 1은 1번
    cache[0][0] = 1; cache[0][1] = 0;
    cache[1][0] = 0; cache[1][1] = 1;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 2; i <= n; ++i) {
            // 점화식
            cache[i][0] = cache[i - 2][0] + cache[i - 1][0];
            cache[i][1] = cache[i - 2][1] + cache[i - 1][1];
        }

        cout << cache[n][0] << ' ' << cache[n][1] << '\n';
    }

    return 0;
}


// 다른 풀이
#include <iostream>
#include <cstring> 
using namespace std;

int cache[41];
int zero, one;

int solve(int num) {
    if (num == 0)
        return 0;

    if (num == 1)
        return 1;

    int& ret = cache[num];
    if (ret != -1)return ret;

    ret = solve(num - 1) + solve(num - 2);
    return ret;
}

int main(int argc, char** argv) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;

    memset(cache, -1, sizeof(cache));
    while (t--) {
        int n;
        cin >> n;

        // n이 0과 1일 때 제외하고는 0의 개수는 n-1의 피보나치수, 1의 개수는 n의 피보나치 수이다.
        if (n == 0)
            cout << 1 << ' ' << 0 << '\n';
        else if (n == 1)
            cout << 0 << ' ' << 1 << '\n';
        else
            cout << solve(n - 1) << ' ' << solve(n) << '\n';
    }

    return 0;
}