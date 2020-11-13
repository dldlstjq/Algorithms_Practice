/*
처음에는 이동하려는 채널을 한글자씩 잘라서 저장한다음 고장난 버튼과 비교해 해당 채널로 바로 갈 수 있는지 없는지로 판단했다.
틀렸다길래 검색해보니 브루트포스 방법을 이용해 처음부터 끝까지 다 검사한단다...
채널은 500,000까지지만 5 6 7 8 9가 망가졌을 경우도 고려해야하기 때문에 MAX를 1,000,000+1까지 설정한다.
자세한건 코드 참고
*/

#include <iostream>

using namespace std;

#define MAX_M 1000000

// 고장난 버튼을 체크
bool chk[10];

// c라는 숫자를 버튼으로 눌러 이동할 경우 이동할 수 있다면 숫자버튼을 누르는 횟수를 리턴
int possible(int c)
{
    // 0인 경우 처리
    if (c == 0)
    {
        return chk[0] ? 0 : 1;
    }

    int len = 0;
    while (c > 0)
    {
        if (chk[c % 10]) return 0;
        len += 1;
        c /= 10;
    }

    return len;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M;

    cin >> N;

    cin >> M;

    // 고장난 버튼 처리
    while (M--)
    {
        int broken_btn;
        cin >> broken_btn;
        chk[broken_btn] = true;
    }

    int ans = abs(N - 100);

    // 완전탐색 과정 1부터 차례대로 검사해서 
    for (int i = 0; i < MAX_M; i++)
    {
        int c = i;
        // 숫자버튼이 고장나지 않아서 그 채널로 이동할 수 있다면 (숫자버튼을 누르는 횟수 + 이동하려는 채널과의 차이)
        int cmp_ans = possible(c) ? possible(c) + abs(N - c) : abs(N - 100);

        if (ans > cmp_ans)
            ans = cmp_ans;
    }

    cout << ans << "\n";

    return 0;
}