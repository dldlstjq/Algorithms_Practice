/*
9251_LCS 와 비슷한 문제였는데 여기서는 연속된 문자열의 최대 길이를 구해야 한다.
연속된이라는 것을 보고 현재 인덱스와 이전 인덱스가 같으면 계속 진행하고 다르면 아닌걸로
접근했는데 인덱스가 0인 경우 이전 인덱스가 없기 때문에 이걸 예외처리 해야했고
일치하다 끝나버릴 때 어떻게 처리할지가 관건이었다.

다른 사람 풀이를 참고하니 연속이라는 조건이 추가되어 cache를 3차원 배열로 잡았다.
전에도 2차원으로 생각이 안나면 3차원으로 생각해보자라고 했는데도 잊어버렸다.
역시 사람은 복습을 해야된다는 걸 다시금 깨닫는다.

그리고 반복문을 이용해 풀면 훨씬 더 쉽게 풀리는 것 같다. 접근도 쉬워진다.
DP문제는 반복문으로 풀었을 때 더 쉽게 풀리는게 있고 재귀를 이용했을 때가 더 쉬울 때도 있는 것 같다.
*/

#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

string s1, s2;
int cache[2][4001][4001];

//현재 이어지는 부분문자열 존재여부, str1 인덱스, str2 인덱스
int solve(bool head, int idx1, int idx2) {
    //기저 사례: 둘 중 하나라도 문자열 끝인 경우
    if (idx1 == s1.length() || idx2 == s2.length())
        return 0;

    int& ret = cache[head][idx1][idx2];
    if (ret != -1)return ret;

    //부분문자열 시작이 없으면 탐색
    if (head == 0) {
        ret = max(solve(false, idx1 + 1, idx2), solve(false, idx1, idx2 + 1));
        if (s1[idx1] == s2[idx2])  //같은 문자로 시작할 경우
            ret = max(ret, solve(true, idx1 + 1, idx2 + 1) + 1);
    }
    //현재 이어지는 문자열이 있을 경우
    else {
        if (s1[idx1] != s2[idx2])//끊길 경우
            ret = 0;
        else //이어질 경우
            ret = solve(true, idx1 + 1, idx2 + 1) + 1;
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    memset(cache, -1, sizeof(cache));
    cin >> s1 >> s2;
    cout << solve(0, 0, 0);
    return 0;
}


//반복문 풀이. 재귀보다 훨씬 더 간단하게 풀린다...
//이전 인덱스와 현재 인덱스가 같다면 계속 1씩 더해주면 끝이었다.
#include <iostream>
// a 가 빠르면 0 b가 빠르면 1
int Dp[4001][4001];

int main()
{
    int max = 0;
    string A, B;
    cin >> A >> B;

    for (int i = 0; i < A.size(); i++)
        for (int j = 0; j < B.size(); j++)
        {
            if (A[i] == B[j]) {
                if (i == 0 || j == 0)
                    Dp[i][j] = 1;
                else
                    Dp[i][j] = Dp[i - 1][j - 1] + 1;

                if (max < Dp[i][j])
                    max = Dp[i][j];
            }
        }
    printf("%d\n", max);
    return 0;
}



//내가 푼 풀이
//캐시를 2차원 배열로 잡고 이전 인덱스와 현재 인덱스가 같냐 다르냐를 통해 해결하려 했다.
int cache[4001][4001];

//s1의 인덱스가 idx1, s2의 인덱스가 idx2일때 공통 부분 문자열 반환
int solve(int idx1, int idx2) {
    //이전 인덱스에서 문자는 같은데 현재 인덱스 문자가 다르면 연속이 아니다.
    if (idx1 > 0 && idx2 > 0)
        if (s1[idx1 - 1] == s2[idx2 - 1] && s1[idx1] != s2[idx2])
            return 0;
    //기저 사례: 둘 중 하나라도 문자열 끝인 경우
    if (idx1 == s1.length() || idx2 == s2.length())
        return 0;

    int& ret = cache[idx1][idx2];
    if (ret != -1)return ret;
    //ret = 0;
    //연속으로 나타나야 한다. 같은 문자라도 인덱스가 다르면 그건 안됨.
    if (idx1 < s1.length() && idx2 < s2.length()) {
        //제일 처음 시작할 때는 이전 인덱스가 없기 때문에 예외로 하나 빼준다.
        if (s1[idx1] == s2[idx2]) {
            if (idx1 == 0 || idx2 == 0)
                ret = max(ret, solve(idx1 + 1, idx2 + 1) + 1);

            else {
                //두 인덱스 0이 아닌 경우 일치하는 문자가 문자열의 시작인 경우
                if (s1[idx1 - 1] != s2[idx2 - 1] && s1[idx1] == s2[idx2])
                    ret = max(ret, solve(idx1 + 1, idx2 + 1) + 1);
                // 연속된 문자열의 중간인 경우
                else if (s1[idx1 - 1] == s2[idx2 - 1] && s1[idx1] == s2[idx2])
                    ret = max(ret, solve(idx1 + 1, idx2 + 1) + 1);

            }
        }

        ret = max(solve(idx1 + 1, idx2), solve(idx1, idx2 + 1));
    }
    return ret;
}
