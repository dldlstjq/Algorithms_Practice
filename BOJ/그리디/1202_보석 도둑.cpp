/*
완전탐색으로 풀기에는 시간초과가 걸릴 것 같았고 DP로 접근하기에는 배열 크기가 너무 컸다.
그 다음 방법으로 그리디를 생각해야 했는데 그리디 문제를 너무 안풀어봐서 그런지 생각이 안났다.
그리디와 우선순위 큐를 통해 해결해야 한다.

1. pair<int, int>형 배열에 보석의 정보를 입력받고 int형 배열에 가방의 정보를 입력받습니다.

2. 보석은 무게를 기준으로 오름차순 정렬을 하고 가방은 최대 무게 허용량을 기준으로 오름차순 정렬을 합니다.

3. 핵심은 한 번 확인한 보석은 다시 확인하지 않는 것입니다.

i) 가방의 개수만큼 반복문을 돌립니다.

ii) 해당 가방이 허용할 수 있는 보석까지 우선순위 큐에 넣습니다.

iii) 우선순위 큐는 maxHeap이기 때문에 넣은 보석들 중 무게가 제일 많이 나가는 보석이 root에 있습니다.

iv) 따라서, 우선순위 큐의 root에 있는 보석을 가방에 넣어주고 해당 보석을 우선순위 큐에서 pop합니다.

4. 3번을 모든 가방에 대해 반복합니다.
*/

#include <iostream> 
#include <vector>
#include <algorithm> 
#include <queue>
using namespace std;

const int MAX = 300000 + 1;
int N, K, C;
vector<pair<int, int>> v;
int bag[MAX];

int main(int argc, char** argv) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> K;
    for (int i = 0; i < N; ++i) {
        int M, V;
        cin >> M >> V;
        v.push_back({ M,V });
    }

    for (int i = 0; i < K; ++i)
        cin >> bag[i];

    //보석(무게 기준)과 가방 오름차순 정렬
    sort(v.begin(), v.end());
    sort(bag, bag + K);

    long long ret = 0;
    int idx = 0;
    priority_queue<int> pq; //maxheap 사용

    //무게 제한이 낮은 가방부터 최대한 비싼 보석을 넣는 방법
    for (int i = 0; i < K; ++i) {
        //i번째 가방의 무게 제한에 충족하는 보석 다 넣음
        while (idx < N && v[idx].first <= bag[i])
            pq.push(v[idx++].second);

        //pq의 루트에는 현재 기준 제일 비싼 보석이 들어잇음
        if (!pq.empty()) {
            ret += pq.top();
            pq.pop();
        }
    }

    cout << ret;


    return 0;
}