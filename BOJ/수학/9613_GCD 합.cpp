/*
유클리드 호제법으로 최대공약수 구하면 됨.
처음에 sum을 int형으로 했다가 틀림.
*/
#include <iostream>
#include <vector>

using namespace std;

int get_gcd(int a, int b) {
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

    int n, gcd, lcm;
    int t, a;
    long long sum = 0;
    vector <int> v;

    cin >> t;

    while (t--) {
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a;
            v.push_back(a);
        }
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                gcd = get_gcd(v[i], v[j]);
                sum += gcd;
            }
        }

        cout << sum << '\n';
        sum = 0;
        v.erase(v.begin(), v.end());
    }

    return 0;
}