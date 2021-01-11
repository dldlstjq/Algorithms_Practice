//p[a] = 카드 a개의 가격 , DP[a] = a개 카드를 구매했을 때의 최대 비용을 의미한다.
/*
이 문제는 카드 N개를 구매할 때의 최대비용을 구해야 하므로, 마지막에 1개짜리 카드팩을 구매하는 경우를 생각해보자.

마지막에 1개짜리 카드팩을 구매한다고 가정하면, 그 전에서 N - 1개의 카드를 구매해야 하고, 이를 식으로 나타내면

DP[N - 1] + p[1] 이 된다. N - 1개를 구매했을 때의 최대비용과 1개를 구매했을 때의 가격, 즉 총 N개를 구매한 가격이

나오게 된다.

마지막에 2장짜리 카드팩을 사는 것을 고려해보면, DP[N - 2] + p[2]가 된다.

마지막에 N장짜리 카드팩을 사는 것을 고려해보면, DP[N - N] + p[N]이 되게 된다.

이 문제는, 최대비용을 구해야 하므로, 마지막에 카드를 1장 사는 것 부터 최대 N장 사는 것 까지 모두 다 고려해서

비교해 주어야 한다.

따라서, 위의 말을 토대로 점화식을 도출해본다면 DP[N] = DP[N] vs(DP[N - a] + p[a]) 가 된다.
*/



#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//재귀호출로 푼 풀이.
//반복문을 재귀함수로 바꾸면 된다.
int n;
int cache[1001];
int card[1001];

int solve(int num) {
    if (num == 0)
        return 0;
    int& ret = cache[num];
    if (ret != -1)return ret;
    ret = 0;
    //점화식. 모든 경우를 다 탐색하면서 최대값을 찾는다.
    for (int i = 1; i <= num; ++i) {
        ret = max(ret, solve(num - i) + card[i]);
    }
    return ret;
}


int dp[1001];

int Max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int p[1001] = { 0 };
    int n;

    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }

    dp[1] = p[1];
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            dp[i] = Max(dp[i], dp[i - j] + p[j]);
        }
    }

    cout << dp[n];

    return 0;
}