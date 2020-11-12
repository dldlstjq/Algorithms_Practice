/*
첫 풀이방법.
2*5만 고려하여 단순하게 풀어서 틀림.

팩토리얼이 결국 곱으로 이루어진 연산이기 때문에 그리고 0은 10을 얼마나 곱하느냐에 따라 결정이 되기 때문에
팩토리얼을 이루는 수의 소인수 중에서 2와 5의 개수에 따라 결정이 된다.

정리를 하면
N! = 1 x 2 x 3 x ... x N

ex) 10! = 3628800
10! = 1 x 2 x 3 x 4 x 5 x 6 x 7 x 8 x 9 x 10
10! = 1 x 2 x 3 x (2 x 2) x 5 x (2 x 3) x 7 x (2 x 2 x 2) x (3 x 3) x (2 x 5)
10! = 2^8 x 3^4 x 5^2 x 7
10! = (2^2 x 5^2) x 2^6 x 3^4 x 7
10! = 10^2 x 2^6 x 3^4 x 7

2와 5의 개수 중 작은 값이 10의 개수 (0의 개수)가 된다.
따라서 0의 개수를 구할 때에는 2의 개수와 5의 개수를 구하고 그 중 작은 값이 결과값이 된다.

주의할 점은 2와 5의 제곱수들은 포함하는 2와 5의 갯수가 더 많다는 것이다.
예를 들면 4 = 2 x 2, 25 = 5 x 5 … 이므로 개수를 더 세어주어야 한다.
*/

/*정답 풀이*/
#include <stdio.h>

int main()
{
    int n;
    int two = 0, five = 0;
    int i;

    scanf("%d", &n);

    for (i = 2; i <= n; i *= 2) {
        two += n / i;
    }
    for (i = 5; i <= n; i *= 5) {
        five += n / i;
    }

    printf("%d\n", (two < five) ? two : five);

    return 0;
}






/////////////////////////////////////////
/*내가 푼 틀린 풀이*/
#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;


int fact[510];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;

    cin >> n;
    int num = 0;
    //0~4: 1개 5~9:2개 10~14:3개 15~19:4개 이런식으로 늘어남
    for (int i = 0; i < 501; i += 5) {
        for (int j = i; j < i + 5; j++)
            fact[j] = num;
        num++;
    }

    cout << fact[n];

    return 0;
}