/*
전형적인 dp 풀이이다. 밑에서부터 시작해야 하는 줄 알아 풀이에 어려움을 겪었는데
0,0 부터 시작해서 밑으로 내려가면 0,0에 최댓값이 저장된다.
*/

// bottom-up 방식
#include <string>
#include <vector>
#include <cstring>
using namespace std;

const int MAX = 500 + 1;
vector<vector<int>> tri;
int cache[MAX][MAX];

int solve(int y, int x) {
    if (y == tri.size() - 1)
        return tri[y][x];

    // 메모이제이션
    int& ret = cache[y][x];
    if (ret != -1)return ret;

    ret = max(solve(y + 1, x), solve(y + 1, x + 1)) + tri[y][x];
    return ret;
}

int solution(vector<vector<int>> triangle) {
    int answer = 0;
    int n = triangle.size();

    tri.resize(n);

    for (int i = 0; i < triangle.size(); ++i)
        tri[i] = triangle[i];

    memset(cache, -1, sizeof(cache));
    solve(0, 0);
    answer = cache[0][0];

    return answer;
}


// top-down 방식
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int solution(vector<vector<int>> triangle) {
    int answer = 0;

    vector<vector<int>> dp(triangle.size());
    for (int i = 0; i < triangle.size(); i++) {
        dp[i].resize(triangle[i].size());
    }

    dp[0][0] = triangle[0][0];

    for (int i = 0; i < triangle.size() - 1; i++) {
        for (int j = 0; j < triangle[i].size(); j++) {
            dp[i + 1][j] = max(dp[i + 1][j], dp[i][j] + triangle[i + 1][j]);
            dp[i + 1][j + 1] = max(dp[i + 1][j + 1], dp[i][j] + triangle[i + 1][j + 1]);
        }
    }

    int max_val = 0;
    int N = triangle.size() - 1;
    for (int j = 0; j < triangle[N].size(); j++) {
        max_val = max(max_val, dp[N][j]);
    }

    answer = max_val;
    return answer;
}