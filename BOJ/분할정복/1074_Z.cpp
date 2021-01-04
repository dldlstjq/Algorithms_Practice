/*
1780-종이의 개수랑 1992-쿼드트리랑 비슷한 개념의 문제였는데 해결하지 못했다.
해당 위치에서 거꾸로 올라오면서 재귀를 구현하려고 했었는데 생각이 잘 안났다.
구글링 해보니 이해가 되는 코드는 시간초과가 났고 밑의 코드가 통과했다.

다른 블로그를 보니 주어진 순서대로 방문하면 많은 재귀호출로 인해 시간초과가 나서
현재 재귀호출 중인 정사각형 범위내에 정답이 있는지 없는지 판단해서 
없다고 판단되는 경우 아예 그 정사각형 영역은 재귀호출하지 않고 리턴시켜 버리며, 
그 정사각형 영역에 포함된 점의 개수를 결과값에 더해준다.
(실제 재귀 호출로 방문하지 않지만 방문 했다고 판단하는것임)

다음에 다시 꼭 풀어봐야 겠다.
*/

#include <iostream>

using namespace std;

int N, r, c;
int x, y, ans;

void solve(int x, int y, int n) {

    if (x == r && y == c) {
        cout << ans << "\n";
        return;
    }


    if (r < x + n && r >= x && c < y + n && c >= y)
    {
        solve(x, y, n / 2);
        solve(x, y + n / 2, n / 2);
        solve(x + n / 2, y, n / 2);
        solve(x + n / 2, y + n / 2, n / 2);
    }
    // (r,c)가 현재 사분면이 아니면 그냥 사분면의 크기만큼 더해준다 (탐색한걸로 친다)
    else ans += n * n;

}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> N >> r >> c;

    solve(0, 0, (1 << N));

    return 0;
}