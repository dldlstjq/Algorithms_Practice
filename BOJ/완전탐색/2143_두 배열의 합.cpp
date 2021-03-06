﻿/*
A, B 각 배열에 대한 부 배열을 구해 합을 저장한다.
그 후 A 부 배열의 원소와 B 부 배열의 원소를 더해 T를 만족하는 것을 lower, upper_bound를 이용해 찾는다.
*/

// 2021.07.01 완전탐색으로 분류되어 있어서 완탐을 쓰려 했는데 부분합을 이용해야 했다.
// 부 배열은 연속된 인덱스가 부 배열이다. 따라서 0,3 이렇게 떨어진 배열은 부 배열이 아니다.
// 각 배열의 모든 부분 합을 구해서 lower_bound, upper_bound를 써서 구하면 답이 나오는데 lower, upper_bound를 안쓴지 오래돼서 생각이 안났다.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define MAX 1001
long long T;
int n, m;
long long A[MAX];
long long B[MAX];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> T;
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> A[i];

    cin >> m;
    for (int i = 0; i < m; ++i)
        cin >> B[i];

    vector<long long> v1;   //A 부 배열
    vector<long long> v2;   //B 부 배열
    long long sum = 0;
    int low = 0, high = 0;

    //A 부 배열 합
    for (int i = 0; i < n; ++i) {
        long long sum = A[i];
        v1.push_back(sum);
        for (int j = i + 1; j < n; ++j) {
            sum += A[j];
            v1.push_back(sum);
        }
    }

    //B 부 배열 합
    for (int i = 0; i < m; ++i) {
        long long sum = B[i];
        v2.push_back(sum);
        for (int j = i + 1; j < m; ++j) {
            sum += B[j];
            v2.push_back(sum);
        }
    }

    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());

    long long result = 0;   //결과값
    for (int i = 0; i < v1.size(); ++i) {
        long long lower = lower_bound(v2.begin(), v2.end(), T - v1[i]) - v2.begin();
        long long upper = upper_bound(v2.begin(), v2.end(), T - v1[i]) - v2.begin();
        result += (upper - lower);
    }

    cout << result;

    return 0;
}