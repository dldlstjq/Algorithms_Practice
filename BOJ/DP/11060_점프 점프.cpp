/*
최소를 구해야 해서 cache를 INF로 초기화했다.
최대 maze[i]만큼 움직일 수 있기 때문에 1~maze[i]만큼 움직이면 된다.
음직일 때 i를 1부터 maze[i]까지 잡아주는게 이해하기에 더 쉬운것 같다.
*/

#include <iostream>
#include <algorithm>

using namespace std;

const int MAX = 1000 + 1;
const int INF = 987564321;
int n;
int maze[MAX];
int cache[MAX];

//내 풀이
int solve(int idx) {
    //오른쪽 끝에 오면 0 리턴
    if (idx == n - 1)
        return 0;

    //오른쪽 끝으로 갈 수 없으면 INF를 반환한다.
    int& ret = cache[idx];
    if (ret != INF)return ret;

    int tmp = maze[idx];
    //현재 칸이 idx고 칸에 쓰인 수가 tmp라면 
    //갈 수 있는 칸 idx+1~idx+tmp 까지 갈 수 있다
    for (int i = idx + 1; i <= idx + tmp; ++i) {
        ret = min(ret, 1 + solve(i));
    }
    return ret;
}

//다른 풀이
int minJump(int start)
{
    if (start == N - 1) //목적지 도달할 경우
        return 0;
    if (start >= N) //목적지 도달 못할 경우
        return INF;

    int& result = cache[start];
    if (result != -1)
        return result;
    result = INF;
    for (int i = 1; i <= arr[start]; i++) //arr[start]이하 갈 수 있으므로
        result = min(result, 1 + minJump(start + i));
    return result;

}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    for (int i = 0; i < MAX; ++i)
        cache[i] = INF;

    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> maze[i];

    int ans = solve(0);
    //INF를 반환하면 갈 수 없다.
    if (ans == INF)
        cout << -1;
    else
        cout << ans;
    return 0;
}