/*
빨리 해결할 수 있을줄 알았는데 결국 못했다.
애초에 2차원 dp로만 계속 생각하다 마땅히 풀이가 생각이 안나서
3차원 dp로 바꿨는데 이마저 제대로 된 식을 세우지 못했다.
3차원 인자가 각각의 체력으로 들어가면 쉽게 풀렸는데 이상하게 잡았다.

2차원 dp로도 생각이 안나면 빨리 3차원도 생각해보는게 좋은 것 같고
dp에 들어갈 인자가 각각 뭘 의미하는지도 정확하게 해야겠다고 느꼈다.
*/

#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int INF = 987654321;
int n;
int scv[4];

//cache[i][j][k]=i번째로 공격받는 scv가 j번째이고, 체력이 k남았을 때 최소 공격횟수
int cache[61][61][61];

int solve(int x, int y, int z) {
    //음수가 나올 시에는 0으로 바꿔준다
    if (x < 0)
        return solve(0, y, z);
    if (y < 0)
        return solve(x, 0, z);
    if (z < 0)
        return solve(x, y, 0);

    //scv 3개 모두 체력이 0이하면 끝
    if (x <= 0 && y <= 0 && z <= 0)
        return 0;

    int& ret = cache[x][y][z];
    if (ret != -1)return ret;
    ret = INF;

    //만약 셋 중에 하나라도 0이하로 내려가는 걸 애초에 막고 싶다면
    //solve(max(0, x-9), max(0, y-3), max(0, z-1)) 로 처리하면 셋 다 0일때만 예외처리하면 된다.
    ret = min(ret, solve(x - 9, y - 3, z - 1) + 1);
    ret = min(ret, solve(x - 9, y - 1, z - 3) + 1);

    ret = min(ret, solve(x - 3, y - 9, z - 1) + 1);
    ret = min(ret, solve(x - 3, y - 1, z - 9) + 1);

    ret = min(ret, solve(x - 1, y - 3, z - 9) + 1);
    ret = min(ret, solve(x - 1, y - 9, z - 3) + 1);

    return ret;
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    memset(cache, -1, sizeof(cache));

    cin >> n;

    for (int i = 0; i < n; ++i)
        cin >> scv[i];

    int ans = solve(scv[0], scv[1], scv[2]);
    cout << ans;

    return 0;
}



/*
처음 접근한 풀이. 2차원 배열로 캐시를 잡았다가 도통 생각나지 않아 3차원 배열로 바꿨다.
cache[i][j][k]=i번째로 공격받는 scv가 j번째이고, 체력이 k남았을 때 최소 공격횟수로 잡았는데
그래도 뭔가 풀리지 않았다.

핵심은 세 인자를 모두 체력으로 잡아주고 거기서 총 6가지 경우를 다 헤아리면 됐었다.
*/
//cache[i][j][k]=i번째로 공격받는 scv가 j번째이고, 체력이 k남았을 때 최소 공격횟수
int cache[3][3][61];

int solve(int order, int idx, int life) {
    if (life <= 0)
        return 0;
    int& ret = cache[order][idx][life];
    if (ret != -1)return ret;
    ret = INF;

    //첫번째는 9만큼 없어지고 두번째는 3... 이런식으로 접근했다.
    if (order == 0) {
        ret = min(ret, solve(order, idx, life - 9) + 1);
    }

    else if (order == 1) {
        ret = min(ret, solve(order, idx, life - 3) + 1);
    }

    else if (order == 2)
        ret = min(ret, solve(order, idx, life - 1) + 1);
    /*if (n == 3) {
        ret = (solve(idx, scv[idx] - 9) + 1) + (solve(idx + 1, scv[idx + 1] - 3) + 1) + (solve(idx + 2, scv[idx + 2] - 1) + 1);
        ret = min(ret, (solve(idx, scv[idx] - 9) + 1) + (solve(idx + 1, scv[idx + 1] - 1) + 1) + (solve(idx + 2, scv[idx + 2] - 3) + 1));

        ret = min(ret, (solve(idx, scv[idx] - 3) + 1) + (solve(idx + 1, scv[idx + 1] - 9) + 1) + (solve(idx + 2, scv[idx + 2] - 1) + 1));
        ret = min(ret, (solve(idx, scv[idx] - 3) + 1) + (solve(idx + 1, scv[idx + 1] - 1) + 1) + (solve(idx + 2, scv[idx + 2] - 9) + 1));

        ret = min(ret, (solve(idx, scv[idx] - 1) + 1) + (solve(idx + 1, scv[idx + 1] - 3) + 1) + (solve(idx + 2, scv[idx + 2] - 9) + 1));
        ret = min(ret, (solve(idx, scv[idx] - 1) + 1) + (solve(idx + 1, scv[idx + 1] - 9) + 1) + (solve(idx + 2, scv[idx + 2] - 3) + 1));
    }

    else if (n == 2) {
        ret = (solve(idx, scv[idx] - 9) + 1) + (solve(idx+1, scv[idx+1] - 3) + 1);
        ret = min(ret, (solve(idx + 1, scv[idx + 1] - 9) + 1) + (solve(idx, scv[idx] - 3) + 1));

    }

    else if (n == 1) {
        ret = min(ret, solve(idx, life - 9) + 1);
    }*/
    ret = min(ret, solve(order, idx, life - 9) + 1);
    return ret;
}