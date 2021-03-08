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