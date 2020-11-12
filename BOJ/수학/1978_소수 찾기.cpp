/*
소수 찾는 알고리즘.
소수관한 문제를 제대로 못풀었는데 동빈나 유튜브를 보면서 이번 기회에 제대로 연습했다.
*/

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;


int isPrimeNumber(int x) {
    if (x != 1) {
        int end = (int)sqrt(x);
        for (int i = 2; i <= end; i++) {
            if (x % i == 0)return 0;
        }
        return 1;
    }
    return 0;

}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, num, result = 0;
    vector <int> v;

    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> num;
        v.push_back(num);
        result += isPrimeNumber(v[i]);
    }

    cout << result;

    return 0;
}