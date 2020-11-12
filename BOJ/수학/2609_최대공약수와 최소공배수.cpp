/*
처음에는 1부터 n까지 하나씩 다 나눠서 떨어지는 것 중 제일 큰 수를 최대공약수로 구함.
유클리드 호제법 이용하면 더 쉽게 풀이 가능.
두 수의 최소공배수는 a*b/최대공약수 하면 구할 수 있음.
그냥 알고리즘 자체 외우는게 좋을듯.
*/

#include <stdio.h>
using namespace std;

int a, b;

int gcd(int a, int b) {
    if (a % b == 0)
        return b;
    else
        return gcd(b, a % b);
}

int main() {
    scanf("%d %d", &a, &b);
    int g = a > b ? gcd(a, b) : gcd(b, a);
    printf("%d\n%d", g, a * b / g);
    return 0;
}