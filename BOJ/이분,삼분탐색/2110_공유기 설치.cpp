/*
처음에 문제 이해를 못했다. 
이진탐색이면 low, high 두 변수로 탐색하는데 이번에는 세 개의 공유기를 설치한다 해서 변수를 세개 써야하나 고민했다.
최소거리를 left, 최대거리를 right로 잡고 이분탐색하며 조건을 만족하는 거리 중 최대를 출력하면 된다.

- 풀이방법
1. 주어진 집들의 좌표는 정렬되어있지 않으므로 정렬을 합니다.
2. 최소 거리는 1, 최대 거리는 처음 집과 마지막 집 사이의 거리입니다.
3. 이분 탐색을 진행하는데 해당 간격으로 공유기를 설치할 때 조건을 충족하는지 확인합니다.
4. 3번에서 조건을 충족하는 거리 중 최대를 출력합니다.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define MAX 200001
int n, c;
int v[MAX];
bool check(int mid) {
    //v[0]를 제일 처음으로 설정
    int prev = v[0];
    int cnt = 1;

    //두번째 원소부터 집 사이의 거리가 mid 이상인지 확인
    for (int i = 1; i < n; i++) {
        if (v[i] - prev >= mid) {
            cnt++;
            prev = v[i];
        }
    }
    //c개 이상 설치 할 수 있으면
    if (cnt >= c)
        return true;
    return false;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);


    cin >> n >> c;

    for (int i = 0; i < n; i++)
        cin >> v[i];

    sort(v, v + n);

    //low는 가능한 최소거리인 1, high는 최대에서 최소 거리를 뺸 값을 설정
    int low = 1, high = v[n - 1] - v[0];
    int ans = 0;
    while (low <= high) {
        int mid = (low + high) / 2;

        //mid 이상의 간격으로 공유기 3개 설치할 수 있는지 확인
        if (check(mid)) {
            ans = max(ans, mid);
            low = mid + 1;
        }
        else
            high = mid - 1;
    }
    cout << ans;
    return 0;
}