/*
1676 팩토리얼 0의 개수와 비슷한 문제.
nCm 은 n! / (m!(n-m)!) 로 나타낼 수 있기 때문에
n!, m!, (n-m)!의 2와 5 개수를 구하는 방법을 똑같이 써주고 
원하는 결과는 min(n!의 2의 개수 - m!의 2의 개수 - (n-m)!의 2의 개수, n!의 5의 개수 - m!의 5의 개수 - (n-m)!의 5의 개수)
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

pair<long long, long long> zero(long long n) {
    long long two = 0, five = 0;
    for (long long i = 2; i <= n; i *= 2) {
        two += n / i;
    }
    for (long long i = 5; i <= n; i *= 5) {
        five += n / i;
    }
    return (pair<long long, long long>(two, five));
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    long long n, m;
    pair<long long, long long> ans_n, ans_m, ans_nm;

    cin >> n >> m;

    ans_n = zero(n);
    ans_m = zero(m);
    ans_nm = zero(n - m);

    long long two = 0, five = 0;
    two = ans_n.first - ans_m.first - ans_nm.first;
    five = ans_n.second - ans_m.second - ans_nm.second;

    cout << min(two, five);
    return 0;
}