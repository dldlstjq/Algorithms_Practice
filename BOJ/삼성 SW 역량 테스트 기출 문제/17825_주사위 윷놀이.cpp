/*
자세한 풀이는 안산학생님 블로그 참고

1. 윷놀이 판을 어떻게 저장하는가
2. 파란색 칸에서 어떻게 말의 방향을 이동할것인가

이 두가지를 어떻게 표현해야 할지 몰랐다.
완전탐색이기 때문에 재귀를 해야하는데 재귀 로직 역시 생각나지 않았다.

처음엔 윷놀이 판을 2차원 배열에 저장했는데 이렇게 하니까 주사위 수만큼 이동을 어떻게 해야할지,
방향 전환은 어떻게 해야할지도 몰랐다.

안산학생님 블로그를 보니 일차원 배열로 해서
각 윷놀이 칸마다 0부터 시작해서 임의의 번호를 붙이고 해당 원소는 말이 이동할 다음 위치를 저장했다.
자세한 풀이는 코드 참고
*/

#include <iostream>
#include <algorithm>

using namespace std;

//주사위
int dice[10];

//현재 말의 위치
int horse[4];

//윷놀이 판. 해당 노드에 다음 이동할 노드 번호를 저장
int map[35];

int turn[35];   // - 판에서 방향 전환. 방향 전환이 되는 노드 따로 관리

bool check[35]; // - 현 위치에 말이 있는지 확인

int score[35];  // - 윷놀이 판의 점수

//최종 값
int ret;

void dfs(int cnt, int sum) {
    if (cnt == 10) {
        ret = max(ret, sum);
        return;
    }

    for (int i = 0; i < 4; ++i) {
        //현재 말 위치, 이동할 말 위치
        int prev = horse[i];
        int now = prev;
        //움직여야 하는 횟수
        int move = dice[cnt];

        //만약 현재 위치가 방향 전환 해야하는 곳이라면
        //방향 전환하고 움직이는 횟수 1 감소
        if (turn[now] > 0) {
            now = turn[now];
            move -= 1;
        }

        //주사위만큼 이동
        //map[now]에는 now 위치일때 이동할 다음 위치가 저장되어 있다.
        while (move--)
            now = map[now];

        //이미 말이 존재한다면 다른 말 이동
        if (now != 21 && check[now] == true)
            continue;

        check[prev] = false;
        check[now] = true;
        horse[i] = now;

        dfs(cnt + 1, sum + score[now]);

        horse[i] = prev;
        check[prev] = true;
        check[now] = false;
    }
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    //맵 초기화
    //map[a]=b a위치에서 다음 이동할 위치는 b
    for (int i = 0; i < 21; ++i)
        map[i] = i + 1;
    map[21] = 21;

    for (int i = 22; i < 27; i++)
        map[i] = i + 1;
    map[28] = 29; map[29] = 30; map[30] = 25;
    map[31] = 32; map[32] = 25; map[27] = 20;

    //turn[a]=b a자리에서 b자리로 이동
    turn[5] = 22; turn[10] = 31; turn[15] = 28;
    turn[25] = 26;

    //각 위치마다 점수
    for (int i = 0; i < 21; i++)
        score[i] = i * 2;
    score[22] = 13; score[23] = 16; score[24] = 19;
    score[31] = 22; score[32] = 24; score[28] = 28;
    score[29] = 27; score[30] = 26; score[25] = 25;
    score[26] = 30; score[27] = 35;

    for (int i = 0; i < 10; ++i)
        cin >> dice[i];

    dfs(0, 0);
    cout << ret;

    return 0;
}