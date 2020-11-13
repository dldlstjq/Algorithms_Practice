/*
문제를 보자마자 모든 순열마다 값을 구해서 최대를 구하면 된다는 걸 알았다.
문제는 순열을 구현하는 건데 함수를 직접 짜다가 안돼서 검색해보니 C++에서 next_permutation이라고 순열 함수를 제공했다.
다시 한번 코테 준비를 C++로 하라는 이유를 알았다...
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vector<int> v(n);

    for (int i = 0; i < n; i++)
        cin >> v[i];

    int max = 0;

    //정렬 후 next_permutation 이용해 순열 마다 제일 큰 차 구함
    sort(v.begin(), v.end());
    do {
        int sum = 0;
        for (int i = 1; i < n; i++) {
            sum += abs(v[i - 1] - v[i]);
        }
        if (max < sum)
            max = sum;

    } while (next_permutation(v.begin(), v.end()));

    cout << max;

    return 0;
}