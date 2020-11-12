/*
스택을 활용해서 품.
n을 b로 나눈 나머지를 스택에 넣고 숫자에 따라 알파벳으로 변환하여 출력
*/

#include <cstdio>
#include <stack>

using namespace std;

int main() {
    long long n = 0;
    int b;
    stack <int> s;

    scanf("%lld %d", &n, &b);

    while (n != 0) {
        s.push(n % b);
        n /= b;
    }
    int len = s.size();
    for (int i = 0; i < len; i++) {
        if (s.top() >= 10) {
            s.top() = s.top() + 'A' - 10;
            printf("%c", s.top());
        }
        else
            printf("%d", s.top());
        s.pop();
    }
    return 0;
}