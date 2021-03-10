/*
9251_LCS 랑 똑같은데 긴 문자열을 직접 찾아서 출력해야 한다.
종만북에서 직접 최적해를 구하는 부분이 있는데 이 부분을 다시 보면서 익혀야 할 필요성을 느꼈다.

reconstrcut함수는 메모이제이션 할 때와 비슷하게 범위를 벗어나면 종료,
같은 문자면 ans에 더해준다. 그리고 인덱스를 추가했을 때 길이가 더 긴 쪽을 우선으로
재귀를 호출한다.
*/

#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX = 1001;
string str1, str2;
int cache[MAX][MAX];
string ans;

int solve(int a, int b) {
    //기저사례: 둘 중 하나라도 문자열 끝일 경우
    if (a == str1.length() || b == str2.length())
        return 0;
    int& ret = cache[a][b];
    if (ret != -1)return ret;

    //문자열 범위 안에 있으면서
    //두 문자가 같으면 인덱스 1씩 증가
    //다르면 a,b 둘 중 하나씩 증가시킨 것중 최대가 정답
    if (a < str1.length() && b < str2.length()) {
        if (str1[a] == str2[b]) {
            ret = max(ret, solve(a + 1, b + 1) + 1);
        }
        else
            ret = max(solve(a + 1, b), solve(a, b + 1));
    }
    return ret;
}

void reconstruct(int a, int b) {
    //기저사례: 인덱스 범위 초과시 그만
    if (a == str1.length() || b == str2.length())
        return;

    //공통부분 찾았을 경우
    if (str1[a] == str2[b]) {
        ans += str1[a];
        reconstruct(a + 1, b + 1);
    }
    //str1의 인덱스를 추가했을 경우 str2의 인덱스를 추가했을 때보다 LCS의 길이가 크거나 같은 경우
    else if (cache[a + 1][b] >= cache[a][b + 1])
        reconstruct(a + 1, b);
    else
        reconstruct(a, b + 1);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    memset(cache, -1, sizeof(cache));
    cin >> str1 >> str2;

    cout << solve(0, 0) << "\n";
    reconstruct(0, 0);
    cout << ans;

    return 0;
}