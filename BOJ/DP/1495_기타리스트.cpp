/*
정답과 거의 비슷하게 따라갔는데 디테일한 부분에서 잘 되지 않았다.
우선 재귀를 이용하면 현재 노래번호에 1씩 더해주면 자동으로 반복문을 실행한것처럼 되는데
재귀함수 안에서 또 반복문으로 1씩 더해주는 걸 넘기다보니 답이 제대로 안나온 것 같다.

또 "'계산 한적 없다'와 '불가능'한 경우를 다른 숫자로 표현하는 것이 핵심입니다.
둘 다 -1로 표현한다면 메모이제이션이 정상적으로 처리하지 못하여 시간초과가 발생하기 때문입니다" 라고 한다.

기저사례 처리 시 인덱스보다 볼륨 오버를 먼저 처리해야하고 볼륨을 더할지 뺄지를 한번에 비교해야
시간초과를 안 받았다. 볼륨 더하고 빼는걸 따로 처리하니 시간초과를 받았다.
*/

#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int n, s, m;
int volume[101];

//cache[i][j]=i번째 곡 연주할 때 현재 볼륨이 j일때 최대 볼륨
int cache[101][1001];

//idx는 노래 번호, now는 현재 소리
int solve(int idx, int now) {
    //현재 볼륨이 최대보다 넘거나 0보다 작을 경우 먼저 처리해야 한다.
    //노래 번호가 n번째 일떄 부터 처리하면 볼륨 오버를 처리할 수 없다.
    if (now > m || now < 0)
        return -100;    //메모이제이션 판별 수(-1)와 같을 경우 시간 초과

    if (idx == n)
        return now;

    int& ret = cache[idx][now];
    if (ret != -1)return ret;

    //max(volume[idx+1]만큼 더할 경우, volume[idx+1]만큼 뺄 경우)
    ret = max(solve(idx + 1, now + volume[idx + 1]), solve(idx + 1, now - volume[idx + 1]));
    return ret;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    memset(cache, -1, sizeof(cache));

    cin >> n >> s >> m;
    for (int i = 1; i <= n; ++i)
        cin >> volume[i];

    int ans = solve(0, s);
    if (ans == -100)
        cout << -1;
    else
        cout << ans;
    return 0;
}