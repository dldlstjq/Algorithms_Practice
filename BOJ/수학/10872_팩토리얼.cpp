/*
재귀함수로 팩토리얼 구현
*/
#include <iostream>

using namespace std;

int factorial(int n) {
    if (n <= 1)
        return 1;
    else
        return n * factorial(n - 1);
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;

    cin >> n;

    cout << factorial(n);

    return 0;
}