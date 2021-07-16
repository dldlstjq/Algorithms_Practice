/*
처음엔 dp로 접근해서 오르막길 길이를 구하고 높이차를 구했다.
그랬더니 시간초과가 났다.

다시 생각해보니 굳이 dp를 안쓰고 그냥 하나씩 계산해보면 쉽게 구할 수 있었다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 1000 + 1;
int N;
int h[MAX];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> h[i];

    int ret = 0;
    for (int i = 0; i < N; ++i) {
        int start = h[i];   //높이 시작
        int diff = 0;       //높이 차
        for (int j = i + 1; j < N; ++j) {
            //start보다 높은 위치에 있고 오르막길이면 높이 차 구함
            if (start < h[j] && h[j - 1] < h[j])
                diff = h[j] - start;
            else
                break;
        }
        ret = max(ret, diff);
    }

    cout << ret;
    return 0;
}


//////////////////////////////
//첫 dp풀이
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAX = 1000 + 1;
int N;
int h[MAX];
int cache[MAX];

//오르막길이 있는지 구한다.
int solve(int idx) {
    //다음 길이 작거나 같으면 오르막길 아니다.
    if (h[idx] >= h[idx + 1])
        return 0;

    int& ret = cache[idx];
    if (ret != -1)return ret;

    ret = 0;
    if (h[idx] < h[idx + 1])
        ret += solve(idx + 1) + 1;
    return ret;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> h[i];

    //오르막길 크기를 구한다.
    memset(cache, -1, sizeof(cache));
    for (int i = 0; i < N - 1; ++i)
        solve(i);

    //오르막길 크기 구한다.
    int ans = 0;
    //cache[i]가 -1이 아니면 오르막길이 존재한다.
    //cache[i]에는 i번째부터 오르막길 길이가 있다.
    //즉 i ~ i+cache[i] 까지가 오르막길이다.
    //오르막길 높이를 구하고 i를 cache[i]+1만큼 옮겨줘서 i~ i+cache[i] 사이에 있는 값들은 넘어간다.
    for (int i = 0; i < N - 1; i += cache[i] + 1)
        if (cache[i] != -1) {
            ans = max(ans, h[i + cache[i]] - h[i]);
        }

    cout << ans;
    return 0;
}