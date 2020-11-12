//자리수가 int형 초과해서 long long으로 해야 정답
#include <iostream>

using namespace std;

long long get_gcd(long long a, long long b) {
    while (b != 0) {
        long long r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    long long a, b, gcd, lcm;

    cin >> a >> b;
    gcd = get_gcd(a, b);
    for (int i = 0; i < gcd; i++)
        cout << "1";

    return 0;
}