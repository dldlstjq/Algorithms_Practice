/*
첫번째로 승률 계산을 위해 자료형을 double로 두고 계산했다.
거기서 일단 자료형 변환에 어려움이 있었다.
두번째로 승리를 하면 게임 수도 늘어나야 되는데 그걸 고려하지 못해 승리 횟수만 증가하는 식으로 코드를 짰다.
문제 이해를 잘못함으로써 문제해결에 어려움을 겪었다.

그리고 이분탐색방법으로 접근해서 문제를 풀어 승리 횟수만 증가하는 식으로 가다보니 예제의 답이 이해가질 않았다.
승률이 넘을때 까지 게임횟수를 늘려야 하는데 이분탐색방법으로는 게임횟수가 늘지 않으니 문제가 해결될 리 없었다.
아직까지 이분법에 많이 익숙하지 않다는 걸 느꼈다.
*/

#include <iostream>

using namespace std;

long long L = 2000000000;

long long N;  //플레이 횟수
long long M;  //승리 횟수

//n게임 중 m게임 이겼을 때 승률
int percent(long long n, long long m) {
    return (m * 100) / n;
}

int win_Rate(long long n, long long m) {
    if (percent(n, m) == percent(n + L, m + L))
        return -1;
    long long low = 0, high = L;

    //반복문 불변식
    //1. low 게임 이기면 승률은 변하지 않는다.
    //2. high 게임 이기면 승률은 변한다.
    while (low + 1 < high) {
        long long mid = (low + high) / 2;
        if (percent(n, m) == percent(n + mid, m + mid))
            low = mid;
        else
            high = mid;
    }
    return high;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;

    while (T--) {
        cin >> N >> M;
        cout << win_Rate(N, M) << "\n";
    }

    return 0;
}