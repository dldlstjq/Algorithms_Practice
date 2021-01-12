#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//재귀함수로 푼 풀이. 기본적인 알고리즘은 반복문으로 푼 것과
//비슷하고, ret을 해당 인덱스의 값으로 잡아준다.
//그리고 다음 인덱스에 해당하는 값이 더 크면 그 값을 더해준다.
//메인 함수에서 실행할 때 배열의 모든 인덱스를 순회하면서 실행해야
//가장 큰 값을 구할 수 있다.
int n;
int A[1001];
int cache[1001];

int lis(int start) {
    int& ret = cache[start];
    if (ret != -1)return ret;
    ret = A[start];
    for (int i = start + 1; i < n; ++i)
        if (A[start] < A[i])
            ret = max(ret, lis(i) + A[start]);
    return ret;
}


int dp[1001];

int maximum(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int a[1001] = { 0 };
    int n, max = 0;
    int i, j;
    cin >> n;

    for (int i = 1; i <= n; i++)
        cin >> a[i];

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {

            //10 20 10 30 의 경우 10+20+30이 10+30보다 크기 때문에
            //maximum으로 비교해줌
            if (a[i] > a[j]) {
                dp[i] = maximum(a[i] + dp[j], dp[i]);
            }
        }
        if (dp[i] > max)
            max = dp[i];
    }

    cout << max << '\n';

    return 0;
}