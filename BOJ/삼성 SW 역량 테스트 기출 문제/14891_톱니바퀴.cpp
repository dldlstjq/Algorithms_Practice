/*
15662-톱니바퀴 2 문제를 풀어서 로직이 쉽게 생각났다.
톱티바퀴2를 풀때는 구조체를 선언해서 변수를 저장했는데
여기서는 vector<string>으로 톱니바퀴를 저장하고
방향여부를 나타내는 배열하나를 선언했다.

오른쪽, 왼쪽을 돌면서 맞닿은 극이 같으냐 다르냐에 따라 진행하면 되는데
1. 톱니바퀴를 회전시킬 때 인덱스를 반대로 설정한것
2. 방향 direction 인덱스에 변수를 잘못 넣은것
두개 때문에 풀이에 시간이 조금 걸렸다.

한 번 풀었던 문제도 다시 푸니 생각이 잘 안나는 것 같다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<string> gear;
int K;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    for (int i = 0; i < 4; ++i) {
        string str;
        cin >> str;
        gear.push_back(str);
    }

    cin >> K;
    for (int i = 0; i < K; ++i) {
        int num, dir;
        cin >> num >> dir;
        num -= 1;

        int direction[4] = { 0 };
        direction[num] = dir;

        //오른쪽
        for (int j = num; j < 3; ++j) {
            //극이 같으면 종료
            if (gear[j][2] == gear[j + 1][6])
                break;
            //극이 다르면 회전 위치 갱신
            direction[j + 1] = (direction[j] == 1) ? -1 : 1;
        }

        //왼쪽
        for (int j = num; j > 0; --j) {
            if (gear[j][6] == gear[j - 1][2])
                break;
            direction[j - 1] = (direction[j] == 1) ? -1 : 1;
        }

        //톱니바퀴 회전
        string tmp;
        for (int j = 0; j < 4; ++j) {
            tmp = gear[j];
            //방향이 변화없으면 넘어간다.
            if (direction[j] == 0)
                continue;
            //시계방향
            else if (direction[j] == 1) {
                for (int k = 0; k < 8; ++k)
                    gear[j][(k + 1) % 8] = tmp[k];
            }
            //반시계
            else if (direction[j] == -1) {
                for (int k = 0; k < 8; ++k)
                    gear[j][(k + 7) % 8] = tmp[k];
            }
        }
    }

    int score = 0;
    score += (gear[0][0] == '0') ? 0 : 1;
    score += (gear[1][0] == '0') ? 0 : 2;
    score += (gear[2][0] == '0') ? 0 : 4;
    score += (gear[3][0] == '0') ? 0 : 8;

    cout << score;

    return 0;
}