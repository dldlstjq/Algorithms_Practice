/*
1. 이 문제는 제곱수를 만드는 건데 현재의 제곱수의 최소값을 위해서 이전의 최소값을 이용하여서 최소값을 만든다.

2. 검색의 범위는 제곱수기 때문에 1 부터 j * j <= i 까지로 충분하다.그러므로 검색시간을 줄일 수 있다.

3. 즉 Dp[i] = Dp[i - j * j] + 1 라는 식이 나오는데 이 식은 j * j 수의 제곱수 값 1 + 이전에 값 Dp[i - j * j] 값으로 구 할수 있다.

4. 하지만 j의 최대값만으로 하면 예외 조건이 생길 수 수 있으므로 1~j의 최대값까지 전부 비교 해야한다.그 예외 조건의 예시는 12가 있다.

- 12 = 3 * 3 + 1 * 1 + 1 * 1 + 1 * 1 = 4

- 12 = 2 * 2 + 2 * 2 + 2 * 2 = 3

재귀호출로 풀어보려했는데 시간초과가 났다.
아무래도 스택 오버플로우가 일어나서 도중에 프로그램을 종료시키는 것 같다.
반복문이 아무래도 실행속도가 빠르다 보니 쉽게 풀 수 있는 건 점화식을 세워서
반복문으로 빨리 해결하는게 나은 것 같기도 하다.
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//재귀함수 풀이
//제곱수는 precalc로 미리 1로 계산한다.
//그 후 num보다 작은 모든 제곱수에 대해 최소값을 구한다.
const int INF = 987654321;
int n;
int cache[100001];

//제곱수는 미리 1로 계산
void precalc() {
    for (int i = 1; i * i <= n; ++i)
        cache[i * i] = 1;
}

//num이 제곱수면 1을 반환, 아니면 재귀함수로 값을 구한다.
int solve(int num) {
    int& ret = cache[num];
    if (ret != INF)
        return ret;
    for (int i = 1; i * i <= num; ++i)
        ret = min(ret, solve(num - i * i) + 1);
    return ret;
}



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