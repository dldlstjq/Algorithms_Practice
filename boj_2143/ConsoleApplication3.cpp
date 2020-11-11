#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <utility>
#include <map>

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