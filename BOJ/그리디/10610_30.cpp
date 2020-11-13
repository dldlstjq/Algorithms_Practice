/*
처음엔 가능한 모든 수가 30의 배수가 되는지 아닌지 확인하는 쪽으로 접근했다.
그러다 보니 0이 맨 앞에 오면 안되고 0이 2개이상 일때는 어떻게 해야하는지 등 고려해야할 부분이 많아서 못 풀었다.

30의 배수가 되는 조건은 자리수를 다 더해서 3의 배수이고 숫자 중 0이 있어야 된다는 것을 알았다.
두 조건을 확인해서 내림차순으로 출력하면 풀 수 있다.
*/

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

bool cmp(int a, int b) {
    return a > b;
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string num;
    cin >> num;

    //자리수 다 더함. 0이 있는지 체크
    long long sum = 0;
    bool flag = false;

    for (int i = 0; i < num.length(); i++) {
        if (num[i] == '0')
            flag = true;
        sum += num[i] - '0';
    }

    //자리수가 3의 배수이고 0이 있으면 30의 배수
    if (sum % 3 == 0 && flag == true) {
        sort(num.begin(), num.end(), cmp);  //내림차순으로 정렬해서 출력
        cout << num;
    }

    else
        cout << -1;

    return 0;
}