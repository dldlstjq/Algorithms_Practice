/*
N, M이 최대 100이기 때문에 완전탐색은 시간초과가 난다.
재귀나 다른 방법을 생각해봤는데 막상 떠오르지가 않았다.

다른 사람 풀이를 찾아보니 DP를 이용한 풀이인데 이런 생각 자체를 잘 하지 못하겠다.
코드를 보며 이해하는 게 더 빠른 것 같다.
*/

#include <iostream> 
#include <vector> 
#include <algorithm>
using namespace std;

const int MAX = 100 + 1;
int N, M, K;
string word;
int cache[MAX][MAX];    // dp[x][y] : x개의 a와 y개의 z로 만들 수 있는 문자열 수
bool noWord;

//dp 만들기
int possible(int A, int Z) {
    //기저 사례
    if (A == 0 || Z == 0)
        return 1;
    int& ret = cache[A][Z];
    if (ret != -1)return ret;

    //dp[x][y]=dp[x-1][y]+dp[x][y-1]
    ret = min(possible(A - 1, Z) + possible(A, Z - 1), 1000000000 + 1);
    return ret;
}

//a 개수, z 개수, 이전 순번
void getWord(int A, int Z, int skip) {
    if (A == 0) {
        for (int i = 0; i < Z; ++i)
            word += 'z';
        return;
    }
    if (Z == 0) {
        for (int i = 0; i < A; ++i)
            word += 'a';
        return;
    }

    //a가 맨 앞에 붙고 나머지 a-1, z 로 만들 수 있는 경우의 수
    int idx = possible(A - 1, Z);
    //맨 앞에 a를 붙이는 경우
    if (skip < idx) {
        word += 'a';
        getWord(A - 1, Z, skip);
    }
    //맨 앞에 z를 붙이는 경우
    else {
        word += 'z';
        getWord(A, Z - 1, skip - idx);
    }

}

int main(int argc, char** argv) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M >> K;
    memset(cache, -1, sizeof(cache));

    if (K > possible(N, M))
        noWord = true;

    //정답단어 만들기
    else
        getWord(N, M, K - 1);

    if (noWord)
        cout << -1;
    else
        cout << word;

    return 0;
}