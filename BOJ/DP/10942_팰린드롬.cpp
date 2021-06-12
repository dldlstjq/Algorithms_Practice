/*
팰린드롬자체가 앞으로 읽어도 뒤로 읽어도 같은 걸 말하기 때문에
시작과 끝을 늘리고 줄이면서 수가 같은지 확인해야 된다.
cache를 0으로 초기화하여 팰린드롬이면 1을 반환하도록 했는데
재귀함수를 쓰지 않고도 해결할 수 있다.
*/

// 2021.06.13 재귀 풀이와 똑같이 풀었고 정답을 쉽게 받았다.

#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX = 2001;
int n, m;
int arr[MAX];
//cache[a][b]= a~b일때 팰린드롬인가.
int cache[MAX][MAX];

//재귀 풀이
int solve(int start, int end) {
    //start==end가 같거나 start가 end넘어서면 1 리턴
    if (start >= end)
        return 1;

    int& ret = cache[start][end];
    if (ret != 0)return ret;

    //start와 end의 원소가 같으면 1씩 늘이고 줄여가며 메모이제이션 실행
    //애초에 두 원소가 다르면 ret이 0이다
    if (arr[start] == arr[end]) {
        ret = solve(start + 1, end - 1);
    }

    return ret;
}


//비재귀. 미리 팰린드롬인지 구해놓고 값을 가져온다.
void palindrome(void)
{
    //길이 1
    for (int i = 1; i <= N; i++)
        cache[i][i] = true;

    //길이 2
    for (int i = 1; i < N; i++)
        if (arr[i] == arr[i + 1])
            cache[i][i + 1] = true;

    //길이 3 이상
    for (int i = 2; i < N; i++)
        for (int j = 1; j <= N - i; j++)
            //앞 뒤가 같고, 앞 뒤 사이에 있는 수들이 팰린드롬인 경우
            if (arr[j] == arr[j + i] && cache[j + 1][j + i - 1])
                cache[j][j + i] = true;
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    memset(cache, 0, sizeof(cache));

    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> arr[i];

    cin >> m;
    for (int i = 0; i < m; ++i) {
        int s, e;
        cin >> s >> e;
        //팰린들모이면 1, 아니면 0 리턴
        cout << solve(s, e) << "\n";
    }
    return 0;
}