/*
전화기 자체를 2차원 배열로 보고 각 숫자를 누를때마다 조건에 맞게 왼손, 오른손 좌표를 옮겼다.
그렇게 어렵진 않았는데 코드가 생각보다 길어졌고 다른 사람 풀이를 보니 
일차원 배열에 키패드를 저장해서 모듈러 연산을 통해 짧게 구현했다.
2,5,8,0 또한 규칙에 맞게 계산하여 내가 푼 풀이의 절반도 안되는 줄로 해결했다.

같은 문제를 풀더라도 짧은 코드로 이해하기 쉽게 짜는게 중요하다는 것을 느꼈다.
*/

#include <string>
#include <vector>
using namespace std;

pair<int, int> r_hand, l_hand; //왼손, 오른손 좌표 저장

string solution(vector<int> numbers, string hand) {
    string answer = "";

    //왼손, 오른손 초기 위치
    l_hand.first = 3; l_hand.second = 0;
    r_hand.first = 3; r_hand.second = 2;

    for (int i = 0; i < numbers.size(); ++i) {
        //1, 4, 7은 왼손
        if (numbers[i] == 1 || numbers[i] == 4 || numbers[i] == 7) {
            answer += 'L';
            if (numbers[i] == 1)
                l_hand.first = 0, l_hand.second = 0;
            else if (numbers[i] == 4)
                l_hand.first = 1, l_hand.second = 0;
            else if (numbers[i] == 7)
                l_hand.first = 2, l_hand.second = 0;
        }
        //3,6,9은 오른손
        else if (numbers[i] == 3 || numbers[i] == 6 || numbers[i] == 9) {
            answer += 'R';
            if (numbers[i] == 3)
                r_hand.first = 0, r_hand.second = 2;
            else if (numbers[i] == 6)
                r_hand.first = 1, r_hand.second = 2;
            else if (numbers[i] == 9)
                r_hand.first = 2, r_hand.second = 2;
        }
        //2,5,8,0은 더 가까운 손을 이용
        else if (numbers[i] == 2 || numbers[i] == 5 || numbers[i] == 8 || numbers[i] == 0) {
            if (numbers[i] == 2) {//2의 좌표는 (0,1)
                int dist_left = abs(0 - l_hand.first) + abs(1 - l_hand.second);
                int dist_right = abs(0 - r_hand.first) + abs(1 - r_hand.second);
                if (dist_left == dist_right) {
                    if (hand == "right") {
                        answer += 'R';
                        r_hand.first = 0; r_hand.second = 1;
                    }
                    else {
                        answer += 'L';
                        l_hand.first = 0; l_hand.second = 1;
                    }

                }
                else {
                    if (dist_left > dist_right) {
                        answer += 'R';
                        r_hand.first = 0; r_hand.second = 1;
                    }
                    else {
                        answer += 'L';
                        l_hand.first = 0; l_hand.second = 1;
                    }
                }

            }
            else if (numbers[i] == 5) {//5의 좌표는 (1,1)
                int dist_left = abs(1 - l_hand.first) + abs(1 - l_hand.second);
                int dist_right = abs(1 - r_hand.first) + abs(1 - r_hand.second);
                if (dist_left == dist_right) {
                    if (hand == "right") {
                        answer += 'R';
                        r_hand.first = 1; r_hand.second = 1;
                    }
                    else {
                        answer += 'L';
                        l_hand.first = 1; l_hand.second = 1;
                    }

                }
                else {
                    if (dist_left > dist_right) {
                        answer += 'R';
                        r_hand.first = 1; r_hand.second = 1;
                    }
                    else {
                        answer += 'L';
                        l_hand.first = 1; l_hand.second = 1;
                    }
                }
            }
            else if (numbers[i] == 8) {//8의 좌표는 (2,1)
                int dist_left = abs(2 - l_hand.first) + abs(1 - l_hand.second);
                int dist_right = abs(2 - r_hand.first) + abs(1 - r_hand.second);
                if (dist_left == dist_right) {
                    if (hand == "right") {
                        answer += 'R';
                        r_hand.first = 2; r_hand.second = 1;
                    }
                    else {
                        answer += 'L';
                        l_hand.first = 2; l_hand.second = 1;
                    }

                }
                else {
                    if (dist_left > dist_right) {
                        answer += 'R';
                        r_hand.first = 2; r_hand.second = 1;
                    }
                    else {
                        answer += 'L';
                        l_hand.first = 2; l_hand.second = 1;
                    }
                }
            }
            else if (numbers[i] == 0) {//0 좌표는 (3,1)
                int dist_left = abs(3 - l_hand.first) + abs(1 - l_hand.second);
                int dist_right = abs(3 - r_hand.first) + abs(1 - r_hand.second);
                if (dist_left == dist_right) {
                    if (hand == "right") {
                        answer += 'R';
                        r_hand.first = 3; r_hand.second = 1;
                    }
                    else {
                        answer += 'L';
                        l_hand.first = 3; l_hand.second = 1;
                    }

                }
                else {
                    if (dist_left > dist_right) {
                        answer += 'R';
                        r_hand.first = 3; r_hand.second = 1;
                    }
                    else {
                        answer += 'L';
                        l_hand.first = 3; l_hand.second = 1;
                    }
                }
            }
        }

    }
    return answer;
}