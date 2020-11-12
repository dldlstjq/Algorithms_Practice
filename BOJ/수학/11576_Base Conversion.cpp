/*
진법 변환 부분을 함수로 만들어 푸는 방법도 있음.
*/

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//진법변환 함수
void conversion(int a, int b) {
    if (a < b) {
        cout << a << " ";
    }
    else {
        conversion(a / b, b);
        cout << a % b << " ";
    }
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int a, b, m, num;
    long long result = 0;

    vector <long long> v;

    cin >> a >> b;
    cin >> m;

    for (int i = 0; i < m; i++) {
        cin >> num;
        v.push_back(num);
    }

    //10진법으로 먼저 바꿔줌
    int j = 0;
    for (int i = v.size() - 1; i >= 0; i--) {
        result += v[i] * pow(a, j);
        j++;
    }
    //b 진법 저장하기 위해 벡터 비워줌
    v.erase(v.begin(), v.end());

    //결과 0이면 0출력 아니면 진법 변환
    if (result == 0)
        cout << 0;
    else {
        while (result != 0) {
            v.push_back(result % b);
            result /= b;
        }
        reverse(v.begin(), v.end());
        for (int i = 0; i < v.size(); i++)
            cout << v[i] << " ";
    }

    //함수를 통해 진법 변환
    //conversion(result, b);

    return 0;
}