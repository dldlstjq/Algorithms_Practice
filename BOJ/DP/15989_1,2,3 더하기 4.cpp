/*
1차원 배열을 이용해 일반적인 방식으로 풀면 중복된 것까지 모두 포함해서 나온다.
중복을 피하기 위해 2차원 배열을 선언해야 하는 것 까진 알았는데 그 뒤로 점화식을 세우지 못했다.

일단 문제에 없는 조건 '오름차순으로만 더할 수 있다'를 추가해봅니다. 왜냐면 그렇게 해야 중복으로 세는 경우를 뺄 수 있거든요.

그리고 dp 식을 적어보면 아래와 같습니다.

- dp[i][j]= 정수 i를 만들 때 마지막으로 더한 수가 j인 경우의 수

더할 수 있는 1, 2, 3이니까 경우의 수를 아래처럼 나눌 수 있습니다.
마지막에 더한 수가 1인 경우: 바로 앞에 더한 수는 1밖에 나올 수 없습니다
마지막에 더한 수가 2인 경우: 바로 앞에 더한 수가 1, 2가 나올 수 있습니다
마지막에 더한 수가 3인 경우: 바로 앞에 더한 수가 1, 2, 3이 나올 수 있습니다
이걸 식으로 정리하면

dp[i][1] = dp[i-1][1];
dp[i][2] = dp[i-2][1]+dp[i-2][2];
dp[i][3] = dp[i-3][1]+dp[i-3][2]+dp[i-3][3];

인 걸 알 수 있습니다.
*/

#include <iostream>
#include <cstring>

using namespace std;

const int MAX = 10000 + 1;
int n;
//cache[i][1]=1로 시작하고, 1보다 작거나 같은 수를 사용해서 i를 만드는 경우
int cache[MAX][4];


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    memset(cache, 0, sizeof(cache));

    /*
    1,2,3일 때 미리 다 구해놓고 i=4일때 부터 점화식 써도 된다.
    cache[1][1] = 1;
    cache[2][1] = cache[2][2] = 1;
    cache[3][1] = cache[3][2] = cache[3][3] = 1;

    for (int i = 4; i < MAX; ++i) {
        cache[i][1] = 1;
        cache[i][2] = cache[i - 2][1] + cache[i - 2][2];
        cache[i][3] = cache[i - 3][1] + cache[i - 3][2] + cache[i - 3][3];
    }*/

    cache[0][1] = 1;
    for (int i = 1; i < MAX; ++i) {
        cache[i][1] = cache[i - 1][1];
        if (i > 1)
            cache[i][2] = cache[i - 2][1] + cache[i - 2][2];
        if (i > 2)
            cache[i][3] = cache[i - 3][1] + cache[i - 3][2] + cache[i - 3][3];
    }
    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        cout << cache[n][1] + cache[n][2] + cache[n][3] << "\n";
    }

    return 0;
}