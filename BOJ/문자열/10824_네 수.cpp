/*
처음에 int형으로 입력 받았다가 런타임 에러남.

각 수는 1,000,000 까지 입력이 가능하다.
ABCD모두 1,000,000이 입력된 경우에는 2,000,000 * 2,000,000 = 4,000,000,000,000 까지 최대값이 나올 수 있다.
따라서 long long으로 변환해야 정답.

난 처음부터 long long으로 입력 받았는데 a,b,c,d는 int형으로 받고 변환할때 long long으로 변환하는게 더 나은거 같다.
*/
#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    long long a, b, c, d;
    long long result;
    string s1, s2;

    cin >> a >> b >> c >> d;

    s1 = to_string(a);
    s2 = to_string(b);
    s1 += s2;

    result = stoll(s1);

    s1 = to_string(c);
    s2 = to_string(d);
    s1 += s2;

    result += stoll(s1);

    cout << result;

    return 0;
}