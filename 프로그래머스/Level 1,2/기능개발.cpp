/*
처음엔 스택을 생각했는데 가장 먼저 들어간 작업날짜를 알아야 했다.
그래서 큐를 이용하여 다음 작업날짜가 큐 프론트 날짜보다 크면 작업이 완료되고 작거나 같으면 큐에 계속 삽입한다.
다른 사람 풀이를 보니 큐를 이용하지 않고 한 번의 배열 순회만으로도 답을 구할 수 있다.
진짜 천재적인 사람이 많다.
*/


//내 풀이
#include <string>
#include <vector>
#include <queue>
using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> answer;

    queue<int> q;

    // 각 작업의 완성날짜를 complete에 저장
    for (int i = 0; i < progresses.size(); ++i) {
        int tmp = 100 - progresses[i];
        if (tmp % speeds[i] != 0)
            q.push(tmp / speeds[i] + 1);
        else
            q.push(tmp / speeds[i]);
    }

    while (!q.empty()) {
        int cnt = 1;
        int cur = q.front();
        q.pop();

        while (cur >= q.front() && !q.empty()) {
            q.pop();
            cnt++;
        }

        answer.push_back(cnt);
    }


    return answer;
}


// 다른 사람 풀이
// 종료되기까지 날짜를 구한 뒤 배열에 삽입한다. 앞의 작업을 기다려야할 경우 단순히 배열 맨 뒤값을 증가시키면 끝이다.
vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> answer;

    int day;
    int max_day = 0;
    for (int i = 0; i < progresses.size(); ++i)
    {
        day = (99 - progresses[i]) / speeds[i] + 1;

        if (answer.empty() || max_day < day)
            answer.push_back(1);
        else
            ++answer.back();

        if (max_day < day)
            max_day = day;
    }

    return answer;
}