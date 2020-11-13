/*
완전탐색을 풀 때 썼던 기법을 다 생각해봤는데 떠오르는 알고리즘이 없었다.
앞서 푼 1182나 6603 문제를 활용하려 해도 잘 안돼서 인터넷에 쳐보니 투 포인터 알고리즘이라는 것이 있었다.
투 포인터 알고리즘을 쓰면 쉽게 해결된다.

투 포인터 알고리즘
1차원 배열이 있고 이 배열에서 각자 다른 원소를 가리키고 있는 2개의 포인터를 조작해가며 원하는 것을 얻는 형태
조건
 - 모든 원소가 다 자연수이기 때문에 성립합니다.

*/
#include <iostream>

using namespace std;
#define MAX 10001
int n, m;
int arr[MAX];
int cnt;


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    int result = 0, sum = 0, low = 0, high = 0;
    while (1) {
        //투 포인터 알고리즘
        //1. 현재 부분합이 m이상이거나 이미 high==n이면 low++
        //2. 그렇지 않다면 high++
        //3. 현재 부분합이 m 과 같으면 결과+1
        if (sum >= m)
            sum -= arr[low++];
        else if (high == n)
            break;
        else
            sum += arr[high++];
        if (sum == m)
            cnt++;
    }
    cout << cnt;
    return 0;
}