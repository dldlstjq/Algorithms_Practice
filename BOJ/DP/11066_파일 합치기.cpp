/*
파일을 합칠 때 반드시 페이지가 섞이면 안된다.
즉 1-3, 2-4 이렇게 합쳐서 전체 합치면 순서가 섞이기 때문에 할 수가 없다.
처음엔 아무렇게나 합칠 수 있는 줄 알고 어떻게 해야하나 고민하다 방법이 떠오르지 않았다.

2차원 cache를 이용해야 하고 cache[시작번호][끝번호]를 사용해서 cache는 시작번호부터 끝번호까지의 비용을 담게된다.
또한 각각의 비용에 더불어 합치는 비용까지 더해야 하기 때문에 부분합을 미리 구해놔야 한다.
이래 저래 어려운 문제였다.

알고리즘은 다음과 같다.

예를 들어, 6개의 파일에 대해 dp[1][6]을 채우는 방법은, 어느 기점을 기준으로 왼쪽 최소비용, 오른쪽 최소비용의 합이다.
그 중 왼쪽은 다시 어느 기점을 기준으로 왼쪽 최소비용, 오른쪽 최소비용의 합으로 이루어져 있을 것이다.
이렇게 계속 재귀적으로 나누어가다 보면 더이상 쪼개지지 않는 경우에 도달하고, (파일이 한개라면 비용은 0이다)
이 비용을 리턴받아 왼쪽, 오른쪽 최소비용을 채워나간다.
*/

#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX = 500 + 1;
const int INF = 987654321;
int novel[MAX];
int psum[MAX];
//cache[a][b]=a번째 장부터 b번째 장까지 합치는데 드는 최소한 비용
int cache[MAX][MAX];

int solve(int start, int end) {
    //파일이 한개라면 비용은 0이다.
    if (start == end)
        return 0;

    int& ret = cache[start][end];
    if (ret != INF)return ret;
    //dp[1][4]를 구한다 할때
    //dp[1][1]+dp[2][3], dp[1][2]+dp[3][4], dp[1][3]+dp[4][4] 를 구하는 과정이다.
    //psum을 사용하는 이유는 여기서 구하는 것은 값의 합이 아닌
    //소요되는 비용을 구하는 것이기 때문이다.
    //dp[1][2]가 70 dp[3][4]가 80이면
    //dp[1][4]가 150이 아닌 dp[1][2]+dp[3][4]+[1]부터[4]까지의합 = 300이 되어야한다.
    for (int mid = start; mid < end; ++mid) {
        int left = solve(start, mid);
        int right = solve(mid + 1, end);
        ret = min(ret, left + right);
    }
    return ret += psum[end] - psum[start - 1];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        for (int i = 0; i < MAX; ++i)
            for (int j = 0; j < MAX; ++j)
                cache[i][j] = INF;

        memset(psum, 0, sizeof(psum));

        //1부터 i번째까지의 합을 나타낸다.
        for (int i = 1; i <= n; ++i) {
            cin >> novel[i];
            psum[i] = psum[i - 1] + novel[i];
        }
        cout << solve(1, n) << "\n";
    }

    return 0;
}