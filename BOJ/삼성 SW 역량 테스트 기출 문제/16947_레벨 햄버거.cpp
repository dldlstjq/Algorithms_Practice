/*
예제입력을 보고 직접 문자열을 구할 수 없어 보였다.
이전 버거가 현재 버거 중간에 끼어 들어가기 때문에 재귀풀이를 생각했다.
재귀를 사용하려니 버거 인덱스 설정을 어떻게 해야하는지 생각이 안났다.
다른 사람의 풀이를 참고해 대략 어떻게 해결해 나갈지 알 수 있었다.

전체 재료수와 패티수를 저장한 다음 재귀를 돌려 x의 위치가 어디인지에 따라
패티 수를 반환하면 된다.
*/

#include <iostream>
#include <algorithm>

using namespace std;

int N;
long long X;
long long burger[51];   //전체 재료 수
long long p[51];    //패티 수


long long solve(int n, long long x) {
    if (n == 0) {
        if (x == 0)return 0;
        if (x == 1)return 1;
    }
    //0        1          2        3          4      
    //1 + burger[i - 1] + 1 + burger[i - 1] + 1

    //0: 1번째는 무조건 햄버거 번
    if (x == 1)
        return 0;

    //1: 가운데 패티 이전에까지 먹으면 -1하고 재귀
    else if (x <= 1 + burger[n - 1])
        return solve(n - 1, x - 1);

    //2: x가 가운데 패티이면 이전 패티갯수+1
    else if (x == 1 + burger[n - 1] + 1)
        return 1 + p[n - 1];

    //3: 가운데 패티 갯수+ 이전 패티 갯수를 구하기 위해 위치에서 빼준다.
    else if (x <= 1 + burger[n - 1] + 1 + burger[n - 1])
        return 1 + p[n - 1] + solve(n - 1, x - 1 - burger[n - 1] - 1);

    //4: 전체 다 먹으면 n번째 패티값
    else
        return p[n];

}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> X;

    //lv0은 패티 한장
    burger[0] = 1;
    p[0] = 1;

    //전체 레이어와 패티 수를 구한다.
    for (int i = 1; i <= N; ++i) {
        burger[i] = 1 + burger[i - 1] + 1 + burger[i - 1] + 1;
        p[i] = p[i - 1] * 2 + 1;
    }
    cout << solve(N, X);

    return 0;
}