/*
문제 이해도 그렇게 어렵지 않았고 풀이도 금방 생각났다.
인덱스와 합을 인자로 해서 하나씩 더하거나 빼서 조건에 만족하게 만들면 됐다.
처음 제출했을 때는 틀렸는데 solve를 호출할 때 solve(0,0)으로 넣어줬다.
arr[0]는 시작숫자이기 때문에 sum이 arr[0]부터 시작해야 맞는 답이 나왔다.
단순히 solve(0,0) 을 넣어주면 중복 계산을 해서 2가 아닌 4라는 값이 나왔다.
*/

#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX = 100 + 1;
int n;
int arr[MAX];
long long cache[MAX][MAX];

long long solve(int idx, int sum) {
    //sum이 음수이거나 20을 넘어가면 안된다.
    if (sum < 0 || sum > 20)
        return 0;
    //제일 마지막 인덱스이고 원소가 sum이랑 같으면 등식 성립
    if (idx == n - 1 && arr[idx] == sum)
        return 1;

    //제일 마지막 원소가 sum이랑 다르면 안됨
    if (idx == n - 1 && arr[idx] != sum)
        return 0;

    long long& ret = cache[idx][sum];
    if (ret != -1)return ret;
    ret = 0;

    //각 식에 더하고 빼는 과정을 모두 합한다.
    ret = solve(idx + 1, sum + arr[idx]) + solve(idx + 1, sum - arr[idx]);
    return ret;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    memset(cache, -1, sizeof(cache));
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> arr[i];
    //맨 처음 원소가 sum에 포함된 채로 시작해야한다.
    cout << solve(1, arr[0]);
    return 0;
}