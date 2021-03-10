/*
못 푼 dp 문제들 특징이 접근을 아예 못했거나, 비슷하게 갔는데 뭔가 하나에서 안되거나 둘 중 하나였다.
이 문제는 비슷하게 접근했는데 마지막 하나가 안된 그런 문제였다.

각 N에 대하여 어떤 값들이 올 수 있는지 생각해본다면

1. 단순히 최대인 N-1값에 1을 더한 값이 올 수 있다. 즉, 버튼 A를 누르는 경우
2. 최소한 ctrl-ACV는 같이 눌러야 하므로, N-3값에 ACV를 눌러 값을 구성할 수 있다.
3. ctrl-ACVV와 같이 누를 수 있으므로, N-4값에 aCVV를 눌러 값을 구성할 수 있다.
4. ctrl-ACVVV...와 같이 누를 수 있으므로, N-k값에 ACVVV...를 눌러 값을 구성할 수 있다.

3, 4번을 생각하지 못했다. 그리고 붙여넣는다면 몇 개의 A가 생기는지도 생각해야 한다.

일단 최소 3번은 눌러야하기 때문에 n이 3이상인 경우부터 시작해야 하고
ACVV를 k번 수행한다면 DP[N-k]*(k-1)을 하면 구할 수 있다.

N=7
A A A ctrl-A C V V 
DP[N-4]*(4-1)

*/

#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int n;
//cache[i]=i번 누를때 A 최대 갯수
long long cache[101];

long long solve(int num) {
    //기저 사례: 1이면 1번눌러 A출력 해야한다.
    if (num <= 0)
        return 0;
    long long& ret = cache[num];
    if (ret != -1)return ret;

    //먼저 A만 눌렀을 때 나오는 갯수 저장
    ret = solve(num - 1) + 1;

    //ctrl-A,C,V를 눌렀을 때 최대가 되는지 비교한다.
    //num이 3이상일 때 ctrl-A,C,V를 누를 수 있다.
    //ACV, ACVV, ACVVV 처럼 ctrl-V를 여러번 누르는 경우가 있을 수 있는데
    //solve(num-i)*(i-1)을 하면 A 개수를 구할 수 있다.
    if (num >= 3) {
        for (int i = 3; i < n; ++i)
            ret = max(ret, solve(num - i) * (i - 1));
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    memset(cache, -1, sizeof(cache));
    cin >> n;
    cout << solve(n);

    return 0;
}