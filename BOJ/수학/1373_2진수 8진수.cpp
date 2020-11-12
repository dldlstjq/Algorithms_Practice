/*
처음엔 뒤에서 부터 3자리씩 끊어서 계산하면서 진법 변환 했는데 틀림.
백준 강의에서 더 간단하게 풀이한 코드.
무작정 달려들기보다 조금 더 컴퓨팅적 생각을 해야겠다는 느낌을 받음...
*/

#include <iostream>
#include <string>

using namespace std;

int main() {
    string s;
    cin >> s;

    int n = s.size();

    if (n % 3 == 1)
        cout << s[0];
    else if (n % 3 == 2)
        cout << (s[0] - '0') * 2 + (s[1] - '0');

    for (int i = n % 3; i < n; i += 3)
        cout << (s[i] - '0') * 4 + (s[i + 1] - '0') * 2 + (s[i + 2] - '0');

    cout << '\n';
}



//////////////////////////////////////
/*
처음에 풀었던 풀이. 오답 처리 받음
*/
#include <iostream>
#include <cstdio>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string n;
    long long result = 0;
    vector <int> v;

    cin >> n;


    //뒤에서 부터 3자리씩 끊어서 계산. 
    //마지막에 3으로 떨어지지 않으면 while 벗어나서 계산 
    int i = n.size() - 1;
    while (1) {
        int k = 0;
        for (int j = i; j >= i - 2; j--) {
            n[j] = n[j] - 48;
            result += n[j] * pow(2, k++);
        }
        v.push_back(result);
        if (i - 3 < 2) {
            break;
        }
        else {
            i -= 3;
            result = 0;
        }
    }

    //i가 0 or 1 인덱스에 있는경우 하나씩 계산.
    //i가 2이상이면 2, 1, 0 3개 가능하므로 제외
    if (i - 3 < 2) {
        i -= 3;
        for (int j = i; j >= 0; j--) {
            int k = 0;
            n[j] = n[j] - 48;
            result += n[j] * pow(2, k++);
        }
        v.push_back(result);
    }

    for (int j = v.size() - 1; j >= 0; j--)
        cout << v[j];

    return 0;
}