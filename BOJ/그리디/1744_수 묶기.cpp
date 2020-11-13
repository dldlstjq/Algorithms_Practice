/*
0과 1 처리가 어려워 풀지 못했다.

1. 1과 곱하면은 손해이기 때문에 1은 무조건 더합니다. 따라서, 1의 개수를 더해줍니다.
2. 양수는 내림차순으로 저장하고 음수는 오름차순으로 저장해야 두 수를 곱했을 때 최대가 됩니다.
3. 무조건 두 수를 곱한다고 가정하기 때문에 우선순위 큐(벡터)의 크기가 홀수일 경우 오류가 발생합니다.

i) 따라서, 양수가 저장되어있는 우선순위 큐 크기가 홀수이면 1을 넣어줘 짝이 없는 양수를 그대로 더해주게 합니다.
ii) 음수가 저장되어있는 우선순위 큐 크기가 홀수이면 입력받은 숫자 중에 0이 있었을 경우 0을 넣어줘 0을 더해주게 하고 없었다면 i)처럼 1을 넣어줘 짝이 없는 음수를 그대로 더해주게 합니다.

나는 벡터를 이용해 문제해결했다. 양수와 음수의 경우 오름차순으로 정렬해서 곱해도 상관없음.
벡터의 크기를 짝수로 맞춰주는 것, 0이랑 1 처리를 잘하면 풀 수 있었을 것 같다.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define MAX 10000
int n;
int arr[MAX];

//양수, 음수의 개수 홀수면 1 추가해서 높은 숫자부터 2개씩 곱해줌
int sum(vector<int>& arr, int num) {
    int result = 0;
    if (num % 2 == 1) {
        arr.push_back(1);
        sort(arr.begin(), arr.end());
        for (int i = 0; i < arr.size(); i += 2) {
            result += arr[i] * arr[i + 1];
        }
    }

    else {
        sort(arr.begin(), arr.end());
        for (int i = 0; i < arr.size(); i += 2) {
            result += arr[i] * arr[i + 1];
        }
    }
    return result;
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    vector<int> pos;   //양수저장
    vector<int> neg;   //음수저장
    int one = 0, zero = 0;        //0, 1 개수 저장

    //0,1은 따로 카운트 해줌
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        if (arr[i] > 1)
            pos.push_back(arr[i]);
        else if (arr[i] < 0)
            neg.push_back(arr[i]);
        else if (arr[i] == 1)
            one++;
        else if (arr[i] == 0)
            zero++;
    }


    int sum1 = 0, sum2 = 0;
    //양수의 경우 짝수면 두개씩 곱하고 홀수면 1 추가해서 곱함
    sum1 = sum(pos, pos.size());

    //음수 개수 홀수일때
    //0이 있으면 0, 없으면 1 삽입
    if (neg.size() % 2) {
        zero == 0 ? neg.push_back(1) : neg.push_back(0);
    }

    sum2 = sum(neg, neg.size());

    cout << sum1 + sum2 + one;


    return 0;
}