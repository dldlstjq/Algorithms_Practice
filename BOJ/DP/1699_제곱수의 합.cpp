//1. 이 문제는 제곱수를 만드는 건데 현재의 제곱수의 최소값을 위해서 이전의 최소값을 이용하여서 최소값을 만든다.
//
//2. 검색의 범위는 제곱수기 때문에 1 부터 j * j <= i 까지로 충분하다.그러므로 검색시간을 줄일 수 있다.
//
//3. 즉 Dp[i] = Dp[i - j * j] + 1 라는 식이 나오는데 이 식은 j * j 수의 제곱수 값 1 + 이전에 값 Dp[i - j * j] 값으로 구 할수 있다.
//
//4. 하지만 j의 최대값만으로 하면 예외 조건이 생길 수 수 있으므로 1~j의 최대값까지 전부 비교 해야한다.그 예외 조건의 예시는 12가 있다.
//
//- 12 = 3 * 3 + 1 * 1 + 1 * 1 + 1 * 1 = 4
//
//- 12 = 2 * 2 + 2 * 2 + 2 * 2 = 3

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

long long int dp[100001];

int Min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    long long int a[301] = { 0 };
    int n;

    cin >> n;

    for (int i = 0; i <= n; i++)
        dp[i] = i;

    for (int i = 2; i <= n; i++) {
        for (int j = 2; j * j <= i; j++) {
            dp[i] = Min(dp[i], dp[i - j * j] + 1);
        }
    }
    cout << dp[n] << '\n';



    return 0;
}