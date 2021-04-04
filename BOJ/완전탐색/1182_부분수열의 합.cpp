/*
6603 로또 문제와 비슷한 문제여서 풀 수 있을 것 같았다.
처음 풀 때 인덱스만 넘겨주었는데 잘 안 풀렸다. sum을 같이 변수로 넘겨줘야 문제가 해결 됐다.
거의 다 풀 줄 알았는데 아직 연습이 더 필요하다는 것을 다시 깨달았다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define MAX 21
int arr[MAX];
int N, S;
int cnt;

/* 첫 풀이. 
void dfs(int idx) {
    if (sum == S) {
        cnt++;
        return;
    }

    for (int i = idx; i < N; i++) {
        sum += arr[idx];
        dfs(idx + 1);
        sum -= arr[idx];
    }

}
*/
void dfs(int idx, int sum) {
    sum += arr[idx];    //해당 idx 숫자 더함
    //범위 초과시 종료
    if (idx >= N)
        return;
    //조건만족 시 카운트
    if (sum == S) {
        cnt++;
    }

    //숫자 더한 경우
    dfs(idx + 1, sum);
    //안 더한 경우
    dfs(idx + 1, sum - arr[idx]);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> S;
    for (int i = 0; i < N; i++)
        cin >> arr[i];

    //여기서 반복문으로 0~N-1까지 다 돌리면 정확한 값이 안나온다.
    //dfs 내부 dfs(idx + 1, sum - arr[idx]); --> 여기서 idx=0에서 sum-arr[idx]=0이 되어 카운트된다.
    dfs(0, 0);
    cout << cnt;
    return 0;
}