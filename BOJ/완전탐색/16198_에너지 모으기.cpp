/*
비교적 단순한 완탐문제였는데 조금 헤맸다.
에너지 값을 계산하고 원소를 하나 삭제한것까진 좋았는데 다시 계산할때 백트래킹으로 삭제한 원소를
다시 삽입해 줘야 맞는 답을 구할 수 있었다.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
vector<int> v;

int solve(vector<int> energy) {
    //첫번째와 마지막은 못고르기 때문에 구슬이 두 개 남으면 종료
    if (energy.size() == 2)
        return 0;

    int ret = 0;

    //1부터 size-1까지 반복해서 최대값을 구한다.
    for (int i = 1; i < energy.size() - 1; ++i) {
        int tmp = energy[i - 1] * energy[i + 1];
        vector<int> tmpenergy;
        //i번째 원소를 제외하고 새로운 벡터에 남은 원소를 삽입한다.
        for (int j = 0; j < energy.size(); ++j) {
            if (i != j)
                tmpenergy.push_back(energy[j]);
        }
        tmp += solve(tmpenergy);
        ret = max(ret, tmp);
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    v.resize(n);
    for (int i = 0; i < n; ++i)
        cin >> v[i];

    cout << solve(v);
    return 0;
}


// 2021.06.30 백트래킹을 사용하는데 원래 배열의 원소를 삭제하고 삽입하는 방식으로 풀었다.
// 이때 풀었던 것보다 위에서 풀듯이 따로 배열을 선언해서 하는게 더 간편하고 덜 복잡할것 같다.
#include <iostream> 
#include <vector> 
#include <algorithm>
using namespace std;

const int MAX = 10 + 1;
int N;
vector<int> energy;
int ret;

void solve(int sum) {
    // 배열에 원소가 2개만 남으면 최댓값 구하고 종료
    if (energy.size() == 2) {
        ret = max(ret, sum);
        return;
    }

    // 맨 끝은 제외이므로 인덱스 1부터 맨 마지막-1까지
    for (int i = 1; i < energy.size() - 1; ++i) {
        int num = energy[i];    // 현재 인덱스 해당하는 배열 값
        int ans = sum;
        ans += energy[i - 1] * energy[i + 1];    //에너지 합
        energy.erase(energy.begin() + i);    // 삭제
        solve(ans);
        energy.insert(energy.begin() + i, num);    // 다시 삽입
    }

}

int main(int argc, char** argv) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 0; i < N; ++i) {
        int n;
        cin >> n;
        energy.push_back(n);
    }

    solve(0);

    cout << ret;
    return 0;
}