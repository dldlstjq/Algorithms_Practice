/*
유클리드 호제법으로 최대공약수 구해서 최소공배수 구해주면 됨
*/
#include <cstdio>

using namespace std;

int get_gcd(int a, int b) {
    while (b != 0) {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int get_lcm(int a, int b, int c) {
    return a * b / c;
}


int main() {
    int a, b, gcd, lcm;
    int t;
    scanf("%d", &t);

    while (t--) {
        scanf("%d %d", &a, &b);

        gcd = get_gcd(a, b);
        lcm = get_lcm(a, b, gcd);

        printf("%d\n", lcm);
    }

    return 0;
}