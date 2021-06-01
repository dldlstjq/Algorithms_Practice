/*
문제를 맞힌 수를 구하는 것 까지는 해결했는데 가장 높은 점수를 가진 사람을 저장하는게 생각이 잘 안났다.
점수가 같으면 같은 사람을 오름차순으로 넣어야 하는데 일일이 비교하는 건 너무 안좋은 코드였다.
해결과정을 보니 가장 큰 수를 구한 다음 그것과 같은 개수를 맞힌 수포자를 넣으면 끝이었다.
알면 정말 쉬운 문제인데 모르면 많은 시간이 걸릴것 같은 문제이다.
*/

#include <string>
#include <vector>
using namespace std;

vector<int> solution(vector<int> answers) {
    vector<int> answer;

    // 정답 미리 선언
    int first[5] = { 1,2,3,4,5 };
    int second[8] = { 2,1,2,3,2,4,2,5 };
    int third[10] = { 3,3,1,1,2,2,4,4,5,5 };

    int score[3] = { 0 };   //맞힌 개수 저장

    // 모듈러를 활용하면 쉽게 계산
    for (int i = 0; i < answers.size(); ++i) {
        if (answers[i] == first[i % 5])
            score[0]++;
        if (answers[i] == second[i % 8])
            score[1]++;
        if (answers[i] == third[i % 10])
            score[2]++;
    }

    // 가장 많이 맞힌 개수를 ret에 저장
    int ret = max(max(score[0], score[1]), score[2]);

    // ret과 같으면 answer에 저장하면 됨.
    for (int i = 0; i < 3; i++) {
        if (score[i] == ret)
            answer.push_back(i + 1);
    }

    return answer;
}