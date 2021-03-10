/*
처음엔 1차원 dp로 잡고 길이 L인 문자열의 갯수를 저장하는 것을 생각했다.
점화식이 생각이 안났고 그래서 2차원 DP로 생각했다.
대충 중간을 K라고 잡고 0~K, K+1~L-1 이렇게 해야한다는 건 대충 이해했다.
하지만 점화식 생각이 도저히 안났다.

아이디어는 D[n]이 길이 n의 올바른 괄호 개수라면
0                      i                L
( -------------------- )[               ]
처음의 여는 괄호에 대응되는 닫는 괄호가 i 번째에 위치한다면 그 안에 있는 ---------------------영역은 D[i-2]
그리고 [     ] 영역은 전체 n에서 i만큼 빠지므로 D[n - i]가 된다.

따라서 D[n] = D[i-2] * D[n - i]이고
정답을 인정받으려면 n이 증가할수록 카운트가 급증하기 때문에 
long long 자료형에 % 1,000,000,007을 한번에 해주면 이미 해주기 전에 값이 long long 범위를 초과하여 쓰레기 값이 되므로
매번 더해질때마다 해줘야 함.
*/

#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX = 5000 + 1;
const int MOD = 1000000007;

int L;
//cache[i]=길이가 i인 괄호문자열 갯수
long long cache[MAX];

long long solve(int length) {
    //기저 사례
    if (length == 0)
        return 1;

    long long& ret = cache[length];
    if (ret != -1)return ret;

    ret = 0;
    //점화식 D[n] = D[i-2] * D[n - i]
    for (int i = 2; i <= length; i += 2) {
        ret += (solve(i - 2) * solve(length - i));
        ret %= MOD;
    }
    return ret % MOD;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        memset(cache, -1, sizeof(cache));
        cin >> L;
        //홀수인 괄호문자열은 성립 안한다.
        if (L % 2 == 1)
            cout << 0 << "\n";
        else
            cout << solve(L) << "\n";
    }
    return 0;
}