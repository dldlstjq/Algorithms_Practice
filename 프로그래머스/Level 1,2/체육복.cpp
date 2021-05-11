/*
student 배열을 전역으로 선언해 1로 초기화해준다.
reserve에 있는 학생은 1을 더해주고 lost에 있는 학생은 1을 빼준다.
결과적으로 여벌이 있는 친구는 2, 여벌이 없으면 1, 아예 없으면 0이 저장된다.

lost배열을 돌면서 체육복이 없으면 양옆을 확인해서 여벌이 있으면(값이 2이면)빌리고 없으면 못 빌린다.
간단한 그리디 문제인데 체육복을 빌릴때 여벌이 있지만 도난당한 경우를 고려해야 했다.
그러면 student값이 1이 되어 체육복을 빌리지 않아도 됐는데 이 경우를 고려하지 않아
조금 헤맸다.

그리고 인덱스를 1부터 시작하기 때문에 경우를 lost[i]=1, lost[i]=n으로 나누지 않고 한번에 처리하는 경우도 있다.
*/

#include <string>
#include <vector>
#include <iostream>
using namespace std;

int student[31];    //여벌 체육복 있는 친구는 2, 아니면 1, 도난은 0

int solution(int n, vector<int> lost, vector<int> reserve) {
    int answer = 0;

    //초기화
    for (int i = 0; i < 31; ++i)
        student[i] = 1;


    //여벌 체육복 있는 친구는 1 추가
    for (int i = 0; i < reserve.size(); ++i)
        student[reserve[i]]++;

    //도난 당하면 1 감소
    for (int i = 0; i < lost.size(); ++i)
        student[lost[i]]--;


    for (int i = 0; i < lost.size(); ++i) {
        //이미 한 벌 있는 친구는 빌릴 필요 없다.
        if (student[lost[i]] == 1)
            continue;

        //1번친구는 2번만 가능
        if (lost[i] == 1) {
            if (student[lost[i] + 1] == 2) {
                student[lost[i]] += 1;
                student[lost[i] + 1] -= 1;
            }

        }
        //n번째 친구는 n-1만 가능
        else if (lost[i] == n) {
            if (student[lost[i] - 1] == 2) {
                student[lost[i]] += 1;
                student[lost[i] - 1] -= 1;
            }
        }
        //왼쪽, 오른쪽 중 있는 친구거 빌린다.
        else {
            if (student[lost[i] - 1] == 2) {
                student[lost[i]] += 1;
                student[lost[i] - 1] -= 1;
            }
            else if (student[lost[i] + 1] == 2) {
                student[lost[i]] += 1;
                student[lost[i] + 1] -= 1;
            }
        }

    }

    //체육복이 있는 친구만 카운트
    for (int i = 1; i <= n; ++i)
        if (student[i])
            answer++;


    return answer;
}


///////////////////////////////////////////////////
//다른 사람 풀이. 여벌이 있으면 1, 여벌이 있는데 도난이면 0, 그냥 도난이면 -1이다.
//체육복이 없으면 양 옆을 확인해서 여벌이 있으면 빌린다.
//인덱스가 1부터 시작하기 때문에 i=1 일때 i-1=0이라서 인덱스 에러가 나지 않는다. 훨씬 간단하다.
#include <string>
#include <vector>

using namespace std;
int student[35];
int solution(int n, vector<int> lost, vector<int> reserve) {
    int answer = 0;
    for (int i : reserve) student[i] += 1;
    for (int i : lost) student[i] += -1;
    for (int i = 1; i <= n; i++) {
        if (student[i] == -1) {
            if (student[i - 1] == 1)
                student[i - 1] = student[i] = 0;
            else if (student[i + 1] == 1)
                student[i] = student[i + 1] = 0;
        }
    }
    for (int i = 1; i <= n; i++)
        if (student[i] != -1) answer++;

    return answer;
}