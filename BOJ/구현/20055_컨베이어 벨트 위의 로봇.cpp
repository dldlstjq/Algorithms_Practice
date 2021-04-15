/*
문제 이해가 되지 않아 풀지 못했다.

내려가는 위치에서 땅으로 내려간다는 의미가 로봇이 없어진다는 의미이고
컨베이어 벨트가 움직일때는 로봇도 같이 움직인다.

또한 맨 처음 시작할 때는 로봇이 하나도 없고 순서대로 진행할 때 로봇을 올리면 된다.

구현 자체는 쉽지만 문제 이해를 하지 못한다면 해결할 수 없을 것 같다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
using namespace std;

const int MAX = 100 + 2;
int N, K;

deque<int> A;
deque<bool> robot;

//로봇과 벨트 둘 다 움직인다.
void rotate() {
    robot.push_front(robot.back());
    robot.pop_back();

    A.push_front(A.back());
    A.pop_back();

    //내려가는 위치에 있으면 땅으로 내려간다
    robot[N - 1] = false;
}

void move() {
    //0부터 시작했기 때문에 N-2가 N번째 이다.
    //N-1에서 0으로 가면서 움직일 수 있으면 움직인다.
    for (int i = N - 2; i >= 0; --i) {
        if (!robot[i + 1] && (A[i + 1] > 0) && robot[i]) {
            robot[i] = false;
            robot[i + 1] = true;
            A[i + 1]--;
        }
    }
    //내려가는 위치에 있으면 땅으로 내려간다
    robot[N - 1] = false;
}

//첫번째 위치에 놓을 수 있으면 놓는다.
void put_robot() {
    if (!robot[0] && A[0] > 0) {
        robot[0] = true;
        A[0]--;
    }

}

int check() {
    int cnt = 0;
    for (int i = 0; i < 2 * N; ++i) {
        if (A[i] == 0)
            cnt++;
    }
    return cnt;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> K;

    for (int i = 0; i < 2 * N; ++i) {
        int dur;
        cin >> dur;
        A.push_back(dur);
        robot.push_back(false);
    }

    int level = 1;
    while (1) {
        rotate();
        move();
        put_robot();

        int ret = check();
        if (ret >= K)
            break;
        level++;
    }
    cout << level;
    return 0;
}