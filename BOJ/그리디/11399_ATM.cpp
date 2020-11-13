/*
쉬운 그리디 문제.
인출에 걸리는 시간이 짧은 순으로 정렬해서 시간 더하면 최소가 된다. 
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, sum = 0;
    cin >> n;
    vector<int> v(n);

    for (int i = 0; i < n; i++)
        cin >> v[i];

    //정렬해서 작은 수부터 차례로 더한다
    sort(v.begin(), v.end());

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            sum += v[j];
        }
    }

    cout << sum;
    return 0;
}