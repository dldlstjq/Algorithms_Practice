/*
투 포인터 알고리즘을 이용하면 풀 수 있다.
코드 참고
*/
#include <iostream>

using namespace std;
#define MAX 100001

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, s;
    int arr[MAX] = { 0 };
    int cnt;

    cin >> n >> s;
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    int result = 0, sum = 0, low = 0, high = 0;
    int min = 999999999;
    while (1) {
        //투 포인터 알고리즘
        //1. 현재 부분합이 s이상이거나 이미 high==n이면 low++
        //2. 그렇지 않다면 high++
        //3. 부분합이 s이상인 경우 길이 체크. 
        //이미 high가 포인터 하나 앞서있기 때문에 (high-1)-low+1를 해야 길이 나옴
        if (sum >= s) {
            if (min > high - 1 - low + 1)
                min = high - 1 - low + 1;
            sum -= arr[low++];
        }

        else if (high == n)
            break;
        else
            sum += arr[high++];

    }

    //min이 999999999면 합을 만드는것이 불가능
    if (min == 999999999)
        cout << 0;
    else
        cout << min;
    return 0;
}