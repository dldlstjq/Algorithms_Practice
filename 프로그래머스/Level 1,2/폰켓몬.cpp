/*
처음에 백트래킹으로 접근했다가 시간초과를 받았다.
완전탐색으로 모든 경우를 해보는 것은 시간초과이기 때문에 다른 방법을 써야하는데 중복을 생각하면 set이나 map을 쓰면 된다.
여기서는 set을 썼는데 set을 쓴 후 nums/2 크기와 비교하면 쉽게 답이 나온다.
중복울 볼 때 set이나 map을 바로 생각해내야 하는데 그러질 못해 5분안에 끝낼 문제를 30분 이상 허비한 것 같다.
*/

#include <vector>
#include <algorithm>
#include <set>
using namespace std;


int solution(vector<int> nums)
{
    int answer = 0;

    // set에 폰켓몬 종류 저장. set은 중복을 허용하지 않아 각 종류당 하나의 폰켓몬만 저장
    set<int> s(nums.begin(), nums.end());

    // set의 개수가 N/2 보다 작거나 같으면 set의 크기가 최댓값
    // set의 크기가 N/2 보다 크면 N/2가 최대이다.
    if (s.size() <= nums.size() / 2) {
        answer = s.size();
    }

    else {
        answer = nums.size() / 2;
    }

    return answer;
}


/// 백트래킹 풀이
#include <vector>
#include <algorithm>
using namespace std;

int n;  // nums 크기 저장
int ret;    // 폰켓몬 종류 최대 개수
vector<int> pocketmon;  //nums를 저장할 전역변수

void solve(int idx, vector<int> v) {
    // 범위 벗어나면 안 됨
    if (idx == n)
        return;

    // n/2만큼 선택하면 종류 갱신
    if (v.size() == n / 2) {
        // 중복 원소를 제거하면 폰켓몬 종류가 나온다.
        vector<int> tmp = v;
        sort(tmp.begin(), tmp.end());
        tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());

        int size = tmp.size();
        ret = max(ret, size);
        return;
    }

    // 백트래킹
    for (int i = idx; i < n; ++i) {
        v.push_back(pocketmon[i]);
        solve(idx + 1, v);
        v.pop_back();
    }

}


int solution(vector<int> nums)
{
    int answer = 0;

    n = nums.size();
    pocketmon = nums;

    vector<int> ans;
    solve(0, ans);
    answer = ret;
    return answer;
}