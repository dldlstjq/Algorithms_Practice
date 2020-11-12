/*
처음에 문제 이해를 잘 못해 헤맸는데 인터넷 찾아서 겨우 이해함.
-2로 나누면서 나머지가 0이면 벡터나 문자열에 추가하고 n을 -2로 나눠줌.
n이 양수면 -2로 나눈 나머지를 다시 저장하고 음수면 밑에 코드대로 계산해서 추가.
마지막으로 reverse로 뒤집어서 출력.
다른 코드를 찾아보니 백준님이 푼 방법이 있었는데 재귀함수 이용해서 더 간단하게 품. 밑에 코드 추가
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    int minus;
    string str = "";
    vector <int> v;

    cin >> n;

    minus = -1 * 2;
    if (n == 0)
        cout << 0;

    else {
        while (n != 0) {
            if (n % minus == 0) {
                //str += to_string(n % minus);
                v.push_back(n % minus);
                n /= minus;
            }
            else {
                if (n < 0) {
                    int tmp = (n / minus) + 1;
                    //str += to_string((n - (minus * tmp)));
                    v.push_back(n - (minus * tmp));
                    n = tmp;
                }
                else {
                    //str += to_string(n % minus);
                    v.push_back(n % minus);
                    n /= minus;
                }
            }
        }

        reverse(v.begin(), v.end());
        for (int i = 0; i < v.size(); i++)
            cout << v[i];
        // cout << str;
    }

    return 0;
}


/////////////////////////////////////////
/*
백준 풀이
*/

#include <cstdio>
void go(int n)
{
    if (n == 0)
        return;

    if (n % 2 == 0)
    {
        go(-(n / 2));
        printf("0");
    }
    else
    {
        if (n > 0)
            go(-(n / 2));
        else
            go((-n + 1) / 2);

        printf("1");
    }
}
int main() {
    int n;

    scanf("%d\n", &n);

    if (n == 0)
        printf("0\n");
    else
        go(n);
}