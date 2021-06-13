/*
문제 이해를 잘못해서 해결 못했다.
서류와 인터뷰 숫자가 순위인데 성적점수로 이해해서 풀이에 애를 먹었다.
서류 심사 순위대로 오름차순 하면 1등은 무조건 뽑는다.
그 상태에서 현재 인터뷰 순위보다 더 좋은 순위를 보면 선발하고 값을 갱신한다.
*/

#include <iostream> 
#include <vector> 
#include <algorithm>
using namespace std;

int N;
vector<pair<int, int>> v;

int main(int argc, char** argv) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;
    while (T--) {
        int paper, interview;
        v.clear();

        cin >> N;
        for (int i = 0; i < N; ++i) {
            // 성적이 아니라 순위이다.
            cin >> paper >> interview;
            v.push_back({ paper,interview });
        }

        sort(v.begin(), v.end());   // 서류심사 순위대로 정렬

        int ret = 1;    // 서류 심사 1위는 무조건 선발
        int interview_rank = v[0].second;   // 첫번째 사원의 인터뷰 순위
        for (int i = 1; i < N; ++i) {
            // 인터뷰 순위가 현재 학생 인터뷰 순위보다 좋으면 선발
            if (interview_rank > v[i].second) {
                interview_rank = v[i].second;
                ret++;
            }
        }
        cout << ret << '\n';
    }

    return 0;
}