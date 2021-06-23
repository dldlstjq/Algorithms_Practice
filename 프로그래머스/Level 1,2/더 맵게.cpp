/*
가장 작은 값, 두번째로 작은 값을 사용하는 걸 보면 우선순위 큐를 써야 한다.
배열에 있는 값을 우선순위 큐로 넣고 규칙에 맞게 계산한 다음 만들 수 있는지 없는지 계산하면 된다.

pq에 배열을 넣을떄 for문을 쓰지 않고 넣는 방법, while문 조건을 잘 설정하면 복잡하게 하지 않아도 문제를 풀 수 있다는 점을
다시 생각해보면 좋을 것 같다.
*/

#include <string>
#include <vector>
#include <queue>

using namespace std;

int solution(vector<int> scoville, int K) {
    int answer = 0;

    priority_queue<int, vector<int>, greater<int>> pq;

    for (int i = 0; i < scoville.size(); ++i)
        pq.push(scoville[i]);

    // 가장 작은 스코빌 질수가 K이상이면 섞을 필요 없음
    if (pq.top() >= K)
        answer = 0;

    else {
        while (1) {
            // 가장 작은, 두번째로 작은 음식 섞는다.
            int mixed = 0;

            int food1 = pq.top();
            pq.pop();
            int food2 = pq.top();
            pq.pop();

            mixed = food1 + food2 * 2;

            // 섞은 음식을 pq에 넣는다.
            pq.push(mixed);
            answer++;

            // 가장 작은 값이 K이상이면 섞을 필요 없음
            if (pq.top() >= K)
                break;

            // pq에 값이 하나만 남을 경우 K미만이면 만들 수 없다.
            if (pq.size() == 1) {
                if (pq.top() < K)
                    answer = -1;
                break;
            }
        }

    }


    return answer;
}


// 다른 사람 풀이
#include <vector>
#include <queue>

using namespace std;

int solution(vector<int> scoville, int K) {
    int answer = 0;
    int needHot;
    priority_queue<int, vector<int>, greater<int>> pq(scoville.begin(), scoville.end());

    while (pq.top() < K) {
        if (pq.size() == 1) return answer = -1;
        needHot = pq.top(); pq.pop();
        pq.push(needHot + pq.top() * 2);
        pq.pop(); answer++;
    }

    return answer;
}